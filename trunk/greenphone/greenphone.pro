qtopia_project(qtopia app)
TARGET =greenphone
INCLUDEPATH += ../mapmodel/ ../exif/src/ ../gpsMap/src/ 
LIBS += ../mapmodel/libmapmodel.a
QT += script

# Input
HEADERS +=  src/citymap.h \
            ../exif/src/geofoto.h \
            src/dialogs.h \
            src/featurecontainer.h \
            src/featurename.h \
            src/mapfeature.h \
            src/streetwidget.h \
            src/tagdialog.h \
            src/loadscreen.h \
            src/script.h \
            ../QMapControl/src/highlightnode.h \
            ../QMapControl/qmapcontrol.h \
            ../QMapControl/src/mapcontrol.h \
            ../QMapControl/src/layermanager.h \
            ../QMapControl/src/layer.h \
            ../QMapControl/src/mapadapter.h \
            ../QMapControl/src/geometry.h \
            ../QMapControl/src/point.h \
            ../QMapControl/src/wmsmapadapter.h \
            ../QMapControl/src/tilemapadapter.h \
            ../QMapControl/src/imagemanager.h \
            ../QMapControl/src/mapnetwork.h \
            ../QMapControl/src/gps_position.h \
            ../QMapControl/src/imagepoint.h \
            ../QMapControl/src/circlepoint.h \
            ../QMapControl/src/linestring.h \
            ../QMapControl/src/curve.h \
            ../QMapControl/src/osmmapadapter.h \
            ../QMapControl/src/maplayer.h \
            ../QMapControl/src/geometrylayer.h \
            ../QMapControl/src/yahoomapadapter.h \
            ../QMapControl/src/googlemapadapter.h \
            ../QMapControl/src/googlesatmapadapter.h \
            ../gpsMap/src/gps.h \
        
FORMS += ui/streetwidget.ui ui/tagdialog.ui ui/loadscreenwidget.ui
SOURCES +=  src/citymap.cpp \
            src/dialogs.cpp \
            src/featurecontainer.cpp \
            src/featurename.cpp \
            src/main.cpp \
            src/mapfeature.cpp \
            src/streetwidget.cpp \
            src/tagdialog.cpp \
            src/loadscreen.cpp \
            src/script.cpp \
            ../QMapControl/src/highlightnode.cpp \
            ../QMapControl/src/mapcontrol.cpp \
            ../QMapControl/src/layermanager.cpp \
            ../QMapControl/src/layer.cpp \
            ../QMapControl/src/mapadapter.cpp \
            ../QMapControl/src/geometry.cpp \
            ../QMapControl/src/point.cpp \
            ../QMapControl/src/wmsmapadapter.cpp \
            ../QMapControl/src/tilemapadapter.cpp \
            ../QMapControl/src/imagemanager.cpp \
            ../QMapControl/src/mapnetwork.cpp \
            ../QMapControl/src/gps_position.cpp \
            ../QMapControl/src/imagepoint.cpp \
            ../QMapControl/src/circlepoint.cpp \
            ../QMapControl/src/linestring.cpp \
            ../QMapControl/src/curve.cpp \
            ../QMapControl/src/osmmapadapter.cpp \
            ../QMapControl/src/maplayer.cpp \
            ../QMapControl/src/geometrylayer.cpp \
            ../QMapControl/src/yahoomapadapter.cpp \
            ../QMapControl/src/googlemapadapter.cpp \
            ../QMapControl/src/googlesatmapadapter.cpp \
             ../gpsMap/src/gps.cpp \
            ../exif/src/geofoto.cpp \
        

TRANSLATIONS += greenphone-de.ts greenphone-ko.ts

RESOURCES = images/application.qrc \

# SXE permissions required
pkg.domain = qds,CameraService


depends(libraries/qtopiacomm)

pics.files=pics/*
pics.path=/pics/greenphoto
pics.hint=pics

