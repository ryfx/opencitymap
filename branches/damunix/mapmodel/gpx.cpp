#include "gpx.h"

// Constructors/Destructors
//
Gpx::Gpx( )
{

}

Gpx::~Gpx()
{

}
// Private attribute accessor methods
//
MapModel* 
Gpx::load ( QString fileName ){
    QList<Node*> m_trackPoints;
    MapModel *new_model = new MapModel( );
    QList<Way*> m_trackWays;
    QXmlStreamReader reader;
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)){
         qDebug( )  << "Error: Cannot read file ";
            //return false
    }
    reader.setDevice(&file);

    if (!reader.atEnd( ))
        reader.readNext( );
    while (!reader.atEnd( )){
        if (reader.isStartElement( ))
        {
            if ((reader.name( ) == "gpx") or (reader.name( ) =="trk") or (reader.name( ) =="name") 
            or (reader.name( ) =="trkseg") or (reader.name( ) =="time")  or (reader.name( ) =="bounds"))
            {
                //qDebug( )<< "StartGPX = "<<reader.name( ).toString( );

                if (reader.name( ) =="time")
                {
                    //qDebug() << "set time: " << reader.readElementText( );
                    new_model->setTimestamp ( reader.readElementText( ) );

                }
                
                if (reader.name( ) =="bounds")
                {
                    new_model->setBounds (reader.attributes( ).value("minlat").toString( ).toDouble( ),
                                     reader.attributes( ).value("minlon").toString( ).toDouble( ),
                                     reader.attributes( ).value("maxlat").toString( ).toDouble( ),
                                     reader.attributes( ).value("maxlon").toString( ).toDouble( ));

                }
                
                if (reader.name( ) =="trkseg")
                {
                    if (!reader.atEnd( ))
                        reader.readNext( );
                    while (!reader.atEnd( ))
                    {
                        //is this element the start of an element?
                        if (reader.isStartElement( ))
                        {
                            if (reader.name( ) =="trkpt")
                            {
                                //add a new node.
                                m_trackPoints << (
                                    new Node(
                                        reader.attributes( ).value("lat").toString( ).toDouble( ),
                                        reader.attributes( ).value("lon").toString( ).toDouble( )));

                                if (!reader.atEnd( ))
                                    reader.readNext( );
                                //do this loop until the end of the file is reached
                                //or untill the end of trkpt is reached (see break).
                                while (!reader.atEnd( )){
                                    if (reader.isStartElement( ))
                                    {
                                        if (reader.name( ) == "ele")
                                        {
                                            //setAltitude
                                            m_trackPoints[m_trackPoints.size( )-1]->setAltitude(reader.readElementText( ).toDouble( ));
                                        }
                                        if (reader.name( ) == "time")
                                        {
                                            //setTimestamp
                                            m_trackPoints[m_trackPoints.size( )-1]->setTimestamp(reader.readElementText( ));
                                        }
                                    }
                                    if (reader.isEndElement( ))
                                    {
                                        if (reader.name( ) == "trkpt")
                                        {
                                            break;
                                        }
                                    }
                                    if (!reader.atEnd( ))
                                        reader.readNext( );
                                }
                            }
                        }
                        //find next element
                        if (!reader.atEnd( ))
                            reader.readNext( );
                    }

                }
                if (!reader.atEnd( ))
                    reader.readNext( );
                if (reader.isStartElement( )){
                    qDebug( )<< "StartGPX2 = "<<reader.name( ).toString( );
                }
            }else{
                qDebug( )<< "Something weird? = "<<reader.name( ).toString( );
                reader.raiseError (QObject::tr("Not a gpx file"));
            }
            if (!reader.atEnd( ))
                reader.readNext( );
        }
        else
        {
            if (!reader.atEnd( ))
                reader.readNext( );
        }
    }

    file.close( );
    if (reader.hasError( ))
    {
        qDebug( ) << "Error: Failed to parse file "<< fileName <<": "<< file.errorString( );
    } 
    else if (file.error( ) != QFile::NoError)
    {
        qDebug( ) << "Error: Cannot read file "<< fileName <<": "<< file.errorString( );
    }
    else 
    {
        m_trackWays << ( new Way(m_trackPoints) );
        new_model->setNodes ( m_trackPoints );
        new_model->setWays( m_trackWays );

        return new_model;
    }

    return 0;
}


void 
Gpx::store ( MapModel *model )
{
    QList<Node*> m_trackPoints;
    QString fileName = model->getName();
    
    for (int i=0; i < model->getWays( ).size( ); ++i)
    {
        m_trackPoints += model->getWays( )[i]->getNodes( );
    }
    qDebug( ) << "Storing " <<m_trackPoints.size( ) << " nodes";
    
    if (model->getName( ).endsWith(".gpx"))
    {

    }
    if ( model->getName( ) == "" )
    {
        QDateTime now = QDateTime::currentDateTime( );
        model->setName( now.toString(STORE_FILE_FORMAT) );
        qDebug( ) << "No fileName was set, setting name to: "<< model->getName( ) << ".gpx";
    }
    
    if (fileName.endsWith(".gpx") == false)
    {
        fileName = fileName + ".gpx";
    }
    QFile file(fileName);
    QXmlStreamWriter xmlWriter(&file);


    if (!file.open(QFile::WriteOnly | QFile::Text)) 
    {
        qDebug( )  << "Error: Cannot write file ";
    }


    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument( );
    xmlWriter.writeStartElement("gpx");
    xmlWriter.writeAttribute( "creator", "Openstreetmap Qtopia cell Phone application");
    xmlWriter.writeAttribute( "version", "1.1");
    xmlWriter.writeNamespace(
        "http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd","schemaLocation");
        
    if ( model->getTimestamp() != "" )
        xmlWriter.writeTextElement("time", model->getTimestamp() );
    model->updateBounds();
    xmlWriter.writeEmptyElement("bounds");
    xmlWriter.writeAttribute( "minlat", ((QVariant)model->getMinLatitude()).toString( ));
    xmlWriter.writeAttribute( "minlon", ((QVariant)model->getMinLongitude()).toString( ));
    xmlWriter.writeAttribute( "maxlat", ((QVariant)model->getMaxLatitude()).toString( ));
    xmlWriter.writeAttribute( "minlon", ((QVariant)model->getMaxLongitude()).toString( ));

    xmlWriter.writeStartElement("trk");
    xmlWriter.writeStartElement("trkseg");

    //Ga alle nodes af
    for (int i=0; i < m_trackPoints.size( ); ++i){

        xmlWriter.writeStartElement("trkpt");
        xmlWriter.writeAttribute( "lat", ((QVariant)m_trackPoints[i]->getLatitude( )).toString( ));
        xmlWriter.writeAttribute( "lon", ((QVariant)m_trackPoints[i]->getLongitude( )).toString( ));
        
        if ( m_trackPoints[i]->getAltitude( ) != 0)
        {
            xmlWriter.writeTextElement("ele", ((QVariant)m_trackPoints[i]->getAltitude( )).toString( ));
        }
                
        if ( m_trackPoints[i]->getTimestamp( ) != "")
        {
            xmlWriter.writeTextElement("time",m_trackPoints[i]->getTimestamp( ));
        }
        xmlWriter.writeEndElement( );

    }

    //sluit alle elementen
    xmlWriter.writeEndDocument( );
    file.close( );
    if (file.error( )) {
        qDebug( )  << "Error: Cannot write file ";
    }
    qDebug( ) << "End store";

}


