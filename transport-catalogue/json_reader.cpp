#include "json_reader.h"

#include <string>

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
    for (std::string_view bus : buses)
        buses_array.emplace_back(std::string(bus));

    response.emplace("buses"s, std::move(buses_array));

    return response;
}

json::Node MakeErrorResponse(int request_id) {
    json::Dict response;

    response.emplace("request_id"s, request_id);
    response.emplace("error_message"s, "not found"s);

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
        auto route = ParseBusRouteInput(request_dict_view);
        catalogue.AddRoute(route.number, route.type, route.stops);
    }

    return catalogue;
}




json::Node MakeStatResponse(TransportCatalogue& catalogue, const json::Array& requests/*,
                            const render::Visualization& settings*/) {
    json::Array response;
    response.reserve(requests.size());

    for (const auto& request : requests) {
        const auto& request_dict_view = request.AsMap();

        int request_id = request_dict_view.at("id"s).AsInt();
        std::string type = request_dict_view.at("type"s).AsString();
        std::string name;  //> Could be a name of bus or a stop

        if (type == "Bus"s) {
            name = request_dict_view.at("name"s).AsString();

            const Bus* buf = catalogue.GetRoute(name);
            BusStat bs = catalogue.GetStatistics(buf);
//            if (BusStat bs = catalogue.GetStatistics(catalogue.GetRoute(name))) {
//                response.emplace_back(MakeBusResponse(request_id, *bus_statistics));
//            } else {
//                response.emplace_back(MakeErrorResponse(request_id));
//            }
        } else if (type == "Stop"s) {
            name = request_dict_view.at("name"s).AsString();
            if (auto buses = catalogue.GetBusesPassingThroughTheStop(name)) {
                response.emplace_back(MakeStopResponse(request_id, *buses));
            } else {
                response.emplace_back(MakeErrorResponse(request_id));
            }
        } /*else if (type == "Map"s) {
            std::string image = RenderTransportMap(catalogue, settings);
            response.emplace_back(MakeMapImageResponse(request_id, image));
        }*/
    }

    return response;
}
}
  // namespace request
