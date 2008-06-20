//
// C++ Implementation: streetwidget
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "loadscreen.h"


LoadScreen::LoadScreen(QWidget *parent,Qt::WFlags f)
 : QWidget(parent, f)
{
    setupUi(this);
    QWidget::showMaximized();
}

LoadScreen::~LoadScreen()
{
}



