//
// C++ Interface: streetwidget
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef STREETWIDGET_H
#define STREETWIDGET_H

#include <QWidget>
#include <QtGui>
#include "ui_streetwidget.h"
#include "mapfeature.h"
/**
    @author wolf,,, <wolf@laptop>
*/
class StreetWidget : public QDialog , public Ui::StreetDialog
{
    Q_OBJECT
    public:
        StreetWidget(QDialog *parent = 0);
        void setMapFeature(MapFeature *);
        QString getName();
        QString getContainerName();
        QString getFeatureName();
        ~StreetWidget();
    private:
        QStringList* listWays;
        MapFeature *mapfeature;
        void buildMenus();

    private slots:
        void changeWays(int type);
};

#endif
