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
        request_handler.cpp \
        stat_reader.cpp \
        transport_catalogue.cpp \
        json.cpp

HEADERS += \
    domain.h \
    geo.h \
    input_reader.h \
    json_reader.h \
    request_handler.h \
    stat_reader.h \
    transport_catalogue.h \
    json.h
