
#ifndef NODE_H
#define NODE_H

#include "tag.h"
#include <QList>
#include <QString>

/**
  * class Node
  */
class Node
{

    private:
        // Private attributes
        double m_latitude;
        double m_longitude;
        double m_altitude;
        QString m_timestamp;
        QList<Tag*> m_tags;

    public:
        Node( );
        Node( double lat, double lon, double alt, QString time );
        Node( double lat, double lon, QString time );
        Node( double lat, double lon );
        ~Node();
        // Private attribute accessor methods

        void addTag ( Tag* tag ) { m_tags << ( tag ); };

        const QList<Tag*> getTags() const { return m_tags; };
        
        const QString getTagValue( QString key) const;

        /**
         * Set the value of m_latitude
         * @param lat the new value of m_latitude
        */
        void setLatitude( double lat );

        /**
         * Get the value of m_latitude
         * @return the value of m_latitude
        */
        double getLatitude( ) const;


        /**
         * Set the value of m_longitude
         * @param lon the new value of m_longitude
        */
        void setLongitude( double lon );

        /**
         * Get the value of m_longitude
         * @return the value of m_longitude
        */
        double getLongitude( ) const;


        /**
         * Set the value of m_altitude
         * @param alt the new value of m_altitude
        */
        void setAltitude( double alt );

        /**
         * Get the value of m_altitude
         * @return the value of m_altitude
        */
        double getAltitude( );


        /**
         * Set the value of m_timestamp
         * @param time the new value of m_timestamp
        */
        void setTimestamp( QString time );

        /**
         * Get the value of m_timestamp
         * @return the value of m_timestamp
        */
        QString getTimestamp( );


};

#endif // NODE_H
