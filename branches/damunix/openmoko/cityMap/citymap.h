
#ifndef CITYMAP_H
#define CITYMAP_H
#include "mapcontrol.h"
using namespace qmapcontrol;
#include "ui_citymapbase.h"

class cityMapBase : public QWidget, public Ui_cityMapBase
{
public:
    cityMapBase( QWidget *parent = 0, Qt::WFlags f = 0 );
    virtual ~cityMapBase();
};


#include "highlightnode.h"
#include "mapadapter.h"
#include "maplayer.h"
#include "geometrylayer.h"

#include "mapModel.h"
#include "dataInterface.h"
#include "gpx.h"
#include "osm.h"
				 
class cityMap : public cityMapBase
{ 
    Q_OBJECT
public:
    cityMap( QWidget *parent = 0, Qt::WFlags f = 0 );
    virtual ~cityMap();

private slots:
    void goodBye();
	void construct();
private:
   HighLightNode* _highlightnode;
   MapAdapter* mapadapter;

    Layer* l;
    Layer* roads;
    Layer* mapTags;


    QPen* penWay;
    Gpx* gpxFile;
    Osm* osmFile;
    MapModel* mapmodel;

};

#endif // CITYMAP_H
