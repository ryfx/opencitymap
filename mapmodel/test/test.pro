
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = mapmodeltest

INCLUDEPATH += ../
LIBS        += ../libmapmodel.a


QT += xml
QT += script
SOURCES += main.cpp scriptConversion.cpp
RESOURCES += gamescript.qrc
