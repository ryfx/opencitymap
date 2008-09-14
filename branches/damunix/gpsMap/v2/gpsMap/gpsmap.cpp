
#include "gpsmap.h"
#include <qpushbutton.h>

gpsMapBase::gpsMapBase( QWidget *parent, Qt::WFlags f )
    : QWidget( parent, f )
{
    setupUi( this );
}

gpsMapBase::~gpsMapBase()
{
}

/* 
 *  Constructs a gpsMap which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
gpsMap::gpsMap( QWidget *parent, Qt::WFlags f )
    : gpsMapBase( parent, f )
{
    connect(quit, SIGNAL(clicked()), this, SLOT(goodBye()));
	gps = new LibGpsConnector();
	gps->start();
	qDebug ("Gps online ? %d",gps->isOnline());
}

/*  
 *  Destroys the object and frees any allocated resources
 */
gpsMap::~gpsMap()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  A simple slot... not very interesting.
 */
void gpsMap::goodBye()
{
    close();
}

