qtopia_project(qtopia app)# see buildsystem.html for more project keywords
TARGET =gpsmap
CONFIG+=qtopia_main
CONFIG+=no_singleexec
CONFIG+=no_quicklaunch
CONFIG+=no_tr

INCLUDEPATH += src/ 

DEFINES += PATH_MAX=255
LIBS += -lgps

FORMS =gpsmapbase.ui
HEADERS =gpsmap.h \
src/gpsGen.h \
src/libgpsconnector.h

SOURCES =main.cpp gpsmap.cpp \
src/gps.cpp \
src/libgpsconnector.cpp

desktop.files =gpsmap.desktop
desktop.path =/apps/Applications
desktop.hint =desktop

pics.files =pics/*
pics.path =/pics/gpsmap
pics.hint =pics

help.source =help
help.files =gpsMap.html
help.hint =help

INSTALLS+=desktop pics help

pkg.name =gpsMap
pkg.desc =gpsMap Application
pkg.version =1.0.0-1
pkg.maintainer =Damien RANNOU,,, damunix@gmail.com
pkg.license =GPL
pkg.domain =window
