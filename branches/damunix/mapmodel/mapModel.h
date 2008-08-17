#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QObject>
#include <QDebug>
#include <QList>
#include "node.h"
#include "way.h"
#include "relation.h"
/**
  * class MapModel
  */

class MapModel : public QObject
{
    Q_OBJECT

    private:
        // Private attributes

        QList<Node*> m_nodes;
        QList<Way *> m_ways;
        QList<Relation *> m_relations;

        QString m_name;
        QString m_timestamp;
        double m_maxLat;
        double m_minLat;
        double m_maxLon;
        double m_minLon;

    public:
        MapModel( );
        ~MapModel();
        // Private attribute accessor methods
        //

        /**
        * Set the value of m_name
        * @param name the new value of m_name
        */
        Q_INVOKABLE void setName( QString name ) { m_name = name; };

        /**
        * Get the value of m_name
        * @return the new value of m_name
        */
        Q_INVOKABLE QString getName( ) { return m_name; };

        Q_INVOKABLE void setBounds ( double minLat, double minLon, double maxLat, double maxLon );

        void updateBounds ( );

        //Q_INVOKABLE void setMaxLatitude( double maxLat ) { m_maxLat = maxLat; };
        Q_INVOKABLE double getMaxLatitude( ) { return m_maxLat; };
        Q_INVOKABLE double getMinLatitude( ) { return m_minLat; };
        Q_INVOKABLE double getMaxLongitude( ) { return m_maxLon; };
        Q_INVOKABLE double getMinLongitude( ) { return m_minLon; };

        /**
        * Set the value of m_nodes
        * @param nodes the new value of m_nodes
        */
        void setNodes( QList<Node*> nodes );

        /**
        * Get the value of m_nodes
        * @return the value of m_nodes
        */
        Q_INVOKABLE QList<Node*> getNodes( ) const { return m_nodes; };

        void addNode ( Node* node ) { m_nodes <<  ( node ); };

        void removeNode ( int position  = -1 );


        /**
        * Set the value of m_ways
        * @param ways the new value of m_ways
        */
        void setWays( QList<Way*> ways );

        /**
        * Get the value of m_ways
        * @return the value of m_ways
        */
        Q_INVOKABLE QList<Way *> getWays ( ) const { return m_ways; };

        void addWay (Way* way) { m_ways <<  (way); };

        void removeWay( int position  = -1 );

        /**
        * Set the value of m_relations
        * @param relations the new value of m_relations
        */
        void setRelations( QList<Relation*> relations );

        /**
        * Get the value of m_ways
        * @return the value of m_ways
        */
        QList<Relation *> getRelations ( ) const { return m_relations; };

        void addRelation (Relation* relation) { m_relations <<  (relation); };

        void removeRelation( int position  = -1 );

        /**
         * Set the value of m_timestamp
         * @param time the new value of m_timestamp
        */
        void setTimestamp( QString time )  { m_timestamp = time; };

        /**
        * Get the value of timestamp
        * @return the value of timestamp
        */
        QString getTimestamp() { return m_timestamp; };

};

#endif // MAPMODEL_H
