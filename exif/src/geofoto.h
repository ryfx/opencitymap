//
// C++ Interface: geofoto
//
// Description: 
//
//
// Author: wolfgang Ostes, wolfostes@hotmail.com>, (C) 20088
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GEOFOTO_H
#define GEOFOTO_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QVariant>
#include <QXmlStreamReader>

/**
	@author wolfgang Ostes,,, <wolfostes@hotmail.com>
*/
class GeoFoto
{
    public:
        GeoFoto(QString);
        bool writeSettings();
        bool readSettings();
        void setLongitude(double);
        void setLatitude(double);
        double getLongitude();
        double getLatitude();
        QString ReadXML(QByteArray ,QString );
        QString getPicture();
        ~GeoFoto();
    private:
        double m_latitude;
        double m_longitude;
        QString m_foto;
        int m_offset;
        QByteArray* binData;

};

#endif
