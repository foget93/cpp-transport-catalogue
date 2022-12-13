TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        domain.cpp \
        geo.cpp \
        input_reader.cpp \
        json_reader.cpp \
        main.cpp \
        map_renderer.cpp \
        request_handler.cpp \
        stat_reader.cpp \
        svg.cpp \
        transport_catalogue.cpp \
        json.cpp

HEADERS += \
    domain.h \
    geo.h \
    input_reader.h \
    json_reader.h \
    map_renderer.h \
    request_handler.h \
    stat_reader.h \
    svg.h \
    transport_catalogue.h \
    json.h
