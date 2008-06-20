#include "citymap.h"

Citymap::Citymap(QWidget *parent, Qt::WFlags f)
{
    LoadScreen* startupscreen = new LoadScreen(parent, f );
    startupscreen->show();

    mapfeature = new MapFeature();
    mapfeature->buildFeature();
    
    // create MapControl
    mc = new MapControl(QSize(240,240));
    highlightnode = new HighLightNode();
    mc->setHighLightNode(highlightnode);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(mc);

    QWidget* w = new QWidget(parent, f);
    
    w->setLayout(layout);
    setCentralWidget(w);

    mapadapter = new OSMMapAdapter();
    highlightnode->setMapAdapter(mapadapter);
    // create a layer with the mapadapter and type MapLayer
    l = new MapLayer("Custom Layer", mapadapter);
    mc->addLayer(l);

    roads = new GeometryLayer("roads", mapadapter);
    mc->addLayer(roads);

    mapTags = new GeometryLayer("mapTags", mapadapter);
    mc->addLayer(mapTags);

    penWay = new QPen(QColor(0x0,0x0,0xff,100));
    penWay->setWidth(5);

    // cursor for the GPS module
//     ip = new ImagePoint(0,0, ":/marker2.png", "GPS Marker", Point::Middle);
//     l2 = new MapLayer("gps layer", mapadapter);
//     l2->addGeometry(ip);
//     mc->addLayer(l2);

    gpsTomTom = new GPS();
    gpsTomTom->fake(true); // enable fake GPS

//     connect(gpsTomTom, SIGNAL(new_position(QPointF)),
//                  ip, SLOT(setCoordinate(QPointF)));

    connect(gpsTomTom, SIGNAL(new_position(QPointF)),
              highlightnode, SLOT(setCoordinate(QPointF)));

    qDebug()<<"GPS created";

    createMenus();

    ways = new GeometryLayer("roads", mapadapter);
    mc->addLayer(ways);

    gpxFile= new Gpx();
    osmFile= new Osm();
    mapmodel = osmFile->load( "/mnt/documents/hogeweg.osm" );
    QList<Way*> listway =   mapmodel->getWays();
    QList<Node*> listnode =   mapmodel->getNodes();
    qDebug()<<"way count"<<listway.size();
    qDebug()<<"nodes count"<<listnode.size();
    QList<Node*>nodes = listway.at(1)->getNodes();
//     for(int loop=0 ;loop<listway.size();loop++)
//          drawWay(listway.at(loop));

    drawNodes(mapmodel->getNodes());
    qDebug()<<"add fotos";
    addFotos();
    qDebug()<<"add fotos ok";
    x = 4.47;
    y = 51.02;exit=true;
    mc->setView(QPointF(x,y));
    mc->setZoom(14);

    startupscreen->close();
    delete startupscreen;
    qDebug()<<"close start upscreen";
    ///////////////////////////// test cafe ///////////////////////
      nodeTest = new Node(y+0.001,x+0.001);
      nodeTest->addTag( new Tag("amenity","cafe") );
      drawNode(nodeTest);

      connect(highlightnode,SIGNAL(destinationReach(Node*)),this,SLOT(destinationReachMessage(Node*)));
      highlightnode->add(nodeTest);

//     HighLightFeature("highway","bus_stop");

    connect(mc, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
              this, SLOT(mouseEventCoordinate(const QMouseEvent*, const QPointF)));

    view = new QListView(parent);
    view->setSelectionMode(QAbstractItemView::MultiSelection);
 
}
void Citymap::HighLightFeature(QString featureContainer, QString featureName)
{
    QList<Node*>nodes=mapmodel->getNodes();
    for(int loop=0;loop<nodes.size();loop++)
    {
        Node* node=nodes.at(loop);
        QList<Tag*> tags=node->getTags();
        QString imageName;
    
        for(int loop=0;loop<tags.size() && imageName.isEmpty(); loop++)
        {
            if (tags.at(loop)->getKey()==featureContainer && tags.at(loop)->getValue()==featureName)
            {
                highlightnode->add(node);
    
            }
        }
    }
}
void Citymap::destinationReachMessage(Node * node)
{
//     QMessageBox::information(this, "GPS info", "je hebt uw bestemming bereikt");
    qDebug()<<"je hebt uw bestemming bereikt" << node;
}

