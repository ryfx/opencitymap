#include "tag.h"

// Constructors/Destructors
//  
Tag::Tag( )
{

}

Tag::~Tag()
{

}

Tag::Tag( QString key, QString value )
{
    //qDebug() << "Add tag: key=" << key << ", value=" << value;
    m_key = key;
    m_value = value;
}

// Private attribute accessor methods
//  

/**
 * Set the value of key
 * @param key the new value of key
 */
void 
Tag::setKey( QString key ) {
    m_key = key;
}

/**
 * Get the value of key
 * @return the value of key
 */
QString 
Tag::getKey( ) {
    return m_key;
}

/**
 * Set the value of value
 * @param value the new value of value
 */
void 
Tag::setValue( QString value ) {
    m_value = value;
}

/**
 * Get the value of value
 * @return the value of value
 */
QString 
Tag::getValue( ) {
    return m_value;
}

