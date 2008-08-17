
#include "citymap.h"
#include <qpushbutton.h>

cityMapBase::cityMapBase( QWidget *parent, Qt::WFlags f )
    : QWidget( parent, f )
{
    setupUi( this );
    
}

cityMapBase::~cityMapBase()
{
}

/* 
 *  Constructs a cityMap which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
cityMap::cityMap( QWidget *parent, Qt::WFlags f )
    : cityMapBase( parent, f )
{
    //initialisation of the MapControl (size, etc)
	mc->show();
    mc->init();
	
    //connection of buttons signal
    connect(zoomInButton,SIGNAL(clicked()),mc,SLOT(zoomIn()));
    connect(zoomOutButton,SIGNAL(clicked()),mc,SLOT(zoomOut()));
	
	// we will construct everything when the mc whill be display
	connect(mc,SIGNAL(mcReady()),this,SLOT(construct()));

}

/*  
 *  Destroys the object and frees any allocated resources
 */
cityMap::~cityMap()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  A simple slot... not very interesting.
 */
void cityMap::goodBye()
{
    close();
}

void cityMap::construct()
{
	_highlightnode = new HighLightNode();
	mc->setHighLightNode(_highlightnode);

	mapadapter = new OSMMapAdapter();
	_highlightnode->setMapAdapter(mapadapter);
    // create a layer with the mapadapter and type MapLayer
	l = new MapLayer("Custom Layer", mapadapter);
	mc->addLayer(l);

	roads = new GeometryLayer("roads", mapadapter);
	mc->addLayer(roads);

	mapTags = new GeometryLayer("mapTags", mapadapter);
	mc->addLayer(mapTags);

	penWay = new QPen(QColor(0x0,0x0,0xff,100));
	penWay->setWidth(5);
    
	gpxFile= new Gpx();
	osmFile= new Osm();
	mapmodel = osmFile->load( "/mnt/documents/hogeweg.osm" );
	QList<Way*> listway =   mapmodel->getWays();
	QList<Node*> listnode =   mapmodel->getNodes();

    //define position
	double x = 4.47;
	double y = 51.02;
	
	mc->setView(QPointF(x,y));
	mc->setZoom(8);
	mc->show();
}
