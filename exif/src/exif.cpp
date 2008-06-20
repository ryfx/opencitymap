

#include <QtGui>
#include "exif.h"
#include "gpsarray"
#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QIODevice>

exif::exif()
{
    int ZERO=0;

    // kopieer file voor te testen
    QFile file2("greenphone.jpeg");
    
    if (!file2.open(QIODevice::ReadOnly ))
        qDebug()<<"error reading file";
    QByteArray binData = file2.readAll();
    file2.close();

    // open jpg tekening en plaats de GPS data erin
    QFile file("imageTest44.jpeg");
    if (!file.open(QIODevice::ReadWrite ))
        qDebug()<<"error reading destination image";
    
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
        metaString.append( "  <exif:GPSLatitude>51,2.791228N</exif:GPSLatitude>\n");
        metaString.append( "  <exif:GPSLongitude>4,26.519737E</exif:GPSLongitude>\n");
        metaString.append( "  <exif:GPSTimeStamp>2008-04-20T17:08:48.70Z</exif:GPSTimeStamp>\n");
        metaString.append( " </rdf:Description>\n");
        metaString.append( "</rdf:RDF>\n");
        metaString.append( "</x:xmpmeta>\n");
        metaString.append( "<?xpacket end='w'?>");
        qDebug()<<"meta size "<<metaString.size();

    exifData.append((metaString.size()+0x02)/0xff); // size of the data block
    exifData.append( metaString.size()+0x02);
    exifData.append( metaString);

    binData.insert(0x14,exifData);
    file.write(binData);
}

