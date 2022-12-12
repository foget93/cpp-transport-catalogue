#pragma once

#include "geo.h"
#include "domain.h"

#include <deque>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <memory>

namespace transport_catalogue {

namespace detail {
template<typename Type>
class StopHasher {
public:
    size_t operator()(std::pair<const Type*, const Type*> stop) const {
        return hasher_(stop.first) + 47 * hasher_(stop.second);
    }

private:
    std::hash<const Type*> hasher_;
};


} //namespace detail

using namespace transport_catalogue::detail;
class TransportCatalogue {
public:
    void AddStop(std::string_view name, double latitude, double longitude);

    void AddRoute(std::string_view number, RouteType type, std::vector<std::string_view> stops);

    const Bus* GetRoute(std::string_view name) const;

    const Stop* GetStop(std::string_view name) const;

    std::set<std::string_view> GetBuses(std::string_view stop) const;

    void SetStopDistance(std::string_view stop1, uint64_t dist, std::string_view stop2);

    uint64_t GetStopDistance(const Stop* stop1, const Stop* stop2) const;

    BusStat GetStatistics(const Bus* bus) const;

    //[[nodiscard]] std::unique_ptr<std::set<std::string_view>> GetBusesPassingThroughTheStop(std::string_view stop_name) const;

private:
    std::deque<Bus> buses_;
    std::unordered_map<std::string_view, const Bus*> busname_to_bus_;

    std::deque<Stop> stops_;
    std::unordered_map<std::string_view, const Stop*> stopname_to_stop_;

    std::unordered_map<const Stop*, std::set<std::string_view>> stop_to_busnames_;

    std::unordered_map<std::pair<const Stop*, const Stop*>, uint64_t, StopHasher<Stop>> stop_distance_table_;
};

}//namespace transport_catalogue

