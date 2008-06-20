#include <QVariantMap>

Q_DECLARE_METATYPE( Node * )
Q_DECLARE_METATYPE( QList<Node *> )
Q_DECLARE_METATYPE( Tag * )
Q_DECLARE_METATYPE( QList<Tag *> )
Q_DECLARE_METATYPE( Way * )
Q_DECLARE_METATYPE( QList<Way *> )


QVariantMap tagsToQVariantMap( Node* node )
{
    QVariantMap tagsMap;
    QList<Tag *> tags = node->getTags();
    QListIterator<Tag *> i(tags);
    while( i.hasNext() )
    {
        Tag * tag = i.next();
        tagsMap[tag->getKey()] = QVariant(tag->getValue());
    }

    return tagsMap;
}


QScriptValue nodeToScript( QScriptEngine *engine, Node* const & node )
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("latitude", QScriptValue( engine, node->getLatitude() ) );
    obj.setProperty("longitude", QScriptValue( engine, node->getLongitude() ) );
    obj.setProperty("timestamp", QScriptValue( engine, node->getTimestamp() ) );
    obj.setProperty("tags", engine->toScriptValue( tagsToQVariantMap( node ) ) );

    return obj;
}

void nodeFromScript( const QScriptValue &obj, Node* &node )
{
    node->setLatitude( obj.property("latitude").toNumber() );
    node->setLongitude( obj.property("longitude").toNumber() );
    node->setTimestamp( obj.property("timestamp").toString() );
}


QScriptValue wayToScript( QScriptEngine *engine, Way* const & way )
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("timestamp", QScriptValue( engine, way->getTimestamp() ) );;
    return obj;
}

void wayFromScript( const QScriptValue &obj, Way* &way )
{
    way->setTimestamp( obj.property("timestamp").toString() );
}
/*
QScriptValue tagToScript( QScriptEngine *engine, Tag* const & tag )
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("key", QScriptValue( engine, tag->getKey() ) );
    obj.setProperty("value", QScriptValue( engine, tag->getValue() ) );
    return obj;
}

void tagFromScript( const QScriptValue &obj, Tag* &tag )
{
    tag->setKey( obj.property("key").toString() );
    tag->setValue( obj.property("value").toString() );
}
*/
