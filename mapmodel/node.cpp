#include "node.h"
#include <QDebug>
// Constructors/Destructors
//

Node::Node( )
{
    m_latitude = 0;
    m_longitude = 0;
    m_altitude = 0;
}

Node::~Node()
{

}

Node::Node( double lat, double lon )
{

    m_latitude = lat;
    m_longitude = lon;
    m_altitude = 0;
}

Node::Node( double lat, double lon, double alt, QString time )
{
    m_latitude = lat;
    m_longitude = lon;
    m_altitude = alt;
    m_timestamp = time;
}

Node::Node( double lat, double lon, QString time )
{

    m_latitude = lat;
    m_longitude = lon;
    m_timestamp = time;
    m_altitude = 0;
}
//
// Methods
//


// Private attribute accessor methods
//


const QString 
Node::getTagValue( QString key) const
{
    for (int i=0; i < m_tags.size( ); ++i)
    {
        if (m_tags[i]->getKey() == key)
        {
            return m_tags[i]->getValue();
        }
    }
    
    return 0;
}

/**
 * Set the value of latitude
 * @param lat the new value of latitude
 */
void
Node::setLatitude( double lat ) 
{
    m_latitude = lat;
}

/**
 * Get the value of latitude
 * @return the value of latitude
 */
double
Node::getLatitude( ) const
{
    return m_latitude;
}

/**
 * Set the value of longitude
 * @param lon the new value of longitude
 */
void
Node::setLongitude( double lon ) {
    m_longitude = lon;
}

/**
 * Get the value of longitude
 * @return the value of longitude
 */
double
Node::getLongitude( ) const
{
    return m_longitude;
}

/**
 * Set the value of altitude
 * @param alt the new value of altitude
 */
void
Node::setAltitude( double alt ) {
    m_altitude = alt;
}

/**
 * Get the value of altitude
 * @return the value of altitude
 */
double
Node::getAltitude( ) {
    return m_altitude;
}

/**
 * Set the value of timestamp
 * @param time the new value of timestamp
 */
void
Node::setTimestamp( QString time ) {
    m_timestamp = time;
}

/**
 * Get the value of timestamp
 * @return the value of timestamp
 */
QString
Node::getTimestamp ( ) {
    return m_timestamp;
}



