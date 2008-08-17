qtopia_project(qtopia app) # see buildsystem.html for more project keywords
TARGET=citymap
CONFIG+=qtopia_main
CONFIG+=no_singleexec
CONFIG+=no_quicklaunch
CONFIG+=no_tr

FORMS=citymapbase.ui
INCLUDEPATH += ../../mapmodel/ ../../exif/src/ ../../gpsMap/src/ ../../QMapControl/src/


HEADERS=citymap.h \
            ../../exif/src/geofoto.h \
            ../../QMapControl/src/highlightnode.h \
            ../../QMapControl/qmapcontrol.h \
            ../../QMapControl/src/mapcontrol.h \
            ../../QMapControl/src/layermanager.h \
            ../../QMapControl/src/layer.h \
            ../../QMapControl/src/mapadapter.h \
            ../../QMapControl/src/geometry.h \
            ../../QMapControl/src/point.h \
            ../../QMapControl/src/wmsmapadapter.h \
            ../../QMapControl/src/tilemapadapter.h \
            ../../QMapControl/src/imagemanager.h \
            ../../QMapControl/src/mapnetwork.h \
            ../../QMapControl/src/gps_position.h \
            ../../QMapControl/src/imagepoint.h \
            ../../QMapControl/src/circlepoint.h \
            ../../QMapControl/src/linestring.h \
            ../../QMapControl/src/curve.h \
            ../../QMapControl/src/osmmapadapter.h \
            ../../QMapControl/src/maplayer.h \
            ../../QMapControl/src/geometrylayer.h \
            ../../QMapControl/src/yahoomapadapter.h \
            ../../QMapControl/src/googlemapadapter.h \
            ../../QMapControl/src/googlesatmapadapter.h \
            ../../gpsMap/src/gps.h \
            ../../mapmodel/dataInterface.h \
			../../mapmodel/gpx.h \
			../../mapmodel/mapModel.h \
			../../mapmodel/node.h \
			../../mapmodel/osm.h \
			../../mapmodel/relation.h \
			../../mapmodel/tag.h \
			../../mapmodel/way.h

SOURCES=main.cpp citymap.cpp \
            ../../QMapControl/src/highlightnode.cpp \
            ../../QMapControl/src/mapcontrol.cpp \
            ../../QMapControl/src/layermanager.cpp \
            ../../QMapControl/src/layer.cpp \
            ../../QMapControl/src/mapadapter.cpp \
            ../../QMapControl/src/geometry.cpp \
            ../../QMapControl/src/point.cpp \
            ../../QMapControl/src/wmsmapadapter.cpp \
            ../../QMapControl/src/tilemapadapter.cpp \
            ../../QMapControl/src/imagemanager.cpp \
            ../../QMapControl/src/mapnetwork.cpp \
            ../../QMapControl/src/gps_position.cpp \
            ../../QMapControl/src/imagepoint.cpp \
            ../../QMapControl/src/circlepoint.cpp \
            ../../QMapControl/src/linestring.cpp \
            ../../QMapControl/src/curve.cpp \
            ../../QMapControl/src/osmmapadapter.cpp \
            ../../QMapControl/src/maplayer.cpp \
            ../../QMapControl/src/geometrylayer.cpp \
            ../../QMapControl/src/yahoomapadapter.cpp \
            ../../QMapControl/src/googlemapadapter.cpp \
            ../../QMapControl/src/googlesatmapadapter.cpp \
             ../../gpsMap/src/gps.cpp \
            ../../exif/src/geofoto.cpp \
			../../mapmodel/gpx.cpp \
			../../mapmodel/mapModel.cpp \
			../../mapmodel/node.cpp \
			../../mapmodel/osm.cpp \
			../../mapmodel/relation.cpp \
			../../mapmodel/tag.cpp \
			../../mapmodel/way.cpp

desktop.files=citymap.desktop
desktop.path=/apps/Applications
desktop.hint=desktop

pics.files=pics/*
pics.path=/pics/citymap
pics.hint=pics

pkg.domain = qds,CameraService

depends(libraries/qtopiacomm)

help.source=help
help.files=cityMap.html
help.hint=help

INSTALLS+=desktop pics help

pkg.name=cityMap
pkg.desc=cityMap Application
pkg.version=1.0.0-1
pkg.maintainer=Damien RANNOU,,, damunix@gmail.com
pkg.license=GPL
pkg.domain=window