void Citymap::drawWay(Way* way)
{
    QList<Node*>nodes = way->getNodes();

    if (nodes.size()> 0)
    {
        QList<Tag*> tags=way->getTags();
        bool isWay = false;

        m_pen = new QPen(QColor(0xff,0xff,0xff,100));

        for(int loop=0;loop<tags.size() && !isWay ;loop++)
        {
            if(isWay = mapfeature->getContainer(tags.at(loop)->getKey() )->getFeature(tags.at(loop)->getValue() )->isWay())
                *m_pen = mapfeature->getContainer(tags.at(loop)->getKey() )->getFeature(tags.at(loop)->getValue() )->getPen();
        }
        if(!isWay)
        {
             m_pen = new QPen(QColor(0x7f,0x9a,0xbf,100));;
        }
        QList<Point*> points;
        for(int loop=0; loop<nodes.size(); loop++) 
        {
            points << new Point( nodes.at(loop)->getLongitude(), nodes.at(loop)->getLatitude());
        }
        m_pen->setWidth(5);
        way_tour = new LineString(points, "", m_pen);
        ways->addGeometry(way_tour);
    }
    else
        qDebug()<<"error way is empty";
}
void Citymap::toggleTrace(bool trace)
{
    if ( trace ) 
    {
        qDebug()<<"follow";
        connect(gpsTomTom, SIGNAL(new_position(QPointF)),
              this, SLOT(followGPS(QPointF)));
    }
    else
    {
         disconnect(gpsTomTom, SIGNAL(new_position(QPointF)),
              this, SLOT(followGPS(QPointF)));
    }
}
void Citymap::followGPS(QPointF p)
{
    mc->setView(p);
}
void Citymap::tick2() // GPS timer
{
//     gpsTomTom->updatePosition(); 
//     QTimer::singleShot(300, this, SLOT(tick2()));
}
// aan en uitzetten voor een nieuwe weg te tekenen
void Citymap::toggleRecordRoad()
{ 
    if (!recordAction->isChecked() ) // recording of the road stopped
    {
        disconnect(gpsTomTom, SIGNAL(new_position(QPointF)),
              this, SLOT(recordRoad(QPointF)));
        streetdialog = new StreetWidget();
        if (QDialog::Accepted == streetdialog->exec())
        {
            currentWay = new Way();
            currentWay->addTag(new Tag("name",streetdialog->getName()));
            currentWay->addTag(new Tag(streetdialog->getContainerName(),streetdialog->getFeatureName()));

            QList<Point*> points=currentRoad->points();
            for(int loop=0;loop<currentRoad->numberOfPoints();loop++) 
            {
                qDebug()<<points.at(loop);
                Node* newNode=new Node( points.at(loop)->latitude(), points.at(loop)->longitude(), 344.240, "2008-04-16T09:78:55Z");
                mapmodel->addNode( newNode );
                currentWay->addNode( newNode );
            } 
            mapmodel->addWay(currentWay);
        }
        else
        {
            roads->removeGeometry(currentRoad);
            delete currentRoad;
        }
        delete streetdialog;
    }
    else // recording road started
    {
        QList<Point*> points;
        currentRoad = new LineString(points, "", penWay);
        roads->addGeometry(currentRoad);
        connect(gpsTomTom, SIGNAL(new_position(QPointF)),
              this, SLOT(recordRoad(QPointF)));
    }
}
void Citymap::closeEvent(QCloseEvent *event)
{
    if(!exit) {
        event->ignore();
        exit=true;
    }
    else {
        gpsTomTom->gpsDisconnect();
        qDebug()<<"Exit application" << event;
        mapmodel->setName ("/mnt/documents/hogeweg");
        osmFile = new Osm();
        osmFile->store(mapmodel);
        gpxFile->store(mapmodel);
    }
}
 // teken gps weg
