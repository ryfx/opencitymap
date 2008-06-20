

#include <QtGui>
#include "gpsmap.h"


GPSMap::GPSMap(QWidget *parent, Qt::WFlags f)
 : QWidget(parent, f)//:  QMainWindow( parent, f )
{
    setupUi( this );
    connect(quit, SIGNAL(clicked()), this, SLOT(goodBye()));

    
    gpsTomTom = new GPS();
     gpsTomTom->fake(false);
    connect(gpsTomTom, SIGNAL(new_position(QPointF)),
              this, SLOT(tick(QPointF)));
//     GPSMap::tick();
}

void GPSMap::tick(QPointF p)
{
//     gpsTomTom->updatePosition(); 
    QVariant y = gpsTomTom->getLatitude();
    QVariant x = gpsTomTom->getLongitude();
    QVariant h = gpsTomTom->getAltitude();
//     QVariant s = gpsTomTom->getSatellites();
    longitude->setText(y.toString());
    latitude->setText(x.toString());
    altitude->setText(h.toString());
//     satellites->setText(s.toString());

}
GPSMap::~GPSMap()
{

}
void GPSMap::goodBye()
{
//     gpsTomTom->gpsDisconnect();
    close();
}

