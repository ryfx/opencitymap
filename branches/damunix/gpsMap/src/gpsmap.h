

#ifndef GPSMAP_H
#define GPSMAP_H

// #include <QMainWindow>
// #include <QCloseEvent>
#include <QTimer>
#include <QDialog>
#include <QWidget>
#include <QDialog>

#include "ui_gpsmapbase.h"
#include "gps.h"

class GPSMap 
: public QWidget, public Ui::GPSMapBase
{
    Q_OBJECT
    
    public:
        GPSMap(QWidget *parent =0, Qt::WFlags f=0);
        ~GPSMap();
    
    private slots:
        void tick(QPointF);
        void goodBye();
    
    private:
        GPS* gpsTomTom;
};

#endif
