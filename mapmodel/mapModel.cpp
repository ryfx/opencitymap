#include "mapModel.h"


// Constructors/Destructors
//
MapModel::MapModel( )
{

}

MapModel::~MapModel()
{

}
// Private attribute accessor methods
//

/**
 * Set the value of m_nodes
 * @param nodes the new value of m_nodes
 */
void 
MapModel::setNodes ( QList<Node*> nodes ) 
{
    m_nodes = nodes;
}

void 
MapModel::removeNode ( int position )
{
    if ( position < 0 )
        position = m_nodes.size( ) -1;
    if ( position < m_nodes.size( ) )
        m_nodes.removeAt ( position );
}

/**
 * Set the value of m_ways
 * @param ways the new value of m_ways
 */
void 
MapModel::setWays ( QList<Way *> ways ) 
{
    m_ways = ways;
}

void 
MapModel::removeWay ( int position )
{
    if ( position < 0 )
        position = m_ways.size( ) -1;
    if ( position < m_ways.size( ) )
        m_ways.removeAt ( position );
}

/**
 * Set the value of m_relations
 * @param relations the new value of m_relations
 */
void 
MapModel::setRelations ( QList<Relation *> relations ) 
{
    m_relations = relations;
}

void 
MapModel::removeRelation ( int position )
{
    if ( position < 0 )
        position = m_relations.size( ) -1;
    if ( position < m_relations.size( ) )
        m_relations.removeAt ( position );
}

void 
MapModel::setBounds ( double minLat, double minLon, double maxLat, double maxLon )
{
    m_minLat = minLat;
    m_minLon = minLon;
    m_maxLat = maxLat;
    m_maxLon = maxLon;
}

void 
MapModel::updateBounds ( )
{
    double minLat, minLon, maxLat, maxLon;
    
    if (m_nodes.size() > 0)
    {
        minLat = m_nodes[0]->getLatitude();
        minLon = m_nodes[0]->getLongitude();
        maxLat = minLat;
        maxLon = minLon;
        
        for (int i=0; i < m_nodes.size( ); ++i)
        {
            if (m_nodes[i]->getLatitude() < minLat)
                minLat = m_nodes[i]->getLatitude();
                
            if (m_nodes[i]->getLatitude() > maxLat)
                maxLat = m_nodes[i]->getLatitude();
                
            if (m_nodes[i]->getLongitude() < minLon)
                minLon = m_nodes[i]->getLongitude();
                
            if (m_nodes[i]->getLatitude() > maxLon)
                maxLon = m_nodes[i]->getLongitude();
        }
        
        m_minLat = minLat;
        m_minLon = minLon;
        m_maxLat = maxLat;
        m_maxLon = maxLon;
    }
    else
    {
        qDebug() << "There are no nodes";
    }
}

