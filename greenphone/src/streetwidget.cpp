//
// C++ Implementation: streetwidget
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Cleassens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "streetwidget.h"

StreetWidget::StreetWidget(QDialog *parent)
 : QDialog(parent)
{
    setupUi(this);
    mapfeature = new MapFeature();
    buildMenus();

    QObject::connect(comboBoxRoadType,SIGNAL(currentIndexChanged(int) ),
                this,SLOT(changeWays(int)) );
    emit( changeWays( comboBoxRoadType->currentIndex() ) );
}

void StreetWidget::buildMenus()
{
    listWays = new QStringList();
    mapfeature->buildFeature();
    *listWays = mapfeature->getContainerList(); // get all ways example: highway cycleway railway
    comboBoxRoadType->addItems(*listWays);
}
void StreetWidget::changeWays(int type)
{
    QStringList listWays2;
    mapfeature->filter(WAY);
    listWays2 = mapfeature->getFeatureList( listWays->at(type) );
    comboBoxRoad->clear();
    comboBoxRoad->addItems(listWays2);
    if (!comboBoxRoad->count())
        pushButtonApply->setEnabled(false);
    else
        pushButtonApply->setEnabled(true);
}
QString StreetWidget::getName()
{
    return inputName->text();
}
QString StreetWidget::getContainerName()
{
    return comboBoxRoadType->currentText();
}
QString StreetWidget::getFeatureName()
{
    return comboBoxRoad->currentText();
}
StreetWidget::~StreetWidget()
{

}
void StreetWidget::setMapFeature(MapFeature *aClasse)
{
    *this->mapfeature = *aClasse;
}