void Citymap::recordRoad(QPointF point)
{
    currentRoad->addPoint( new Point(point.x(), point.y()) );
}
// toon het menu voor Tag op de kaart te zetten
void Citymap::displayTagDialog()
{ 
    tagdialog = new TagDialog( );

    if (QDialog::Accepted == tagdialog->exec())
    {
        newNode = new Node(mc->currentCoordinate().ry(),mc->currentCoordinate().rx());
        newNode->addTag(new Tag("name",tagdialog->getName()));
        newNode->addTag(new Tag(tagdialog->getContainerName(),tagdialog->getFeatureName()));
        drawNode(newNode);
        mapmodel->addNode(newNode);
    }
    delete tagdialog;
}
void Citymap::drawNodes(QList<Node*> nodes)
{
    for(int loop=0;loop<nodes.size();loop++)
    {
        drawNode(nodes.at(loop));
    }
}
void Citymap::drawNode(Node* node)
{
    QList<Tag*> tags=node->getTags();
    QString imageName;

    for(int loop=0;loop<tags.size() && imageName.isEmpty() ;loop++)
    {
         imageName = mapfeature->getContainer(tags.at(loop)->getKey() )->getFeature(tags.at(loop)->getValue() )->getPicture();
    }
    if(!imageName.isEmpty())
    {
        QString iconPath = ":/"+ imageName; // /mnt/documents/images/ //QCoreApplication::applicationDirPath()
        if (QFile::exists(iconPath)) {
            QPixmap* image = new QPixmap(iconPath);
            Point* nodePoint = new Point(node->getLongitude(), node->getLatitude(), image, "node" );
            nodePoint->setBaselevel(16);
            nodePoint->setMaxsize(QSize(25,25));
            mapTags->addGeometry(nodePoint);
        }
        else
            qDebug()<<"picture not found"<<iconPath;
    }
}
void Citymap::addFotos()
{
    QString fotoDir= "/mnt/documents/image/jpeg/";

    QDir dir(fotoDir);
    if(dir.exists()) 
    {
        QFileInfoList list;
        QStringList filters;
        filters << "*.jpg" << "*.jpeg";
        dir.setNameFilters(filters);
        dir.setSorting(QDir::Size | QDir::Reversed);
        list = dir.entryInfoList();
        m_photoLayer = new GeometryLayer("Fotos", mapadapter);
        mc->addLayer(m_photoLayer);
        for (int i = 0; i < list.size(); ++i) 
        {
            QFileInfo fileInfo = list.at(i);
            addFoto(fotoDir+fileInfo.fileName());
        }
        connect(m_photoLayer, SIGNAL(geometryClicked(Geometry*, QPoint)),
                this, SLOT(geometryClicked(Geometry*, QPoint)));
    }
    else
    {
        qDebug()<<tr("Error Photo: path not found");
    }
}
void Citymap::addFoto(QString fotoPath)
{
     GeoFoto fotoRead(fotoPath);
     if (fotoRead.readSettings()) // gps data in picture
     {
                Point* fotoTag = new ImagePoint(fotoRead.getLongitude(), fotoRead.getLatitude(), fotoPath, fotoPath);
                fotoTag->setBaselevel(20);
                m_photoLayer->addGeometry(fotoTag);
     }
}
void Citymap::geometryClicked(Geometry* geometry, QPoint)
{
    InfoDialog* infodialog = new InfoDialog(this);
    infodialog->setWindowTitle(geometry->name());

    infodialog->setInfotext("<img width='216' height='264' src=\""+geometry->name()+"\" align=\"left\"/>");

    if (geometry->name() != "")
        infodialog->showMaximized();
}
void Citymap::mouseEventCoordinate(const QMouseEvent* evnt, const QPointF coordinate)
{
    if (m_mouseCount<2)
        QTimer::singleShot(600, this, SLOT(resetMouseCount()));
    else
    {
        double bound = 20/pow(2,mc->currentZoom());
        if (coordinate.x()<previousMouse.x()+bound && coordinate.x()>previousMouse.x()-bound && 
            coordinate.y()<previousMouse.y()+bound &&       coordinate.y()>previousMouse.y()-bound)
            if (mc->currentZoom()<17)
                mc->zoomIn();
        m_mouseCount=0;
    }
    previousMouse = coordinate;
    m_mouseCount++;
}
void Citymap::resetMouseCount()
{
    m_mouseCount=0;
}
void Citymap::keyPressEvent(QKeyEvent * event)
{
    switch(event->key()) {
        case Qt::Key_Up:
            traceAction->setChecked(false);
            mc->scrollUp();
        break;
        case Qt::Key_Down:
            traceAction->setChecked(false);
            mc->scrollDown();
        break;
        case Qt::Key_Left:
            traceAction->setChecked(false);
            mc->scrollLeft();
        break;
        case Qt::Key_Right:
            traceAction->setChecked(false);
            mc->scrollRight();
        break;
        case Qt::Key_1:
            if (mc->currentZoom()<17)
                mc->zoomIn();
        break;
        case Qt::Key_Select:  // select key
             if (mc->currentZoom()<17)
                 mc->zoomIn();
        break;
        case Qt::Key_Back:
            exit=false;
            if (mc->currentZoom()>0)
                mc->zoomOut();
        break;
        default:
            qDebug() <<"key" << event->key();
        break;
    }
}
void Citymap::createMenus()
{
    optionsMenu = QSoftMenuBar::menuFor(this); 

    startScriptAction = new QAction( tr("Start Script"), optionsMenu);
    optionsMenu->addAction( startScriptAction );
    connect( startScriptAction, SIGNAL(triggered ( bool ) ), this, SLOT( startScript() ) );
    
    optionsMenu->addAction( tr("Take picture"), this, SLOT( takePicture() ));
    optionsMenu->addAction( tr("Tag"), this, SLOT(displayTagDialog()) );
    recordAction = new QAction( tr("Record Road"), optionsMenu);
    recordAction->setCheckable( true );
    optionsMenu->addAction( recordAction );
    connect( recordAction, SIGNAL( toggled( bool ) ), this, SLOT( toggleRecordRoad() ) );

    traceAction = new QAction( tr("Follow GPS"), optionsMenu);
    traceAction->setCheckable( true );
    optionsMenu->addAction( traceAction );
    connect( traceAction, SIGNAL( toggled( bool ) ), this, SLOT( toggleTrace(bool) ) );

    optionsMenu->addAction( tr("Select GPS Device"), gpsTomTom, SLOT(selectGPSDevice()));
    optionsMenu->addAction( tr("Exit"), this, SLOT(close()) ); 

    QSoftMenuBar::setLabel(this, Qt::Key_Context1   ,QSoftMenuBar::Options , QSoftMenuBar::AnyFocus);
    QSoftMenuBar::setLabel(this, Qt::Key_Select     ,"","ZoomIn"  , QSoftMenuBar::AnyFocus);
    QSoftMenuBar::setLabel(this, Qt::Key_Back       ,"","ZoomOut"  , QSoftMenuBar::AnyFocus);
}
Citymap::~Citymap()
{
//     delete mc;
//     delete mapadapter;
// //     delete sights;
//     delete mapTags;
//     delete m_photoLayer;
//     delete mapfeature;
}
void Citymap::takePicture()
{
    QtopiaServiceRequest req( "Camera", "shutter()" );
    if (req.send())
    {
        m_photoCount = 0;
        QTimer::singleShot(8000, this, SLOT(fotoScan()));
    }
    else
        qDebug()<<"request service fail:"<<req.message();
}

