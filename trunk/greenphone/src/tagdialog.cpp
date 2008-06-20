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
#include "tagdialog.h"


TagDialog::TagDialog(QDialog *parent)
 : QDialog(parent)
{
    setupUi(this);

// QDialog::showMaximized();
    mapfeature = new MapFeature();

    buildMenus();
    QObject::connect(comboBoxContainer,SIGNAL(currentIndexChanged(int) ),
                this,SLOT(changeWays(int)) );
    emit( changeWays( comboBoxContainer->currentIndex() ) );

}

void TagDialog::buildMenus()
{
    listWays = new QStringList();
    mapfeature->buildFeature();
    *listWays = mapfeature->getContainerList(); // get all tags example: station, halt, 
    comboBoxContainer->addItems(*listWays);
}
void TagDialog::changeWays(int type)
{
    QStringList listWays2;
    mapfeature->filter(NODE);
    listWays2 = mapfeature->getFeatureList( listWays->at(type) );
    comboBoxFeature->clear();
    comboBoxFeature->addItems(listWays2);
    if (!comboBoxFeature->count())
        pushButtonApply->setEnabled(false);
    else
        pushButtonApply->setEnabled(true);
}
QString TagDialog::getName()
{
    return inputName->text();
}
QString TagDialog::getContainerName()
{
    return comboBoxContainer->currentText();
}
QString TagDialog::getFeatureName()
{
    return comboBoxFeature->currentText();
}
QString TagDialog::getFeaturePicture()
{
    return mapfeature->getContainer( getContainerName()  )->getFeature( getFeatureName() )->getPicture();
}
TagDialog::~TagDialog()
{
}
void TagDialog::setMapFeature(MapFeature *aClasse)
{
    *this->mapfeature = *aClasse;
}


