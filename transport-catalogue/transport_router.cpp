#include "transport_router.h"

#include <stdexcept>
#include <string>
#include <utility>

namespace transport_catalogue {

    namespace transport_router {

        TransportRouter::TransportRouter(const TransportCatalogue& db)
            : db_(db) {
        }

        void TransportRouter::SetRoutingSettings(const RoutingSettings& settings) {
            settings_ = settings;
        }

        void TransportRouter::BuildRouter() {
            const auto stops{ db_.GetStops() };
            InitGraph(stops.size() * 2);
            for (const auto* stop : stops) {
                const std::string name = stop->name;
                AddWaitEdge(stop->name);
            }
            const auto buses{ db_.GetBuses() };
            for (const auto* bus : buses) {
                for (std::size_t from_index = 0u; from_index + 1u < bus->stops.size(); ++from_index) {
                    std::size_t distance_m = 0u;
                    std::size_t distance_reverse = 0u;
                    for (std::size_t to_index = from_index + 1u; to_index < bus->stops.size(); ++to_index) {
                        distance_m += db_.GetDistanceBetweenStops(bus->stops[to_index - 1u], bus->stops[to_index]);
                        distance_reverse += db_.GetDistanceBetweenStops(bus->stops[bus->stops.size() - to_index], bus->stops[bus->stops.size() - to_index - 1u]);
                        AddBusEdge(
                            transport_router::BusRoute{
                                bus->name,
                                bus->stops[from_index]->name,
                                bus->stops[to_index]->name,
                                distance_m,
                                to_index - from_index
                            }
                        );
                        if (bus->type == domain::BusType::DIRECT) {
                            AddBusEdge(
                                transport_router::BusRoute{
                                    bus->name,
                                    bus->stops[bus->stops.size() - from_index - 1u]->name,
                                    bus->stops[bus->stops.size() - to_index - 1u]->name,
                                    distance_reverse,
                                    to_index - from_index
                                }
                            );
                        }
                    }
                }
            }
            router_.emplace(graph::Router<double>{ graph_.value() });
        }

        void TransportRouter::BuildRouter(
            const std::vector<BusRoute>& bus_routes,
            const std::vector<const domain::Stop*>& stops,
            const std::size_t vertex_count
        ) {
            InitGraph(vertex_count);
            for (const auto stop : stops) {
                AddWaitEdge(stop->name);
            }
            for (const auto& bus_route : bus_routes) {
                AddBusEdge(bus_route);
            }
            router_.emplace(graph::Router<double>{ graph_.value() });
        }

        void TransportRouter::InitGraph(const std::size_t vertex_count) {
            if (!graph_) {
                graph_ = std::move(Graph(vertex_count));
            }
        }

        void TransportRouter::AddWaitEdge(const std::string_view stop_name) {
            if (!stop_name_to_vertex_info_.count(stop_name)) {
                const std::size_t vertex_count = stop_name_to_vertex_info_.size() * 2;
                stop_name_to_vertex_info_[stop_name] = { vertex_count, vertex_count + 1 };
                edge_infos_.push_back(
                    EdgeInfo{
                        Type::Wait,
                        graph::Edge<double>{vertex_count, vertex_count + 1, static_cast<double>(settings_.bus_wait_time_min)},
                        stop_name, stop_name,
                        std::nullopt,
                        0u
                    }
                );
                const auto& edge = edge_infos_.back().edge;
                graph_.value().AddEdge(edge);
            }
        }

        void TransportRouter::AddBusEdge(const BusRoute& bus_route) {
            const graph::VertexId from_id = stop_name_to_vertex_info_[bus_route.from].stop_waiting_id;
            const graph::VertexId to_id = stop_name_to_vertex_info_[bus_route.to].start_waiting_id;
            double weight;
            if (bus_route.weight.has_value()) {
                weight = bus_route.weight.value();
            }
            else {
                weight = bus_route.distance_m / settings_.bus_velocity_kmh * TO_MINUTES;
            }
            edge_infos_.push_back(
                EdgeInfo{
                    Type::Bus,
                    graph::Edge<double>{from_id, to_id, weight},
                    bus_route.from, bus_route.to,
                    bus_route.bus_name,
                    bus_route.span_count
                }
            );
            const auto& edge = edge_infos_.back().edge;
            graph_.value().AddEdge(edge);
        }

        std::optional<domain::RouteStat> TransportRouter::GetRoute(const std::string_view from, const std::string_view to) const {
            const graph::VertexId from_id = stop_name_to_vertex_info_.at(from).start_waiting_id;
            const graph::VertexId to_id = stop_name_to_vertex_info_.at(to).start_waiting_id;
            const auto route_info = router_.value().BuildRoute(from_id, to_id);
            if (!route_info.has_value()) {
                return std::nullopt;
            }
            domain::RouteStat result;
            result.items.reserve(route_info.value().edges.size());
            for (const auto edge_id : route_info.value().edges) {
                const EdgeInfo& edge_info = edge_infos_[edge_id];
                if (edge_info.type == Type::Wait) {
                    result.items.push_back(domain::WaitRouteItem{ edge_info.edge.weight, edge_info.from });
                }
                else {
                    result.items.push_back(domain::BusRouteItem{ edge_info.edge.weight, edge_info.bus_name.value(), edge_info.span_count });
                }
                result.total_time_min += edge_info.edge.weight;
            }
            return result;
        }

        const RoutingSettings& TransportRouter::GetRoutingSettings() const {
            return settings_;
        }

        const std::vector<TransportRouter::EdgeInfo>& TransportRouter::GetEdgeInfos() const {
            return edge_infos_;
        }

    }

}
