#include "stat_reader.h"

#include <iomanip>
#include <iostream>
#include <set>

using namespace std;

namespace transport_catalogue {

namespace output {

void OutputRouteAbout(std::ostream& os, TransportCatalogue& tc, std::string_view route) {
    if (tc.GetRoute(route) == nullptr) {
        os << "Bus "s << route << ": not found"s << endl;
    }
    else {
        BusStat stat = tc.GetStatistics(tc.GetRoute(route));

        os << "Bus "s << route << ": "s << stat.all_stops
            << " stops on route, "s << stat.unique_stops
            << " unique stops, "s << std::setprecision(6)
            << stat.real_distance << " route length, "s
            << std::setprecision(6) << stat.curvature
            << " curvature"s << endl;
    }
}

void OutputStopAbout(std::ostream& os, TransportCatalogue& tc, string_view name) {
    //bool flag = tc.GetStop(name) != nullptr;
    set<string_view> buses = tc.GetBuses(name);

    if (tc.GetStop(name) != nullptr) {
        if (buses.size() == 0) {
            os << "Stop "s << name << ": no buses"s << endl;
        }
        else {
            os << "Stop "s << name << ": buses "s;
            for (auto it = buses.begin(); it != buses.end(); ++it) {
                if (next(it) != buses.end()) {
                    os << (*it) << " "s;
                }
                else {
                    os << (*it);
                }
            }
            os << endl;
        }
    }
    else {
        os << "Stop "s << name << ": not found"s << endl;
    }
}

void OutputAbout(std::ostream& os, TransportCatalogue& tc, query::Command com) {
    if (com.type == query::QueryType::StopX) {
        OutputStopAbout(os, tc, com.name);
    }

    if (com.type == query::QueryType::BusX) {
        OutputRouteAbout(os, tc, com.name);
    }
} //ne ispolz

}//namespace output
}//namespace transport_catalogue
