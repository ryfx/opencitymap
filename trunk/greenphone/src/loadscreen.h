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
#ifndef LOADSCREEN_H
#define LOADSCREEN_H


#include "ui_loadscreenwidget.h"

/**
    @author wolf,,, <wolf@laptop>
*/
class LoadScreen : public QWidget , public Ui::LoadScreen
{
    Q_OBJECT
    public:
        LoadScreen(QWidget *parent = 0,Qt::WFlags f = 0);
        ~LoadScreen();
};

#endif
