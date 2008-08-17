#include "relation.h"

// Constructors/Destructors
//
Relation::Relation()
{
    //qDebug() <<"Created new Relation";
}

Relation::~Relation()
{

}

Relation::Relation( QList<Way*> ways)
{
	//qDebug() <<"Created new Relation with "<< ways.size()<< " Ways";
	m_ways = ways;
}
// Private attribute accessor methods
//

const QString 
Relation::getTagValue( QString key) const
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
 * @param new_var the new value of timestamp
 */
void
Relation::setTimestamp ( QString time )
{
    m_timestamp = time;
}

/**
 * Set the value of ways
 * @param ways the new value of ways
 */
void
Relation::setWays ( QList<Way*> ways )
{
    m_ways = ways;
}

