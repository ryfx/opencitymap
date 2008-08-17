
#ifndef GPX_H
#define GPX_H

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


/**
  * class Gpx
  */

class Gpx: public DataInterface
{
    public:
        // Constructors/Destructors
        Gpx( );
        virtual ~Gpx();
        // Private attribute accessor methods
        void store( MapModel *model );
        MapModel* load( QString fileName );
        

    private:
        // Private attributes
        
};

#endif // GPX_H
