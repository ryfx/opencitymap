

#include <QApplication>
#include "geofoto.h"

int main()
{
//       Q_INIT_RESOURCE(application);
    qDebug()<<"start prog";
 
//     system("cp photo/greenphone.jpeg test/testfoto.jpeg");

GeoFoto foto("test/fotolow.jpeg");
    foto.setLatitude(51.022024);
    foto.setLongitude(4.473872);
    
    foto.writeSettings();

    GeoFoto fotoRead("test/fotolow.jpeg");
    fotoRead.readSettings();

    qDebug()<<"lat"<<fotoRead.getLatitude();
    qDebug()<<"longitude"<<fotoRead.getLongitude();
}
/*
 GeoFoto foto("test/brusselpoort.jpeg");
    foto.setLatitude(51.022024);
    foto.setLongitude(4.473872);*/

//  GeoFoto foto("test/kraanbrug.jpeg");
//     foto.setLatitude(51.02714);
//     foto.setLongitude(4.474857);

// GeoFoto foto("test/grotemarkt.jpg");
//     foto.setLatitude(51.028136);
//     foto.setLongitude(4.480399);