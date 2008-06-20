#ifndef CITYMAP_H
#define CITYMAP_H

#include <QtGui>
#include <QSoftMenuBar>
//#include <CameraService>
#include "qtopiaservices.h"
#include <QtopiaAbstractService>
#include <QDSServiceInfo>
#include <QDSAction>

#include <QDSActionRequest>
#include <QTimeString>
#include <QDSData>
#include <QContent>
#include <qtopiaphone/QSimCommand>
#include <QVBoxLayout>
#include <QFrame>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QWidget>
#include <Node>

#include "../QMapControl/qmapcontrol.h"
#include "dialogs.h"
#include "streetwidget.h"
#include "loadscreen.h"
#include "tagdialog.h"
#include "mapfeature.h"
#include "gps.h"
// #include "highlightnode.h"
#include "script.h"

#include "mapModel.h"
#include "dataInterface.h"
#include "gpx.h"
#include "osm.h"


#include "geofoto.h"


using namespace qmapcontrol;
class Citymap: public QMainWindow
{
    Q_OBJECT
    public:
        Citymap(QWidget *parent = 0, Qt::WFlags f = 0);

        
        ~Citymap();

    private:
        MapControl* mc;
        MapAdapter* mapadapter;
        StreetWidget* streetdialog;
        TagDialog* tagdialog;
        MapFeature* mapfeature;
        Script* script;
        
        Layer* sights;
        Layer* m_photoLayer;
        Layer* mapTags;
        Layer* roads;
        Layer* ways;
        Layer* test;
        Layer* l;
        Layer* l2;

        QMenu* optionsMenu;
        QMenu* gameMenu;

        QAction* toggleSights;
        QAction* togglePub;
        QAction* toggleMuseum;
        QAction* recordAction;
        QAction* traceAction;
        QAction* startScriptAction;

        QAction* togglePubTour;
        QAction* toggleMuseumTour;
        QAction* toggleSightTour;

        QPen* penWay;
        QPen* m_pen;

        bool ignoreClicks;

        void addFotos();
        void addFoto(QString);
        void drawWay(Way*);
        void drawNode(Node*);
        void drawNodes(QList<Node*>);
        void createMenus();
        void takePhotoNow();
        void HighLightFeature(QString,QString);
 
        QPointF coord1;
        QPointF coord2;
        QPointF previousMouse;
        QPointF* m_destinationPoint;

        LineString* pub_tour;
        LineString* museum_tour;
        LineString* sights_tour;
        LineString* currentRoad;
        LineString* way_tour;

        void tick();

        double x,y ;
        bool m_destinationFlag;

        GPS* gpsTomTom;
        Way* currentWay;
        MapModel* mapmodel;
        MapModel* mapmodel2;
        Gpx* gpxFile;
        Gpx* gpxFile2;
        Osm* osmFile;
        Node* nodeTest;
        Node* nodeTest2;
        Node* newNode;
        Tag* tagTest;
        ImagePoint* ip;
        
        HighLightNode* highlightnode;
        int m_mouseCount;
        int m_photoCount;
        bool exit;
        QListView *view;
        QString *fotoPath;
        
    protected:
        void keyPressEvent(QKeyEvent *event);
        void closeEvent(QCloseEvent *event);

    public slots:
        void geometryClicked(Geometry* geometry, QPoint point);
        void mouseEventCoordinate(const QMouseEvent*, const QPointF);
        void destinationReachMessage(Node*);
        void tick2();
        void recordRoad(QPointF);
        void toggleRecordRoad();
        void toggleTrace(bool);
        void displayTagDialog();
        void takePicture();
        void resetMouseCount();
        void followGPS(QPointF);
        void fotoScan();
        void writeExIFData();
        void startScript();
        void showMessage(QString title, QString message);
 
    signals:
        void destinationReach();
        void showMessageBox(QString, QString);

};


#endif
