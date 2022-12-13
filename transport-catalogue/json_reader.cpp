#include "json_reader.h"

#include <string>
#include <sstream>

namespace request {

using namespace transport_catalogue;
using namespace request;

using namespace std::literals;

/*
enum class RouteType {
    DIRECT, // -
    CIRCULAR // >
};



    void AddStop(std::string_view name, double latitude, double longitude);
    void AddRoute(std::string_view number, RouteType type, std::vector<std::string_view> stops);
*/

//struct Stop {
//    std::string name;
//    geo::Coordinates coordinates;
//};
std::pair<Stop, bool> ParseBusStopInput(const json::Dict& info) {
    Stop stop;

    stop.name = info.at("name"s).AsString();
    stop.coordinates.lat = info.at("latitude"s).AsDouble();
    stop.coordinates.lng = info.at("longitude"s).AsDouble();

    bool has_road_distances = !info.at("road_distances"s).AsMap().empty();

    return {std::move(stop), has_road_distances};
}

//struct Bus {
//    std::string number;
//    std::vector<const Stop*> stops;
//};

/*

*/
struct Bus_str {
    std::string number;
    RouteType type;
    std::vector<std::string_view> stops;
};

Bus_str ParseBusRouteInput(const json::Dict& info) {
    Bus_str bus;

    bus.number = info.at("name"s).AsString();
    bus.type = info.at("is_roundtrip"s).AsBool() ? RouteType::CIRCULAR : RouteType::DIRECT;

    const auto& stops = info.at("stops"s).AsArray();
    bus.stops.reserve(stops.size());

    for (const auto& stop : stops) {
        bus.stops.emplace_back(stop.AsString());
    }

    return bus;
}

//struct BusStat {
//    size_t all_stops {0};
//    size_t unique_stops {0};
//    double distance {0.};
//    uint64_t real_distance {0};
//    double curvature {0.};
//};

json::Node MakeBusResponse(int request_id, const BusStat& statistics) {
    json::Dict response;

    // P.S. no need to use std::move() because all types on the right are trivial
    response.emplace("curvature"s, statistics.curvature);
    response.emplace("request_id"s, request_id);
    response.emplace("route_length"s, static_cast<int>(statistics.real_distance));
    response.emplace("stop_count"s, static_cast<int>(statistics.all_stops));
    response.emplace("unique_stop_count"s, static_cast<int>(statistics.unique_stops));

    return response;
}

json::Node MakeStopResponse(int request_id, const std::set<std::string_view>& buses) {
    json::Dict response;

    response.emplace("request_id"s, request_id);

    json::Array buses_array;
    buses_array.reserve(buses.size());
    for (std::string_view bus : buses) {
        buses_array.emplace_back(std::string(bus));
    }

    response.emplace("buses"s, std::move(buses_array));

    return response;
}

json::Node MakeErrorResponse(int request_id) {
    json::Dict response;

    response.emplace("request_id"s, request_id);
    response.emplace("error_message"s, "not found"s);

    return response;
}

json::Node MakeMapImageResponse(int request_id, const std::string& image) {
    json::Dict response;

    response.emplace("request_id"s, request_id);
    response.emplace("map"s, image);

    return response;
}

TransportCatalogue ProcessBaseRequest(const json::Array& requests) {
    TransportCatalogue catalogue;

    // We could add distances between stops ONLY when they EXIST in catalogue
    std::vector<int> requests_ids_with_road_distances;
    requests_ids_with_road_distances.reserve(requests.size());

    std::vector<int> requests_ids_with_buses;
    requests_ids_with_buses.reserve(requests.size());

    // Step 1. Store all stops to the catalog and mark requests, needed to be processed afterward
    for (int id = 0; id != static_cast<int>(requests.size()); ++id) {
        const auto& request_dict_view = requests.at(id).AsMap();

        if (request_dict_view.at("type"s) == "Stop"s) {
            auto [stop, has_road_distances] = ParseBusStopInput(request_dict_view);
            if (has_road_distances)
                requests_ids_with_road_distances.emplace_back(id);

            catalogue.AddStop(std::move(stop.name), stop.coordinates.lat, stop.coordinates.lng);
        } else if (request_dict_view.at("type"s) == "Bus"s) {
            requests_ids_with_buses.emplace_back(id);
        }
    }

    // Step 2. Add distances between all stops
    for (int id : requests_ids_with_road_distances) {
        const auto& request_dict_view = requests.at(id).AsMap();

        std::string_view stop_from = request_dict_view.at("name"s).AsString();
        for (const auto& [stop_to, distance] : request_dict_view.at("road_distances"s).AsMap())
            catalogue.SetStopDistance(stop_from, distance.AsInt(), stop_to);
    }

    //void AddRoute(std::string_view number, RouteType type, std::vector<std::string_view> stops);
    // Step 3. Add info about buses routes through stops
    for (int id : requests_ids_with_buses) {
        const auto& request_dict_view = requests.at(id).AsMap();
        Bus_str route = ParseBusRouteInput(request_dict_view);
        catalogue.AddRoute(route.number, route.type, route.stops);
    }

    return catalogue;
}

svg::Color JsonToColor(const json::Node& nod) {
    svg::Color col;
    if (nod.IsString()) {
        col = {nod.AsString()};
    }
    else {
        if (nod.AsArray().size() == 4) {
            col = svg::Rgba{
                    static_cast<uint8_t>(nod.AsArray()[0].AsInt()),
                    static_cast<uint8_t>(nod.AsArray()[1].AsInt()),
                    static_cast<uint8_t>(nod.AsArray()[2].AsInt()),
                    nod.AsArray()[3].AsDouble()
            };
        }
        else {
            col = svg::Rgb{
                    static_cast<uint8_t>(nod.AsArray()[0].AsInt()),
                    static_cast<uint8_t>(nod.AsArray()[1].AsInt()),
                    static_cast<uint8_t>(nod.AsArray()[2].AsInt())
            };
        }
    }
    return col;
}

map_renderer::RenderSettings ParseRenderSettings(const json::Dict& settings) {
    map_renderer::RenderSettings render_settings ;

    std::vector<svg::Color> vec;
    for (auto& a: settings.at("color_palette"s).AsArray()) {
        auto x = JsonToColor(a);
        vec.push_back(move(x));
    }


    render_settings.width = settings.at("width"s).AsDouble();
    render_settings.height = settings.at("height"s).AsDouble();
    render_settings.padding = settings.at("padding"s).AsDouble();
    render_settings.line_width = settings.at("line_width"s).AsDouble();
    render_settings.stop_radius = settings.at("stop_radius"s).AsDouble();
    render_settings.bus_label_font_size = settings.at("bus_label_font_size"s).AsInt();
    render_settings.bus_label_offset = {settings.at("bus_label_offset"s).AsArray()[0].AsDouble(),
                                        settings.at("bus_label_offset"s).AsArray()[1].AsDouble()};

    render_settings.stop_label_font_size = settings.at("stop_label_font_size"s).AsInt();
    render_settings.stop_label_offset = {settings.at("stop_label_offset"s).AsArray()[0].AsDouble(),
                                         settings.at("stop_label_offset"s).AsArray()[1].AsDouble()};

    render_settings.underlayer_color = JsonToColor(settings.at("underlayer_color"s));
    render_settings.underlayer_width = settings.at("underlayer_width"s).AsDouble();
    render_settings.color_palette = move(vec);

    return render_settings;
}

json::Node MakeStatResponse(TransportCatalogue& catalogue, const json::Array& requests,
                            const map_renderer::RenderSettings& settings) {
    json::Array response;
    response.reserve(requests.size());

    for (const auto& request : requests) {
        const auto& request_dict_view = request.AsMap();

        int request_id = request_dict_view.at("id"s).AsInt();
        std::string type = request_dict_view.at("type"s).AsString();
        std::string name;

        if (type == "Bus"s) {
            name = request_dict_view.at("name"s).AsString();

            const Bus* buf = catalogue.GetRoute(name);
            if (buf != nullptr) {
                BusStat bs = catalogue.GetStatistics(buf);
                response.emplace_back(MakeBusResponse(request_id, bs));
            } else {
                response.emplace_back(MakeErrorResponse(request_id));
            }
        }
        else if (type == "Stop"s) {
            name = request_dict_view.at("name"s).AsString();
            std::set<std::string_view> buses = catalogue.GetBuses(name);

            if (catalogue.GetStop(name) != nullptr) {
                if (buses.size() == 0 && !catalogue.GetStop(name)) { //остановка не входящая не в один маршрут (будь она не ладна)) =)))
                    response.emplace_back(MakeErrorResponse(request_id));
                }
                else {
                    response.emplace_back(MakeStopResponse(request_id, buses));
                }
            }
            else {
                response.emplace_back(MakeErrorResponse(request_id));
            }
        }
        else if (type == "Map"s) {
            map_renderer::MapRenderer map_rend(settings);
            std::ostringstream os;
            map_rend.PrintRoad(catalogue.GetAllBuses(), os);

            std::string image = os.str();
            response.emplace_back(MakeMapImageResponse(request_id, image));
        }
    }

    return response;
}
}
  // namespace request
