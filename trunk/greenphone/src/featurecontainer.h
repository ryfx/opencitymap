//
// C++ Interface: featurecontainer
//
// Description: 
//
//
// Author: wolf,,, <wolf@laptop>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FEATURECONTAINER_H
#define FEATURECONTAINER_H

#include "featurename.h"

#include <QString>
#include <QList>
#include <QStringList>


class FeatureContainer
{
    public:
        FeatureContainer(QString cname);
        void addFeature(FeatureName* newFeature);
        void filter(int);
        QStringList getFeatureList();
        QString getName();
        FeatureName* getFeature(QString name);
        ~FeatureContainer();
    private:
        QMap< QString, FeatureName * > *m_feature;
        QStringList* filterResult;
        QString containername;
        bool filterNode, filterWay, filterArea;
};

#endif
