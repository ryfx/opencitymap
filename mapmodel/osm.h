
#ifndef OSM_H
#define OSM_H

#include "node.h"
#include "dataInterface.h"
#include "mapModel.h"
#include "way.h"
#include <QString>
#include <QVariant>
#include <QList>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDateTime>
#include <QMap>
#include <QStringList>

/**
  * class Osm
  */

class Osm: public DataInterface
{
    public:
        // Constructors/Destructors
        Osm( );
        virtual ~Osm();
        // Private attribute accessor methods
        void store( MapModel *model );
        MapModel* load( QString fileName );

    private:
        // Private attributes


        
};

#endif // OSM_H
