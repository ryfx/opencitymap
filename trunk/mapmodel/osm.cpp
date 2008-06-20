#include "osm.h"

// Constructors/Destructors
//
Osm::Osm( )
{

}

Osm::~Osm()
{

}
// Private attribute accessor methods
//
MapModel*
Osm::load ( QString fileName ){

    MapModel *new_model = new MapModel( );
    QList<Node*> m_trackPoints;
    QList<Way*> m_trackWays;
    QList<Way*> m_trackRelations;
    QXmlStreamReader reader;
    QFile file(fileName);

    QMap<long, Node*> mapNode;
    QMap<long, Way*> mapWay;
    QMap<long, Relation*> mapRelation;
    long nodeId;
    long wayId;
    long relationId;
    QStringList idShop;

    if (!file.open(QFile::ReadOnly | QFile::Text)){
         qDebug( )  << "Error: Cannot read file ";
            //return false
    }
    reader.setDevice(&file);

    new_model->setName ( fileName );
    reader.readNext( );
    while (!reader.atEnd( ))
    {
        if (reader.isStartElement( ))
        {
            if ((reader.name( ) == "osm"))
            {
                
                qDebug( )<< "Start osm = "<<reader.name( ).toString( );
                if (!reader.atEnd( ))
                    reader.readNext( );
                while (!reader.atEnd( ))
                {                
                    if (reader.isStartElement( ))
                    {
                        // Read bound
                        if ((reader.name( ) == "bound"))
                        {
                            
                            //qDebug( )<< "Start bound = "<< reader.attributes( ).value("box").toString( );
                            //new_model->setBounds (reader.attributes( ).value("minlat").toString( ).toDouble( ),
                            //                 reader.attributes( ).value("minlon").toString( ).toDouble( ),
                            //                 reader.attributes( ).value("maxlat").toString( ).toDouble( ),
                            //                 reader.attributes( ).value("maxlon").toString( ).toDouble( ));
                            
                        }
                        
                        // Read node
                        if (reader.name( ) == "node")
                        {
                            if  (reader.attributes( ).value("id").toString().startsWith("new_") )
                            {
                                nodeId = (-1) * reader.attributes( ).value("id").toString().split("new_")[1].toLong();
                                mapNode[nodeId] = new Node(
                                        reader.attributes( ).value("lat").toString( ).toDouble( ),
                                        reader.attributes( ).value("lon").toString( ).toDouble( ),
                                        reader.attributes( ).value("timestamp").toString( ));
                            }
                            else
                            {
                                nodeId = reader.attributes( ).value("id").toString( ).toLong( );
                                mapNode[nodeId] = new Node(
                                        reader.attributes( ).value("lat").toString( ).toDouble( ),
                                        reader.attributes( ).value("lon").toString( ).toDouble( ),
                                        reader.attributes( ).value("timestamp").toString( ));
                                mapNode[nodeId]->addTag( new Tag (
                                    "osmId", reader.attributes( ).value("id").toString( )));
                            }
                            if (!reader.atEnd( ))
                                reader.readNext( );
                            while (!reader.atEnd( ))
                            {
                                if (reader.isStartElement( ))
                                {
                                    if (reader.name( ) == "tag")
                                    {
                                        mapNode[nodeId]->addTag( new Tag (
                                            reader.attributes( ).value("k").toString( ),
                                            reader.attributes( ).value("v").toString( )));
                                    }
                                }
                                if (reader.isEndElement( ))
                                {
                                    if (reader.name( ) == "node")
                                    {
                                        //qDebug() << "Added " << mapNode[nodeId]->getTags().size() << " Tags to way";
                                        break;
                                    }
                                }
                                if (!reader.atEnd( ))
                                    reader.readNext( );
                            }

                        }

                        // Read way
                        if (reader.name( ) == "way")
                        {
                        
                            if  (reader.attributes( ).value("id").toString().startsWith("new_") )
                            {
                                wayId = (-1) * reader.attributes( ).value("id").toString().split("new_")[1].toLong();
                                mapWay[wayId] = new Way( );
                                mapWay[wayId]->setTimestamp( reader.attributes( ).value("timestamp").toString( ) );

                            }
                            else
                            {
                                wayId = reader.attributes( ).value("id").toString( ).toLong( );
                                mapWay[wayId] = new Way( );
                                mapWay[wayId]->setTimestamp( reader.attributes( ).value("timestamp").toString( ) );
                                mapWay[wayId]->addTag( new Tag (
                                    "osmId", reader.attributes( ).value("id").toString( )));
                            }
                                
                            reader.readNext( );
                            while (!reader.atEnd( ))
                            {
                                if (reader.isStartElement( ))
                                {
                                    if (reader.name( ) == "nd")
                                    {
                                        if (reader.attributes( ).value("ref").toString().startsWith("new_") )
                                        {
                                            if (mapNode.contains((-1) * reader.attributes( ).value("ref").toString( ).split("new_")[1].toLong( )))
                                            {
                                                mapWay[wayId]->addNode ( 
                                                mapNode[(-1) * reader.attributes( ).value("ref").toString( ).split("new_")[1].toLong( )]);
                                            }
                                        }
                                        else
                                        {
                                            if (mapNode.contains(reader.attributes( ).value("ref").toString( ).toLong( )))
                                                mapWay[wayId]->addNode ( mapNode[reader.attributes( ).value("ref").toString( ).toLong( )] );
                                        }
                                    }
                                    if (reader.name( ) == "tag")
                                    {
                                        mapWay[wayId]->addTag( new Tag (
                                        reader.attributes( ).value("k").toString( ),
                                        reader.attributes( ).value("v").toString( )));
                                    }
                                    
                                }
                                if (reader.isEndElement( ))
                                {
                                    if (reader.name( ) == "way")
                                    {
                                        //qDebug() << "Added " << mapWay[wayId]->getNodes().size() << " Nodes to way";
                                        //qDebug() << "Added " << mapWay[wayId]->getTags().size() << " Tags to way";
                                        break;
                                    }
                                }
                                reader.readNext( );
                            }
                        }

                        // Read relation
                        if (reader.name( ) == "relation")
                        {                  
                            if  (reader.attributes( ).value("id").toString().startsWith("new_") )
                            {
                                relationId = (-1) * reader.attributes( ).value("id").toString().split("new_")[1].toLong();
                                relationId = reader.attributes( ).value("id").toString( ).toLong( );
                                mapRelation[relationId] = new Relation( );
                                mapRelation[relationId]->setTimestamp( reader.attributes( ).value("timestamp").toString( ) );
                                mapRelation[relationId]->addTag( new Tag (
                                    "osmId", reader.attributes( ).value("id").toString( )));
                            }
                            else
                            {
                                relationId = reader.attributes( ).value("id").toString( ).toLong( );
                                mapRelation[relationId] = new Relation( );
                                mapRelation[relationId]->setTimestamp( reader.attributes( ).value("timestamp").toString( ) );
                                mapRelation[relationId]->addTag( new Tag (
                                    "osmId", reader.attributes( ).value("id").toString( )));
                            }

                            reader.readNext( );
                            while (!reader.atEnd( ))
                            {
                                if (reader.isStartElement( ))
                                {
                                    if (reader.name( ) == "member")
                                    {
                                    
                                        if (reader.attributes( ).value("type").toString( ) == "way")
                                        {
                                            if (reader.attributes( ).value("ref").toString().startsWith("new_") )
                                            {
                                                if (mapWay.contains((-1) * reader.attributes( ).value("ref").toString( ).split("new_")[1].toLong( )))
                                                    mapRelation[relationId]->addWay ( mapWay[(-1) * reader.attributes( ).value("ref").toString( ).split("new_")[1].toLong( )]);
                                            }
                                            else
                                            {
                                                if (mapWay.contains(reader.attributes( ).value("ref").toString( ).toLong( )))
                                                    mapRelation[relationId]->addWay (
                                                    mapWay[reader.attributes( ).value("ref").toString( ).toLong( )] );
                                            }
                                        }

                                    }
                                    if (reader.name( ) == "tag")
                                    {
                                        mapRelation[relationId]->addTag( new Tag (
                                        reader.attributes( ).value("k").toString( ),
                                        reader.attributes( ).value("v").toString( )));
                                    }
                                }
                                if (reader.isEndElement( ))
                                {
                                    if (reader.name( ) == "relation")
                                    {
                                        //qDebug() << "Added " << mapRelation[relationId]->getWays().size() << " Ways to relation";
                                        //qDebug() << "Added " << mapRelation[relationId]->getTags().size() << " Tags to relation";
                                        break;
                                    }
                                }
                                reader.readNext( );
                            }
                        }

                        if (reader.name( ) != "tag" and 
                            reader.name( ) != "node" and 
                            reader.name( ) != "way" and 
                            reader.name( ) != "relation" and 
                            reader.name( ) != "bound")
                        {
                            qDebug( )<< "Start = "<<reader.name( ).toString( );
                        }
                    }

                    if (!reader.atEnd( ))
                        reader.readNext( );
                    
                }
            }
            else
            {
                qDebug() << "this doesn't seem to start with an osm element";
                break;
            }
        }
        if (!reader.atEnd( ))
            reader.readNext( );
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
        new_model->setNodes ( mapNode.values( ) );
        new_model->setWays( mapWay.values( ) );
        new_model->setRelations( mapRelation.values( ) );

        return new_model;
    }

    return 0;
}


