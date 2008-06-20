//
// C++ Implementation: geofoto
//
// Description: 
//
//
// Author: wolfgang Ostes, wolfostes@hotmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "geofoto.h"
#include "gpsarray"
GeoFoto::GeoFoto(QString foto)
:m_foto(foto)
{
    QFile file(m_foto);
    if (!file.open(QIODevice::ReadOnly )) {
        qDebug()<<"error reading destination image";
    }
        binData = new QByteArray(file.readAll());
//         qDebug()<<"binData size"<<binData->size();
}
bool GeoFoto::readSettings()
{
//      qDebug()<<"readsettings";
    m_offset=0x14;
    if (binData->size()>0 && binData->at(m_offset)==(char)0xff && binData->at(++m_offset)==(char)0xe1)
    {
//          qDebug()<<"read addres"<<m_offset;
        m_offset += binData->at(++m_offset) * 0x100 + binData->at(m_offset+1);m_offset++;
//         qDebug()<<"new offcet"<<m_offset;
	    if (m_offset==327)
		    m_offset--;
        if (binData->at(m_offset)==(char)0xff && binData->at(m_offset+1)==(char)0xe1)
        {
            m_offset++;
            int metaLength = binData->at(++m_offset) * 0x100 + binData->at(++m_offset);
//             qDebug()<<"metaDat lengte:"<<metaLength;
            QByteArray metaData; 
            for(int loop=0; loop<metaLength;loop++){ // copie the meta data
                if(binData->at(m_offset+loop))
                metaData.append( binData->at(m_offset+loop) );
            }
//             qDebug()<<"metaDat size"<<metaData.size();

            m_latitude = ReadXML(metaData,"<exif:GPSLatitude>").toDouble();
            m_longitude = ReadXML(metaData,"<exif:GPSLongitude>").toDouble();
//             qDebug() <<m_foto<<m_latitude;
            return true;
        }
        else
            qDebug()<<"exifadresfail:"<<m_offset;
    }
    else 
        qDebug()<<"file doesn't exist or no picture";
    return false;
}
QString GeoFoto::ReadXML(QByteArray data,QString xmltag)
{
    int start=data.indexOf(xmltag);
    QString xmtag2=xmltag;
    xmltag.insert(1,"/");
    int end=data.indexOf(xmltag);
//     qDebug()<<"start"<<start<<"einde"<<end;
    return data.mid(start+xmltag.size()-1,end-start-xmltag.size());
}
bool GeoFoto::writeSettings()
{
    int ZERO = 0;
    QByteArray exifData;

    exifData.append(0xFF); // start van de EXIF header
    exifData.append(0xe1);

        QByteArray exif1;
        exif1.append("Exif");
        exif1.append(ZERO);
        exif1.append(ZERO);
            QByteArray exifPart = QByteArray::fromRawData(exifCharList,sizeof(exifCharList));
            qDebug()<<"size exif array"<<exifPart.size();
         exif1.append(exifPart);
    exifData.append((exif1.size()+0x02)/0xff); // add size of the data block
    exifData.append( exif1.size()+0x2);
    exifData.append(exif1);             // add data

    exifData.append ( 0xff); // start van de meta header
    exifData.append ( 0xE1);

        QString metaString; //totale grootte 2955
        metaString.append( "http://ns.adobe.com/xap/1.0/");metaString.append(ZERO);
        static const QChar begindata[3] = { 0xef, 0xbb, 0xbf };
        QString strBegin(begindata, 3);
        metaString.append( "<?xpacket begin='");
        metaString.append( strBegin );
        metaString.append( "' id='W5M0MpCehiHzreSzNTczkc9d'?>\n");
        metaString.append( "<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='Image::ExifTool 7.21'>\n");
        metaString.append( "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>\n\n");
        metaString.append( " <rdf:Description rdf:about=''\n");
        metaString.append( "  xmlns:exif='http://ns.adobe.com/exif/1.0/'>\n");
        metaString.append( "  <exif:GPSLatitude>"); //51,2.791228
        metaString.append(QVariant(m_latitude).toString());
        metaString.append("N</exif:GPSLatitude>\n");
        metaString.append( "  <exif:GPSLongitude>");//4,26.519737E
        metaString.append(QVariant(m_longitude).toString());
        metaString.append( "</exif:GPSLongitude>\n");
        metaString.append( "  <exif:GPSTimeStamp>2008-04-20T17:08:48.70Z</exif:GPSTimeStamp>\n");
        metaString.append( " </rdf:Description>\n");
        metaString.append( "</rdf:RDF>\n");
        metaString.append( "</x:xmpmeta>\n");
        metaString.append( "<?xpacket end='w'?>");
//         qDebug()<<"meta size "<<metaString.size();

    exifData.append((metaString.size()+0x02)/0xff); // size of the data block
    exifData.append( metaString.size()+0x02);
    exifData.append( metaString);

    if (binData->size()>0)
    {
        binData->insert(0x14,exifData);
        //     qDebug()<<"Write data to file:"<<binData->size();
        QFile file(m_foto);
        if (!file.open(QIODevice::ReadWrite ))
        {
            qDebug()<<"error reading file";
            return false;
        }
        file.write(*binData);
        file.close();
        delete binData;
        return true;
    }
    qDebug()<<"error empty";
    return false;
}
void GeoFoto::setLongitude(double lon)
{
    m_longitude = lon;
}
void GeoFoto::setLatitude(double lat)
{
    m_latitude = lat;
}
double GeoFoto::getLongitude()
{
    return m_longitude;
}
double GeoFoto::getLatitude()
{
    return m_latitude;
}
QString GeoFoto::getPicture() 
{
    return m_foto;
}

GeoFoto::~GeoFoto()
{
}


