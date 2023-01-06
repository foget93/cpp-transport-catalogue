#include "map_renderer.h"

#include <algorithm>

using namespace std;
using namespace transport_catalogue;

map_renderer::RenderSettings map_renderer::MapRenderer::GetMapRendererSettings() {
    return map_rend_;
}

void map_renderer::MapRenderer::SetMapRenderer(RenderSettings map_rend) {
    map_rend_ = map_rend;
}

svg::Polyline MakePolyline (const transport_catalogue::Bus* busptr, double line_width, svg::Color color, const SphereProjector& proj) {
    using namespace svg;
    Polyline polyline;
    polyline.SetStrokeWidth(line_width).SetFillColor("none");
    polyline.SetStrokeLineJoin(StrokeLineJoin::ROUND);
    polyline.SetStrokeLineCap(StrokeLineCap::ROUND);
    polyline.SetStrokeColor(color);

    vector<geo::Coordinates> coords2;
    for (auto stopptr : busptr->stops) {
        geo::Coordinates coord(stopptr->coordinates.lat, stopptr->coordinates.lng);
        coords2.push_back(move(coord));
    }

    for (const auto coord: coords2) {
        const svg::Point screen_coord = proj(coord);
        polyline.AddPoint(screen_coord);
    }
    return polyline;
}

vector<svg::Text> MakeBusName(const transport_catalogue::Bus* busptr, svg::Point point,
                              int bus_label_font_size, svg::Color color, double underlayer_width,
                              svg::Color underlayer_color, const SphereProjector& proj) {
    using namespace svg;
    vector<Text> result;
    Text number_text;
    Point text_coord = proj(geo::Coordinates(busptr->stops[0]->coordinates.lat, busptr->stops[0]->coordinates.lng));
    number_text.SetData(busptr->number).SetPosition(text_coord).
            SetOffset(point).SetFontSize(bus_label_font_size).SetFontFamily("Verdana"s).SetFontWeight("bold"s).SetFillColor(color);
    Text underlayer_number_text;
    underlayer_number_text.SetData(busptr->number).SetPosition(text_coord).
            SetOffset(point).SetFontSize(bus_label_font_size).SetFontFamily("Verdana"s).
            SetFontWeight("bold"s).SetStrokeLineCap(StrokeLineCap::ROUND).SetStrokeLineJoin(StrokeLineJoin::ROUND).
            SetStrokeWidth(underlayer_width).SetStrokeColor(underlayer_color).SetFillColor(underlayer_color);

    result.push_back(move(underlayer_number_text));
    result.push_back(move(number_text));
    if (busptr->type == RouteType::DIRECT && busptr->stops[busptr->stops.size()/2] != busptr->stops[0]) {
        Text number_text_direct;
        Point text_coord2 = proj(geo::Coordinates(busptr->stops[busptr->stops.size()/2]->coordinates.lat, busptr->stops[busptr->stops.size()/2]->coordinates.lng));
        number_text_direct.SetData(busptr->number).SetPosition(text_coord2).SetOffset(point)
                .SetFontSize(bus_label_font_size).SetFontFamily("Verdana"s)
                .SetFontWeight("bold"s).SetFillColor(color);
        Text underlayer_number_text_direct;
        underlayer_number_text_direct.SetData(busptr->number).SetPosition(text_coord2).SetOffset(point)
                .SetFontSize(bus_label_font_size).SetFontFamily("Verdana"s)
                .SetFontWeight("bold"s).SetStrokeLineCap(StrokeLineCap::ROUND)
                .SetStrokeLineJoin(StrokeLineJoin::ROUND).SetStrokeWidth(underlayer_width)
                .SetStrokeColor(underlayer_color).SetFillColor(underlayer_color);
        result.push_back(move(underlayer_number_text_direct));
        result.push_back(move(number_text_direct));
    }
    return result;
}

void map_renderer::MapRenderer::PrintRoad ( std::vector<const Bus*> buses, ostream& out ) {
    std::sort(buses.begin(), buses.end(), [](const Bus* a, const Bus* b) {
        return lexicographical_compare(a->number.begin(), a->number.end(), b->number.begin(), b->number.end());
    });
    std::vector<const Stop*> stops;

    using namespace svg;
    Document result;
    vector<geo::Coordinates> coords;

    for (auto busptr : buses) {
        for (auto stopptr : busptr->stops) {
            stops.push_back(stopptr);
            geo::Coordinates coord(stopptr->coordinates.lat, stopptr->coordinates.lng);
            coords.push_back(move(coord));
        }
    }

    std::sort(stops.begin(), stops.end(), [](const Stop* a, const Stop* b) {
        return lexicographical_compare(a->name.begin(), a->name.end(), b->name.begin(), b->name.end());
    });

    auto stops0 = unique(stops.begin(), stops.end());
    stops.erase(stops0, stops.end());

    const SphereProjector proj{coords.begin(), coords.end(), map_rend_.width, map_rend_.height, map_rend_.padding};

    size_t i = 0;
    for (auto busptr: buses) {
        if (!busptr->stops.empty()) {
            result.Add(MakePolyline(busptr, map_rend_.line_width, map_rend_.color_palette[i], proj));
            i++;
            i = (i % map_rend_.color_palette.size());
        }
    }
    // остановки(кружки) + название + название маршрутов
    i = 0;
    for (auto busptr: buses) {
        if (!busptr->stops.empty()) {
            for (auto& text :
                MakeBusName(busptr, Point(map_rend_.bus_label_offset.x, map_rend_.bus_label_offset.y), map_rend_.bus_label_font_size, map_rend_.color_palette[i], map_rend_.underlayer_width, map_rend_.underlayer_color, proj)) {
                result.Add(move(text));
            }
            i++;
            i = (i % map_rend_.color_palette.size());
        }
    }

    for (auto stopptr : stops) {
        Circle circle;
        Point circle_coord = proj(geo::Coordinates(stopptr->coordinates.lat, stopptr->coordinates.lng));
        circle.SetCenter(circle_coord).SetRadius(map_rend_.stop_radius).SetFillColor("white"s);
        result.Add(move(circle));
    }
    for (auto stopptr : stops) {
        Text underlayer_stop_text;
        Point text_coord = proj(geo::Coordinates(stopptr->coordinates.lat, stopptr->coordinates.lng));
        underlayer_stop_text.SetPosition(text_coord).SetOffset(Point(map_rend_.stop_label_offset.x, map_rend_.stop_label_offset.y)).
              SetFontSize(map_rend_.stop_label_font_size).SetFontFamily("Verdana"s).SetData(stopptr->name).
              SetStrokeColor(map_rend_.underlayer_color).SetFillColor(map_rend_.underlayer_color).
              SetStrokeWidth(map_rend_.underlayer_width).SetStrokeLineCap(StrokeLineCap::ROUND).SetStrokeLineJoin(StrokeLineJoin::ROUND);
        result.Add(move(underlayer_stop_text));
        Text stop_text;
        stop_text.SetPosition(text_coord).SetOffset(Point(map_rend_.stop_label_offset.x, map_rend_.stop_label_offset.y)).
                SetFontSize(map_rend_.stop_label_font_size).
                SetFontFamily("Verdana"s).SetData(stopptr->name).SetFillColor("black"s);
        result.Add(move(stop_text));
    }

    result.Render(out);
}

bool IsZero(double value) {
    return std::abs(value) < EPSILON;
}

svg::Point SphereProjector::operator()(geo::Coordinates coords) const {
        return {
            (coords.lng - min_lon_) * zoom_coeff_ + padding_,
            (max_lat_ - coords.lat) * zoom_coeff_ + padding_
        };
 }