void Citymap::fotoScan() // GPS timer
{
    QString fotoDir= "/mnt/documents/image/jpeg/";
    qDebug()<<"scan for new foto";

    QDir dir(fotoDir);
    QStringList filters;
    filters << "*.jpg" << "*.jpeg";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Time );//| QDir::Reversed
    QFileInfoList fotoList = dir.entryInfoList();
    int CurrentPhotoCount = fotoList.size();
    if (m_photoCount<CurrentPhotoCount && m_photoCount>0)
    {
        QFileInfo fileInfo = fotoList.first();
        qDebug()<<"new foto"<<fileInfo.fileName();
        fotoPath = new QString(fotoDir+fileInfo.fileName());
        QTimer::singleShot(2000, this, SLOT(writeExIFData()));
    }
    m_photoCount = CurrentPhotoCount;
    if (!isActiveWindow())
        QTimer::singleShot(3000, this, SLOT(fotoScan()));
}
void Citymap::writeExIFData()
{
    GeoFoto foto(*fotoPath);
    foto.setLatitude(mc->currentCoordinate().ry());
    foto.setLongitude(mc->currentCoordinate().rx());
    foto.writeSettings();
    addFoto(*fotoPath);
    qDebug()<<"new foto added to the map";
}
void Citymap::startScript()
{ 
    gameMenu = new QMenu();
    optionsMenu->insertMenu ( startScriptAction, gameMenu );
    gameMenu->addSeparator ();
    gameMenu->setTitle("ScriptMenu");
    optionsMenu->removeAction(startScriptAction);

    script = new Script( mapmodel, gameMenu, highlightnode, view);
    connect(script,SIGNAL(showMessageBox(QString, QString)),
                    this,SLOT(showMessage(QString, QString)));

                    
}

void Citymap::showMessage(QString title, QString message)
{
    QMessageBox::information(this, title, message);
}


