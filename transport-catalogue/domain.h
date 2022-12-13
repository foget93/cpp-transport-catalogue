#pragma once

#include <string>
#include <vector>

#include "geo.h"

namespace transport_catalogue {

enum class RouteType {
    DIRECT, // -
    CIRCULAR // >
};

struct Stop {
    std::string name;
    geo::Coordinates coordinates;
};

struct Bus {
    std::string number;
    std::vector<const Stop*> stops;
    RouteType type;
};


struct BusStat {
    size_t all_stops {0};
    size_t unique_stops {0};
    double distance {0.};
    uint64_t real_distance {0};
    double curvature {0.};
};

}//namespace transport_catalogue

/*
 * В этом файле вы можете разместить классы/структуры, которые являются частью предметной области (domain)
 * вашего приложения и не зависят от транспортного справочника. Например Автобусные маршруты и Остановки.
 *
 * Их можно было бы разместить и в transport_catalogue.h, однако вынесение их в отдельный
 * заголовочный файл может оказаться полезным, когда дело дойдёт до визуализации карты маршрутов:
 * визуализатор карты (map_renderer) можно будет сделать независящим от транспортного справочника.
 *
 * Если структура вашего приложения не позволяет так сделать, просто оставьте этот файл пустым.
 *
 */
