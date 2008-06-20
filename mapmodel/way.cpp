#include "way.h"

// Constructors/Destructors
//
Way::Way()
{
    //qDebug() <<"Created new Way";
}

Way::~Way()
{

}
	
Way::Way( QList<Node*> nodes)
{
	//qDebug() <<"Created new Way with "<< nodes.size()<< " Nodes";
	m_nodes = nodes;
}
// Private attribute accessor methods
//

const QString 
Way::getTagValue( QString key) const
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
 * Set the value of timestamp
 * @param time the new value of timestamp
 */
void
Way::setTimestamp ( QString time )
{
    m_timestamp = time;
}

/**
 * Set the value of nodes
 * @param nodes the new value of nodes
 */
void
Way::setNodes ( QList<Node*> nodes )
{
    m_nodes = nodes;
}

