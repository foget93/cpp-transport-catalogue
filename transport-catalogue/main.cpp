#include "input_reader.h"
#include "transport_catalogue.h"
#include "json_reader.h"
#include "request_handler.h"
#include "map_renderer.h"
#include <sstream>
#include <vector>

using namespace std;
using namespace transport_catalogue;
using namespace query;
using namespace request;

//json::Document LoadJSON(const std::string& s) {
//    std::istringstream strm(s);
//    return json::Load(strm);
//}
//json::Node LoadJSONNode(const std::string& s) {
//    std::istringstream strm(s);
//    return json::LoadNode(strm);
//}

//std::string Print(const json::Node& node) {
//    std::ostringstream out;
//    Print(json::Document{node}, out);
//    return out.str();
//}
//    TransportCatalogue tc;
//    InputReader ir;
//    ir.ParseInput(cin);
//    ir.ParseInput(cin);
//    ir.Load(cout, tc); Input + Stat readers

int main() {
    std::string str {R"( {
                     "base_requests": [
                       {
                         "type": "Bus",
                         "name": "114",
                         "stops": ["Морской вокзал", "Ривьерский мост"],
                         "is_roundtrip": false
                       },
                       {
                         "type": "Stop",
                         "name": "Ривьерский мост",
                         "latitude": 43.587795,
                         "longitude": 39.716901,
                         "road_distances": {"Морской вокзал": 850}
                       },
                       {
                         "type": "Stop",
                         "name": "Морской вокзал",
                         "latitude": 43.581969,
                         "longitude": 39.719848,
                         "road_distances": {"Ривьерский мост": 850}
                       }
                     ],
                     "render_settings": {
                       "width": 200,
                       "height": 200,
                       "padding": 30,
                       "stop_radius": 5,
                       "line_width": 14,
                       "bus_label_font_size": 20,
                       "bus_label_offset": [7, 15],
                       "stop_label_font_size": 20,
                       "stop_label_offset": [7, -3],
                       "underlayer_color": [255,255,255,0.85],
                       "underlayer_width": 3,
                       "color_palette": ["green", [255,160,0],"red"]
                     },
                     "stat_requests": [
                       { "id": 1, "type": "Bus", "name": "114" },
                       { "id": 2, "type": "Stop", "name": "Ривьерский мост" },
                       { "id": 3, "type": "Map" }
                     ]
                   })"s}; // "Map"


    std::istringstream sstream{str};
    ProcessTransportCatalogueQuery(sstream, cout);
//    const auto input_json = json::Load(sstream).GetRoot();
//    //TransportCatalogue tc;
//    const auto& base_request = input_json.AsMap().at("base_requests"s).AsArray();
//    auto tc = request::ProcessBaseRequest(base_request);

    //json::Document doc = LoadJSON(str);

//    int a = 0;

 /*
начальная остановка “Morskoy vokzal” с координатами (99.2283, 329.5),
затем конечная “Riviersiy most” с координатами (50, 232.18) и снова начальная “Morskoy vokzal”.



    map_renderer::RenderSettings set;
    set.width = 600;
    set.height = 400;
    set.padding = 50;
    set.stop_radius = 5;
    set.line_width = 14;
    set.bus_label_font_size = 20;
    set.bus_label_offset = svg::Point(7,15);

    set.stop_label_font_size = 20;
    set.stop_label_offset = svg::Point(7,-3);
    set.underlayer_color = svg::Color {svg::Rgba{255,255,255,0.85}};
    set.underlayer_width  = 3;
    set.color_palette = std::vector<svg::Color>{"green"s, svg::Rgb{255,166,0}, "red"s};

    std::string str {R"({
                     "base_requests": [
                       {
                         "type": "Bus",
                         "name": "14",
                         "stops": [
                           "Ulitsa Lizy Chaikinoi",
                           "Elektroseti",
                           "Ulitsa Dokuchaeva",
                           "Ulitsa Lizy Chaikinoi"
                         ],
                         "is_roundtrip": true
                       },
                       {
                         "type": "Bus",
                         "name": "114",
                         "stops": [
                           "Morskoy vokzal",
                           "Rivierskiy most"
                         ],
                         "is_roundtrip": false
                       },
                       {
                         "type": "Stop",
                         "name": "Rivierskiy most",
                         "latitude": 43.587795,
                         "longitude": 39.716901,
                         "road_distances": {
                           "Morskoy vokzal": 850
                         }
                       },
                       {
                         "type": "Stop",
                         "name": "Morskoy vokzal",
                         "latitude": 43.581969,
                         "longitude": 39.719848,
                         "road_distances": {
                           "Rivierskiy most": 850
                         }
                       },
                       {
                         "type": "Stop",
                         "name": "Elektroseti",
                         "latitude": 43.598701,
                         "longitude": 39.730623,
                         "road_distances": {
                           "Ulitsa Dokuchaeva": 3000,
                           "Ulitsa Lizy Chaikinoi": 4300
                         }
                       },
                       {
                         "type": "Stop",
                         "name": "Ulitsa Dokuchaeva",
                         "latitude": 43.585586,
                         "longitude": 39.733879,
                         "road_distances": {
                           "Ulitsa Lizy Chaikinoi": 2000,
                           "Elektroseti": 3000
                         }
                       },
                       {
                         "type": "Stop",
                         "name": "Ulitsa Lizy Chaikinoi",
                         "latitude": 43.590317,
                         "longitude": 39.746833,
                         "road_distances": {
                           "Elektroseti": 4300,
                           "Ulitsa Dokuchaeva": 2000
                         }
                       }
                     ]
                   })"s};
    istringstream ss {str};
    const auto input_json = json::Load(ss).GetRoot();
    const auto& base_request = input_json.AsMap().at("base_requests"s).AsArray();
    auto tc = request::ProcessBaseRequest(base_request);

    map_renderer::MapRenderer map_rend(set);
    std::vector<const transport_catalogue::Bus* > bus_ptrs;
    bus_ptrs.push_back(tc.GetRoute("14"s));
    bus_ptrs.push_back(tc.GetRoute("114"s));

    map_rend.PrintRoad(bus_ptrs,cout);*/

    return 0;
}

/*
json::Document LoadJSON(const std::string& s) {
    std::istringstream strm(s);
    return json::Load(strm);
}

std::string Print(const Node& node) {
    std::ostringstream out;
    Print(Document{node}, out);
    return out.str();
}
 *
void Benchmark() {
    const auto start = std::chrono::steady_clock::now();
    Array arr;
    arr.reserve(1'000);
    for (int i = 0; i < 1'000; ++i) {
        arr.emplace_back(Dict{
            {"int"s, 42},
            {"double"s, 42.1},
            {"null"s, nullptr},
            {"string"s, "hello"s},
            {"array"s, Array{1, 2, 3}},
            {"bool"s, true},
            {"map"s, Dict{{"key"s, "value"s}}},
        });
    }
    std::stringstream strm;
    json::Print(Document{arr}, strm);
    const auto doc = json::Load(strm);
    assert(doc.GetRoot() == arr);
    const auto duration = std::chrono::steady_clock::now() - start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms"sv
              << std::endl;
}*/

/*
Ввод
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka, 100m to Marushkino
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324, 9500m to Marushkino
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
Вывод
Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.36124 curvature
Bus 750: 7 stops on route, 3 unique stops, 27400 route length, 1.30853 curvature
Bus 751: not found
Stop Samara: not found
Stop Prazhskaya: no buses
Stop Biryulyovo Zapadnoye: buses 256 828
*/
//"road_distances": {"Ривьерский мост": 850}
