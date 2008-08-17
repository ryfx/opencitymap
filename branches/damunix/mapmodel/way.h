
#ifndef WAY_H
#define WAY_H

#include "node.h"
#include "tag.h"
#include <QList>
#include <QString>
#include <QDebug>

/**
  * class Way
  */


class Way
{

    public:
        // Constructors/Destructors
        Way( );
        Way( QList<Node*> nodes );
        ~Way();

    private:
        // Private attributes

        QString m_timestamp;
        QList<Node*> m_nodes;
        QList<Tag*> m_tags;

    public:
    
        // Private attribute accessor methods

        /**
        * Set the value of timestamp
        * @param new_var the new value of timestamp
        */
        void setTimestamp( QString time );

        /**
        * Get the value of timestamp
        * @return the value of timestamp
        */
        QString getTimestamp() { return m_timestamp; };

        /**
        * Set the value of nodes
        * @param nodes the new value of nodes
        */
        void setNodes( QList<Node*> nodes );
        
        void addNode (Node* node) { m_nodes << ( node ); };


        /**
        * Get the value of nodes
        * @return the value of nodes
        */
        const QList<Node*> getNodes() const { return m_nodes; };   
        
        void addTag (Tag* tag) { m_tags << ( tag ); };
        
        const QList<Tag*> getTags() const { return m_tags; };   
        
        const QString getTagValue( QString key) const;
};

#endif // WAY_H
