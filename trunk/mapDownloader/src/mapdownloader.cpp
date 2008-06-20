#include <QtGui>
#include "mapdownloader.h"

MapDownloader::MapDownloader(QWidget *parent)
: QMainWindow(parent)
{
    resize(900,800);
    mc = new MapControl(frameSize());

    // create mapadapter, for mainlayer and overlay
    mapadapter = new OSMMapAdapter();
    mapAdapter = new OSMMapAdapter();
    mainlayer = new MapLayer("map Layer", mapadapter);
    mc->addLayer(mainlayer);
    addZoomButtons();
    setCentralWidget(mc);
    mc->setZoom(3);
    connect(mc, SIGNAL(mouseEventCoordinate(const QMouseEvent*, const QPointF)),
              this, SLOT(mouseEventCoordinate(const QMouseEvent*, const QPointF)));
    downloadListx = new QList<int>;
    downloadListy = new QList<int>;
    downloadListz = new QList<int>;
    updateView();
}
void MapDownloader::addZoomButtons()
{
    // create buttons as controls for zoom
    QPushButton* zoomin = new QPushButton("+");
    QPushButton* zoomout = new QPushButton("-");
    
    zoomin->setMaximumWidth(50);
    zoomout->setMaximumWidth(50);

    sliderZoom = new QSlider();
    sliderZoom->setLayoutDirection(Qt::LeftToRight);
    sliderZoom->setTickInterval(1);
    sliderZoom->setMaximum( mapAdapter->maxZoom() );

    connect(zoomin,  SIGNAL( clicked(bool)), mc, SLOT(zoomIn()));
    connect(zoomout, SIGNAL( clicked(bool)), mc, SLOT(zoomOut()));
    connect(zoomin,  SIGNAL( clicked()),    this, SLOT(debugGPS()));
    connect(zoomout, SIGNAL( clicked()),    this, SLOT(debugGPS()));

    connect(sliderZoom, SIGNAL( valueChanged(int) ),    mc, SLOT(setZoom(int)));
    connect(sliderZoom, SIGNAL( valueChanged(int) ),    this, SLOT(debugGPS()));

    // layout fo the gpc position
    labelLatitude = new QLabel();
    labelLongitude = new QLabel();
    QVBoxLayout* GPSlayout = new QVBoxLayout;
    GPSlayout->addWidget(labelLatitude);
    GPSlayout->addWidget(labelLongitude);

    QPushButton* PushButtonDownload = new QPushButton("Download");
    QPushButton* PushButtonStop = new QPushButton("Stop");
    PushButtonDownload->setMaximumWidth(100);
    PushButtonStop->setMaximumWidth(100);

    comboBoxLayerDepth = new QComboBox();
    comboBoxLayerDepth->setMaximumWidth(50);
    connect(comboBoxLayerDepth,SIGNAL(currentIndexChanged(int)),this,SLOT(labelInfo()) );

    labelTileCount = new QLabel();
    labelTileCount->setMaximumWidth(150);

    QHBoxLayout* layoutButtons = new QHBoxLayout();
    layoutButtons->addWidget(PushButtonDownload);
    layoutButtons->addWidget(PushButtonStop);
    layoutButtons->addStretch();

    QHBoxLayout* layoutOptions = new QHBoxLayout();
    layoutOptions->addWidget(comboBoxLayerDepth);
    layoutOptions->addWidget(labelTileCount);
    layoutOptions->addStretch();

    downloadProgress = new QProgressBar();
    downloadProgress->setMaximumWidth(160);
    QVBoxLayout* layoutmain = new QVBoxLayout();
    layoutmain->addLayout(layoutOptions);
    layoutmain->addWidget(downloadProgress);
    layoutmain->addLayout(layoutButtons);

    connect(PushButtonDownload, SIGNAL(clicked()), this, SLOT(download()));
    connect(PushButtonStop, SIGNAL(clicked()), this, SLOT(stopDownloading()));
    // construct the layout
    QVBoxLayout* innerlayout = new QVBoxLayout;
    innerlayout->addWidget(zoomin);
    innerlayout->addWidget(zoomout);
    innerlayout->addLayout(GPSlayout);
    innerlayout->addWidget(sliderZoom);
    innerlayout->addLayout(layoutmain);
    innerlayout->addWidget(labelLatitude);  //add empty label for not hiding the distancebar
    mc->setLayout(innerlayout);
}
void MapDownloader::debugGPS() // view changed
{
    updateView();
}
void MapDownloader::updateView()
{
    QVariant x=mc->currentCoordinate().x();
    QVariant y=mc->currentCoordinate().y();
    labelLatitude->setText( y.toString() );
    labelLongitude->setText( x.toString() );
    sliderZoom->setSliderPosition( mapadapter->currentZoom());
    setComboBox();
    labelInfo();

    QPointF GPS = mc->currentCoordinate();
//     qDebug()<<"zoom:" << mapadapter->currentZoom()<< "GPS NB:"<<GPS << "TileSize"<<mapAdapter->tilesize();
//     qDebug()<<"corDispl:" << mapadapter->coordinateToDisplay(GPS) <<"tilezoom:"<<tilesonzoomlevel(2);
//     qDebug()<<"tiles count"<<tilesDownloadCount;
}
void MapDownloader::download()
{
    downloadListx->clear();
    downloadListy->clear();
    downloadListz->clear();
    connect(ImageManager::instance(), SIGNAL(imageReceived()),
                   this, SLOT(downloadTileList() ));
    connect(ImageManager::instance(), SIGNAL(loadingFinished()),
                   this, SLOT(downloadfinish() ));
    downloadProgress->setValue(0);
    tilesDownloadCount=0;
    for(int lus=1; lus< comboBoxLayerDepth->currentIndex()+1; lus++)
        downloadLayer(lus);

    labelTileCount->setText("Tiles:"+QVariant(tilesDownloadCount).toString() );
    m_downloadIndex=0;
    downloadTileList();downloadTileList();downloadTileList();downloadTileList();
}
void MapDownloader::downloadTileList()
{
    if (m_downloadIndex<downloadListy->size()) {
    ImageManager::instance()->prefetchImage(mapAdapter->host(), mapAdapter->query(downloadListx->at(m_downloadIndex), 
                            downloadListy->at(m_downloadIndex), downloadListz->at(m_downloadIndex)));
        m_downloadIndex++;
        qDebug()<<"download tiles"<<m_downloadIndex;
        updateProgressBar();
    }
}
void MapDownloader::downloadLayer(int layerDepth) 
{
        QSize windowSize=frameSize();
        QPoint screenmiddle(windowSize.width()/2 * tilesonzoomlevel(layerDepth),windowSize.height()/2 * tilesonzoomlevel(layerDepth));
        int zoom = mapadapter->currentZoom()+layerDepth;
        QPoint mapmiddle_px = mapadapter->coordinateToDisplay( mc->currentCoordinate() );
        mapmiddle_px.setX( mapmiddle_px.x() * tilesonzoomlevel(layerDepth) );
        mapmiddle_px.setY( mapmiddle_px.y() * tilesonzoomlevel(layerDepth) );

        int tilesize = mapadapter->tilesize();
        int cross_x = int(mapmiddle_px.x() )%tilesize;       // position on middle tile
        int cross_y = int(mapmiddle_px.y() )%tilesize;

        int space_left = screenmiddle.x() - cross_x;
        int tiles_left = space_left/tilesize;
        if (space_left>0) 
            tiles_left+=1;

        int space_above = screenmiddle.y() - cross_y;
        int tiles_above = space_above/tilesize;
        if (space_above>0) 
            tiles_above+=1;

        int space_right = screenmiddle.x() - (tilesize-cross_x);
        int tiles_right = space_right/tilesize;
        if (space_right>0) 
            tiles_right+=1;

        int space_bottom = screenmiddle.y() - (tilesize-cross_y);
        int tiles_bottom = space_bottom/tilesize;
        if (space_bottom>0) 
            tiles_bottom+=1;

        int mapmiddle_tile_x = mapmiddle_px.x()/tilesize;
        int mapmiddle_tile_y = mapmiddle_px.y()/tilesize;


        for (int i=-tiles_left+mapmiddle_tile_x; i<=tiles_right+mapmiddle_tile_x; i++)
        {
            for (int j=-tiles_above+mapmiddle_tile_y; j<=tiles_bottom+mapmiddle_tile_y; j++)
            {

                downloadTile(i,j,zoom);
            }
        }
        downloadProgress->setMaximum(tilesDownloadCount);
}
bool MapDownloader::downloadTile(int x,int y, int z)
{
    if( mapAdapter->isValid(x,y,z) ) 
    {
        if (tileExist( mapAdapter->query(x, y, z)) )
             return true;

        downloadListx->append(x);
        downloadListy->append(y);
        downloadListz->append(z);
        tilesDownloadCount++;
        return true;
    }
    else
    {
        qDebug()<<"error download tile "<<mapAdapter->query(x, y, z);
        return false;
    }
}
bool MapDownloader::tileExist(QString tileName)
{
        tileName.replace("/",".");
        QFile file("/mnt/documents/cache/tile"+tileName);
        if (file.exists())
            return true;
        else
            return false;
}
void MapDownloader::setComboBox() 
{
    disconnect(comboBoxLayerDepth,SIGNAL(currentIndexChanged(int)),0,0 );
    comboBoxLayerDepth->clear();
    for(int lus=0; lus< mapAdapter->maxZoom()-mapadapter->currentZoom()+1; lus++)
        comboBoxLayerDepth->addItem( QVariant(lus).toString() );
    connect(comboBoxLayerDepth,SIGNAL(currentIndexChanged(int)),this,SLOT(labelInfo()) );
}
void MapDownloader::labelInfo()
{
    QSize windowSize=frameSize();

    int x =windowSize.width() / mapadapter->tilesize();
    int y =windowSize.height() / mapadapter->tilesize();
    int depth = comboBoxLayerDepth->currentIndex();
    double totalTiles=0;

    totalTiles +=(x+1)*(y+1)*pow(4,depth);
 
    labelTileCount->setText("Tiles:"+QVariant(totalTiles).toString() );
    qDebug()<<"tiles"<<x <<"*"<< y;
}
void MapDownloader::updateProgressBar()
{
    downloadProgress->setValue(downloadProgress->value()+1);
}
void MapDownloader::downloadfinish()
{
    disconnect(ImageManager::instance(),0,this,0);
    qDebug()<<"Download finish";
}
int MapDownloader::tilesonzoomlevel(int zoomlevel) 
{
        return int(pow(2, zoomlevel));
}
void MapDownloader::stopDownloading()
{
    qDebug()<<"stop downloading";
    disconnect(ImageManager::instance(),0,this,0);
    downloadProgress->setValue(0);
    downloadListx->clear();
    downloadListy->clear();
    downloadListz->clear();
}
void MapDownloader::mouseEventCoordinate(const QMouseEvent* evnt, const QPointF coordinate)
{
    if (m_mouseCount<2)
        QTimer::singleShot(600, this, SLOT(resetMouseCount()));
    else
    {
        if (mc->currentZoom()<17)
            mc->zoomIn();
            mc->setView(coordinate);
        m_mouseCount=0;
    }
    updateView();
    m_mouseCount++;
}
void MapDownloader::resetMouseCount()
{
    m_mouseCount=0;
}
MapDownloader::~MapDownloader()
{
}
