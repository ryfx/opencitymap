SOURCES += exif.cpp \
           main.cpp \
 geofoto.cpp
HEADERS += exif.h \
 geofoto.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/exif

