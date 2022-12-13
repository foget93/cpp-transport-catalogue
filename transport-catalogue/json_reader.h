#pragma once

/*
 * Description: parses JSON data built during parsing and forms an array
 * of JSON responses
 */

#include "json.h"
#include "map_renderer.h"
#include "transport_catalogue.h"
#include "domain.h"



namespace request {

transport_catalogue::TransportCatalogue ProcessBaseRequest(const json::Array& requests);

map_renderer::RenderSettings ParseRenderSettings(const json::Dict& settings);

json::Node MakeStatResponse(transport_catalogue::TransportCatalogue& catalogue, const json::Array& requests,
                            const map_renderer::RenderSettings& settings);

}

/*
{
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
  "stat_requests": [
    { "id": 1, "type": "Stop", "name": "Ривьерский мост" },
    { "id": 2, "type": "Bus", "name": "114" }
  ]
}
*/
