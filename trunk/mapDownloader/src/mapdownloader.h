
#ifndef MAPDOWNLOADER_H
#define MAPDOWNLOADER_H

#include <QMainWindow>
#include <QCloseEvent>

#include <QtGui>
#include "../../QMapControl/qmapcontrol.h"
#include "../QMapControl/src/imagemanager.h"
using namespace qmapcontrol;
class MapDownloader : public QMainWindow
{
    Q_OBJECT
    public:
        MapDownloader(QWidget *parent = 0);

        ~MapDownloader();

    private:
        MapControl* mc;
        MapAdapter* mapadapter;
        MapAdapter* mapAdapter;
        Layer* mainlayer;

        QMenu* mapMenu;
        QAction* osmAction;

        int tilesonzoomlevel(int);
        bool downloadTile(int,int,int);
        bool tileExist(QString);
        void downloadLayer(int);
        void setComboBox();
        void addZoomButtons();
        void updateProgressBar();
        void updateView();

        QSlider* sliderZoom;
        QLabel* labelLatitude;
        QLabel* labelLongitude;
        QLabel* labelTileCount;
        QComboBox* comboBoxLayerDepth;
        QProgressBar* downloadProgress;
        QList<int> *downloadListx;
        QList<int> *downloadListy;
        QList<int> *downloadListz;
        int tilesDownloadCount;
        int m_downloadIndex;
        int m_mouseCount;
        
    public slots:
        void mouseEventCoordinate(const QMouseEvent*, const QPointF);
        void resetMouseCount();
        void download();
        void stopDownloading();
        void debugGPS();
        void labelInfo();
        void downloadfinish();
        void downloadTileList();
};

#endif
