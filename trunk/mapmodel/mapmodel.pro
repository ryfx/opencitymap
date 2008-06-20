TEMPLATE = lib
CONFIG += staticlib
TARGET = mapmodel
QT += core 
QT += xml

# Input
HEADERS += dataInterface.h gpx.h osm.h mapModel.h node.h tag.h way.h relation.h
SOURCES += gpx.cpp osm.cpp mapModel.cpp node.cpp tag.cpp way.cpp relation.cpp
