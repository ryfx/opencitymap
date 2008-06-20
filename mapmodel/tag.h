#ifndef TAG_H
#define TAG_H

#include <QString>
#include <QDebug>

/**
  * class Tag
  */

class Tag
{
    public:
        Tag( );
        Tag( QString key, QString value );
        ~Tag();
        /**
         * Set the value of key
         * @param key the new value of key
        */
        void setKey( QString key );

        /**
         * Get the value of key
         * @return the value of key
        */
        QString getKey( );


        /**
         * Set the value of value
         * @param value the new value of value
        */
        void setValue( QString value );

        /**
         * Get the value of value
         * @return the value of value
        */
        QString getValue( );

    private:
        // Private attributes
        //
        QString m_key;
        QString m_value;

};

#endif // TAG_H
