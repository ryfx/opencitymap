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
#ifndef TAGDIALOG_H
#define TAGDIALOG_H

#include <QWidget>
#include <QtGui>
#include "ui_tagdialog.h"
#include "mapfeature.h"
/**
    @author wolf,,, <wolf@laptop>
*/
class TagDialog : public QDialog , public Ui::TagDialog
{
    Q_OBJECT
    public:
        TagDialog(QDialog *parent = 0);
        QString getName();
        QString getContainerName();
        QString getFeatureName();
        QString getFeaturePicture();
        void setMapFeature(MapFeature *);
        ~TagDialog();

    private:
        QStringList* listWays; 
        MapFeature* mapfeature;
        void buildMenus();

    private slots:
        void changeWays(int type);
};

#endif
