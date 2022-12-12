#include "transport_catalogue.h"

#include <algorithm>

using namespace std;

namespace transport_catalogue {

void TransportCatalogue::AddStop(string_view name, double latitude = 0., double longitude = 0.) {
    stops_.push_back({string{name.begin(), name.end()}, {latitude, longitude}});
    stopname_to_stop_[stops_.back().name] = &stops_.back();
} // 1 (добавление: остановки + индексы_остановок )

void TransportCatalogue::AddRoute(string_view number, RouteType type, std::vector<std::string_view> stops) {
    Bus result;
    result.number = string{number.begin(), number.end()};

    for (auto& stop : stops) {
        auto found_stop = GetStop(stop);

        if (found_stop != nullptr) {
            result.stops.push_back(move(found_stop));
        }
    }
    if (type == RouteType::DIRECT) {
        auto temp = result.stops;

        for (int i = temp.size() - 2; i >= 0; --i) {
            result.stops.push_back(result.stops[i]);
        }
    }

    buses_.push_back(move(result));
    busname_to_bus_[buses_.back().number] = &buses_.back();

    for (auto& stop : stops) {
        auto found_stop = GetStop(stop);

        if (found_stop != nullptr) {
            stop_to_busnames_[found_stop].insert(buses_.back().number);
        }
    }
} // 2

const Bus* TransportCatalogue::GetRoute(string_view name) const {
    if (busname_to_bus_.count(name) > 0) {
        return busname_to_bus_.at(name);
    }
    else {
        return nullptr;
    }
}

const Stop* TransportCatalogue::GetStop(string_view name) const {
    if (stopname_to_stop_.count(name) > 0) {
        return stopname_to_stop_.at(name);
    }
    else {
        return nullptr;
    }
}

set<string_view> TransportCatalogue::GetBuses(string_view stop) const {
    if (auto found_stop = GetStop(stop); found_stop != nullptr) {
        if (stop_to_busnames_.count(found_stop)) {
            return stop_to_busnames_.at(found_stop);
        }
    }
    return set<string_view>{};
}

void TransportCatalogue::SetStopDistance(std::string_view stop1, uint64_t dist, std::string_view stop2) {
    auto p_stop1 = GetStop(stop1);
    auto p_stop2 = GetStop(stop2);

    if (p_stop1 != nullptr && p_stop2 != nullptr) {
        stop_distance_table_[pair{p_stop1, p_stop2}] = dist;
    }
}

uint64_t TransportCatalogue::GetStopDistance(const Stop* p_stop1, const Stop* p_stop2) const {
    if (p_stop1 != nullptr && p_stop2 != nullptr) {
        if (stop_distance_table_.count(pair{p_stop1, p_stop2}) > 0) {
            return stop_distance_table_.at(pair{p_stop1, p_stop2});
        }
        else {
            if (stop_distance_table_.count(pair{p_stop2, p_stop1}) > 0) {
                return stop_distance_table_.at(pair{p_stop2, p_stop1});
            }
        }
    }
    return 0;
}

BusStat TransportCatalogue::GetStatistics(const Bus* bus) const {
    BusStat statistics;

    statistics.all_stops = bus->stops.size();

    auto temp = bus->stops;
    sort(temp.begin(), temp.end());
    auto it = unique(temp.begin(), temp.end());
    temp.resize(distance(temp.begin(), it));
    statistics.unique_stops = temp.size();

    for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
        statistics.distance += ComputeDistance(bus->stops[i]->coordinates, bus->stops[i + 1]->coordinates);
        statistics.real_distance += GetStopDistance(bus->stops[i], bus->stops[i + 1]);
    }
    statistics.curvature = statistics.real_distance / statistics.distance;

    return statistics;
}

//std::unique_ptr<std::set<std::string_view>> TransportCatalogue::GetBusesPassingThroughTheStop(
//    std::string_view stop_name) const {
//    const auto stop = GetStop(stop_name);
//    if (const auto position = stop_to_busnames_.find(stop); position != stop_to_busnames_.end())
//        return std::make_unique<std::set<std::string_view>>(position->second);
//    return nullptr;
//}

}//namespace transport_catalogue