void
Osm::store ( MapModel *model )
{
    QList<Node*> m_trackPoints;
    QList<Way*> m_trackWays;
    QList<Relation*> m_trackRelations;
    m_trackPoints = model->getNodes();
    m_trackWays = model->getWays();
    m_trackRelations = model->getRelations();
    QString fileName = model->getName();
    
    unsigned int id;

    if ( model->getName( ) == "" )
    {
        QDateTime now = QDateTime::currentDateTime( );
        model->setName( now.toString(STORE_FILE_FORMAT) );
        qDebug( ) << "No fileName was set, setting name to: "<< model->getName( ) << ".osm";
    }

    if (fileName.endsWith(".osm") == false)
    {
        fileName = fileName + ".osm";
    }
    QFile file(fileName);
    QXmlStreamWriter xmlWriter(&file);
    QVariant varConvert;


    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug( )  << "Error: Cannot write file ";
    }


    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument( );
    xmlWriter.writeStartElement("osm");
    xmlWriter.writeAttribute( "version", "0.5");
    xmlWriter.writeAttribute( "generator", "Openstreetmap Qtopia cell Phone application");

    //Ga alle nodes af
    for (int i=0; i < m_trackPoints.size( ); ++i)
    {
        if (m_trackPoints[i]->getTags().size() > 0)
        {
            xmlWriter.writeStartElement("node");
            if (m_trackPoints[i]->getTagValue("osmId") != "")
            {
                xmlWriter.writeAttribute( "id",  m_trackPoints[i]->getTagValue("osmId"));
            }
            else
            {
                id = (unsigned long)m_trackPoints[i];
                varConvert = id;
                xmlWriter.writeAttribute( "id",  "new_" + varConvert.toString());
            }
            
                varConvert = m_trackPoints[i]->getLatitude( );
            xmlWriter.writeAttribute( "lat", varConvert.toString( ));
                varConvert = m_trackPoints[i]->getLongitude( );
            xmlWriter.writeAttribute( "lon", varConvert.toString( ));
                varConvert = m_trackPoints[i]->getAltitude( );
            if ( m_trackPoints[i]->getTimestamp( ) != "")
            {
                xmlWriter.writeAttribute("timestamp",m_trackPoints[i]->getTimestamp( ));
            }

            for (int j=0; j < m_trackPoints[i]->getTags().size(); ++j)
            {
                if (m_trackPoints[i]->getTags()[j]->getKey() != "osmId")
                {
                    xmlWriter.writeEmptyElement("tag");
                    xmlWriter.writeAttribute( "k", m_trackPoints[i]->getTags()[j]->getKey() );
                    xmlWriter.writeAttribute( "v", m_trackPoints[i]->getTags()[j]->getValue() );
                }

            }
            xmlWriter.writeEndElement( );

        }
        else
        {
            xmlWriter.writeEmptyElement("node");
            if (m_trackPoints[i]->getTagValue("osmId") != "")
            {
                xmlWriter.writeAttribute( "id",  m_trackPoints[i]->getTagValue("osmId"));
            }
            else
            {
                id = (unsigned long)m_trackPoints[i];
                varConvert = id;
                xmlWriter.writeAttribute( "id",  "new_" + varConvert.toString());
            }
                varConvert = m_trackPoints[i]->getLatitude( );
            xmlWriter.writeAttribute( "lat", varConvert.toString( ));
                varConvert = m_trackPoints[i]->getLongitude( );
            xmlWriter.writeAttribute( "lon", varConvert.toString( ));

            if ( m_trackPoints[i]->getTimestamp( ) != "")
            {
                xmlWriter.writeAttribute("timestamp",m_trackPoints[i]->getTimestamp( ));
            }
        }
    }

    //Ga alle ways af
    for (int i=0; i < m_trackWays.size( ); ++i)
    {
        xmlWriter.writeStartElement("way");
        if (m_trackWays[i]->getTagValue("osmId") != "")
            xmlWriter.writeAttribute( "id",  m_trackWays[i]->getTagValue("osmId"));
        else
        {
            id = ((unsigned long)m_trackWays[i]);
            xmlWriter.writeAttribute( "ref",  "new_" + ((QVariant)id).toString());
        }
        if (m_trackWays[i]->getTimestamp( ) != "")
            xmlWriter.writeAttribute("timestamp",m_trackWays[i]->getTimestamp( ));

        //Ga alle nodes van de way af
        for (int j=0; j < m_trackWays[i]->getNodes().size(); ++j)
        {
            xmlWriter.writeEmptyElement("nd");
            if (m_trackWays[i]->getNodes()[j]->getTagValue("osmId") != "")
            {
                xmlWriter.writeAttribute( "ref", m_trackWays[i]->getNodes()[j]->getTagValue("osmId") );
            }
            else
            {
                id = (unsigned long)m_trackWays[i]->getNodes()[j];
                xmlWriter.writeAttribute( "ref",  "new_" + ((QVariant)id).toString());
            }
        }

        //Ga alle tags van de way af
        for (int j=0; j < m_trackWays[i]->getTags().size(); ++j)
        {
            if ( m_trackWays[i]->getTags()[j]->getKey() != "osmId" )
            {
                xmlWriter.writeEmptyElement("tag");
                xmlWriter.writeAttribute( "k", m_trackWays[i]->getTags()[j]->getKey() );
                xmlWriter.writeAttribute( "v", m_trackWays[i]->getTags()[j]->getValue() );
            }
        }
        xmlWriter.writeEndElement( );
    }

    //Ga alle relations
    for (int i=0; i < m_trackRelations.size( ); ++i)
    {
        xmlWriter.writeStartElement("relation");
        if (m_trackRelations[i]->getTagValue("osmId") != "")
        {
            xmlWriter.writeAttribute( "id",  m_trackRelations[i]->getTagValue("osmId"));
        }
        else
        {
            id = (unsigned long)m_trackRelations[i];
            varConvert = id;
            xmlWriter.writeAttribute( "ref",  "new_" + varConvert.toString());
        }
        if (m_trackRelations[i]->getTimestamp( ) != "")
        {
            xmlWriter.writeAttribute("timestamp",m_trackRelations[i]->getTimestamp( ));
        }

        //Ga alle ways van de relation af
        for (int j=0; j < m_trackRelations[i]->getWays().size(); ++j)
        {
            xmlWriter.writeEmptyElement("member");
            xmlWriter.writeAttribute( "type", "way" );
            if (m_trackRelations[i]->getWays()[j]->getTagValue("osmId") != "")
            {
                xmlWriter.writeAttribute( "ref", m_trackRelations[i]->getWays()[j]->getTagValue("osmId") );
            }
            else
            {
                id = (unsigned long)m_trackRelations[i]->getWays()[j];
                varConvert = id;
                xmlWriter.writeAttribute( "ref",  "new_" + varConvert.toString());
            }
        }

        //Ga alle tags van de relation af
        for (int j=0; j < m_trackRelations[i]->getTags().size(); ++j)
        {
            if ( m_trackRelations[i]->getTags()[j]->getKey() != "osmId" )
            {
                xmlWriter.writeEmptyElement("tag");
                xmlWriter.writeAttribute( "k", m_trackRelations[i]->getTags()[j]->getKey() );
                xmlWriter.writeAttribute( "v", m_trackRelations[i]->getTags()[j]->getValue() );
            }

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


