
#ifndef RELATION_H
#define RELATION_H

#include "way.h"
#include "tag.h"
#include <QList>
#include <QString>
#include <QDebug>

/**
  * class Relation
  */


class Relation
{

    public:
        // Constructors/Destructors
        Relation( );
        Relation( QList<Way*> ways );
        ~Relation();

    private:
        // Private attributes

        QString m_timestamp;
        QList<Way*> m_ways;
        QList<Tag*> m_tags;

    public:
    
        // Private attribute accessor methods

        /**
        * Set the value of timestamp
        * @param time the new value of timestamp
        */
        void setTimestamp( QString time );

        /**
        * Get the value of timestamp
        * @return the value of timestamp
        */
        QString getTimestamp() { return m_timestamp; };

        /**
        * Set the value of ways
        * @param ways the new value of ways
        */
        void setWays( QList<Way*> ways );
        
        void addWay (Way* way) { m_ways << ( way ); };


        /**
        * Get the value of ways
        * @return the value of ways
        */
        const QList<Way*> getWays() const { return m_ways; };   
        
        void addTag (Tag* tag) { m_tags << ( tag ); };
        
        const QList<Tag*> getTags() const { return m_tags; };   
        
        const QString getTagValue( QString key) const;
};

#endif // RELATION_H
