
#include <QtopiaApplication>
#include "src/gpsmap.h"

#include <qtopia/qtopiaapplication.h>


// QTOPIA_ADD_APPLICATION("gpsmap", GPSMap)
// QTOPIA_MAIN

#ifdef Q_WS_QWS
#include <qtopia/qtopiaapplication.h>

QTOPIA_ADD_APPLICATION("gpsmap", GPSMap)
QTOPIA_MAIN
#else

#include <QApplication>
int main(int argc, char *argv[])
{
//    Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    GPSMap gpsmap;
    GPSMap.show();
    return app.exec();
}

#endif