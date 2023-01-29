#pragma once

#include "transport_catalogue.h"

#include <charconv>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace catalogue {

namespace query {

enum class QueryType {
    StopX,
    BusX
};

struct Command {
    QueryType type;
    std::string name;
    //data
    std::pair<std::string_view, std::string_view> coordinates;
    std::vector<std::pair<std::string_view, std::string_view>> distances;
    std::vector<std::string_view> route;
    TypeRoute route_type = TypeRoute::DIRECT;
    std::string origin_command;
    std::string desc_command;


    std::pair<std::string_view, std::string_view> ParseCoordinates(std::string_view latitude, std::string_view longitude);

    std::vector<std::string_view> ParseBuses(const std::vector<std::string_view>& vec_input);

    std::vector<std::pair<std::string_view, std::string_view>> ParseDistances(std::vector<std::string_view> vec_input);

    void ParseCommandString(const std::string& input);

};

inline std::vector<std::string_view> Split(std::string_view string, char delim);

class InputReader {
public:
    void Load(std::ostream& os, TransportCatalogue& tc);
    void LoadCommand(std::ostream& os, TransportCatalogue& tc, Command com, bool dist);
    void ParseInput(std::istream& input_stream);

private:
    std::vector<Command> commands_;
};

}//namespace query
}//namespace transport_catalogue
