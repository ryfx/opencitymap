
#ifndef GPSMAP_H
#define GPSMAP_H
#include "ui_gpsmapbase.h"

class gpsMapBase : public QWidget, public Ui_gpsMapBase
{
public:
    gpsMapBase( QWidget *parent = 0, Qt::WFlags f = 0 );
    virtual ~gpsMapBase();
};

#include "libgpsconnector.h"

class gpsMap : public gpsMapBase
{ 
    Q_OBJECT
public:
    gpsMap( QWidget *parent = 0, Qt::WFlags f = 0 );
    virtual ~gpsMap();

private slots:
    void goodBye();
	
private:
	LibGpsConnector* gps;
};

#endif // GPSMAP_H
