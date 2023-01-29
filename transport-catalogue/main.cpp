#include "json.h"
#include "json_reader.h"
#include "transport_catalogue.h"
#include "request_handler.h"
#include "transport_router.h"
#include <sstream>

using namespace std::literals;
int main() {
	catalogue::TransportCatalogue catalogue;
	catalogue::renderer::MapRenderer map_renderer;
	catalogue::JSONReader json_reader(catalogue, map_renderer);

    std::string str {R"(  {
                     "base_requests": [
                         {
                             "is_roundtrip": true,
                             "name": "297",
                             "stops": [
                                 "Biryulyovo Zapadnoye",
                                 "Biryulyovo Tovarnaya",
                                 "Universam",
                                 "Biryulyovo Zapadnoye"
                             ],
                             "type": "Bus"
                         },
                         {
                             "is_roundtrip": false,
                             "name": "635",
                             "stops": [
                                 "Biryulyovo Tovarnaya",
                                 "Universam",
                                 "Prazhskaya"
                             ],
                             "type": "Bus"
                         },
                         {
                             "latitude": 55.574371,
                             "longitude": 37.6517,
                             "name": "Biryulyovo Zapadnoye",
                             "road_distances": {
                                 "Biryulyovo Tovarnaya": 2600
                             },
                             "type": "Stop"
                         },
                         {
                             "latitude": 55.587655,
                             "longitude": 37.645687,
                             "name": "Universam",
                             "road_distances": {
                                 "Biryulyovo Tovarnaya": 1380,
                                 "Biryulyovo Zapadnoye": 2500,
                                 "Prazhskaya": 4650
                             },
                             "type": "Stop"
                         },
                         {
                             "latitude": 55.592028,
                             "longitude": 37.653656,
                             "name": "Biryulyovo Tovarnaya",
                             "road_distances": {
                                 "Universam": 890
                             },
                             "type": "Stop"
                         },
                         {
                             "latitude": 55.611717,
                             "longitude": 37.603938,
                             "name": "Prazhskaya",
                             "road_distances": {},
                             "type": "Stop"
                         }
                     ],
                     "render_settings": {
                         "bus_label_font_size": 20,
                         "bus_label_offset": [
                             7,
                             15
                         ],
                         "color_palette": [
                             "green",
                             [
                                 255,
                                 160,
                                 0
                             ],
                             "red"
                         ],
                         "height": 200,
                         "line_width": 14,
                         "padding": 30,
                         "stop_label_font_size": 20,
                         "stop_label_offset": [
                             7,
                             -3
                         ],
                         "stop_radius": 5,
                         "underlayer_color": [
                             255,
                             255,
                             255,
                             0.85
                         ],
                         "underlayer_width": 3,
                         "width": 200
                     },
                     "routing_settings": {
                         "bus_velocity": 40,
                         "bus_wait_time": 6
                     },
                     "stat_requests": [
                         {
                             "id": 1,
                             "name": "297",
                             "type": "Bus"
                         },
                         {
                             "id": 2,
                             "name": "635",
                             "type": "Bus"
                         },
                         {
                             "id": 3,
                             "name": "Universam",
                             "type": "Stop"
                         },
                         {
                             "from": "Biryulyovo Zapadnoye",
                             "id": 4,
                             "to": "Universam",
                             "type": "Route"
                         },
                         {
                             "from": "Biryulyovo Zapadnoye",
                             "id": 5,
                             "to": "Prazhskaya",
                             "type": "Route"
                         }
                     ]
                 }
                 )"s}; // "Map"


    std::istringstream sstream{str};

    catalogue::Data data = /*std::move(*/json_reader.ReadJSON(/*std::cin*/sstream);

	catalogue::TransportRouter transport_router(catalogue, data.routing_settings);
	catalogue::RequestHandler request_handler(catalogue, map_renderer, transport_router);
	
	json_reader.BuildDataBase(data);
	transport_router.BuildGraphAndRouter();

    json::Document answers = /*std::move(*/json_reader.GenerateAnswer(transport_router, data.stat_requests);
	json::Print(answers, std::cout);
	
	return 0;
}
