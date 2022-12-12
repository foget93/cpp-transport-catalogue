#include "input_reader.h"
#include "transport_catalogue.h"
#include "json_reader.h"
#include <sstream>

using namespace std;
using namespace transport_catalogue;
using namespace query;

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

int main() {
//    TransportCatalogue tc;
//    InputReader ir;
//    ir.ParseInput(cin);
//    ir.ParseInput(cin);
//    ir.Load(cout, tc);

//    std::string str {R"(  {
//                     "base_requests": [
//                       {
//                         "type": "Bus",
//                         "name": "114",
//                         "stops": ["Морской вокзал", "Ривьерский мост"],
//                         "is_roundtrip": false
//                       },
//                       {
//                         "type": "Stop",
//                         "name": "Ривьерский мост",
//                         "latitude": 43.587795,
//                         "longitude": 39.716901,
//                         "road_distances": {"Морской вокзал": 850}
//                       },
//                       {
//                         "type": "Stop",
//                         "name": "Морской вокзал",
//                         "latitude": 43.581969,
//                         "longitude": 39.719848,
//                         "road_distances": {"Ривьерский мост": 850}
//                       }
//                     ],
//                     "stat_requests": [
//                       { "id": 1, "type": "Stop", "name": "Ривьерский мост" },
//                       { "id": 2, "type": "Bus", "name": "114" }
//                     ]
//                   }   )"s};
    std::string str {R"(  {
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
                     ]
                   }   )"s};
    std::istringstream sstream{str};

    const auto input_json = json::Load(sstream).GetRoot();
    //TransportCatalogue tc;
    const auto& base_request = input_json.AsMap().at("base_requests"s).AsArray();
    auto tc = request::ProcessBaseRequest(base_request);

    //json::Document doc = LoadJSON(str);

//    int a = 0;



    return 0;

    /*
     * Примерная структура программы:
     *
     * Считать JSON из stdin
     * Построить на его основе JSON базу данных транспортного справочника
     * Выполнить запросы к справочнику, находящиеся в массиве "stat_requests", построив JSON-массив
     * с ответами.
     * Вывести в stdout ответы в виде JSON
     */
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
