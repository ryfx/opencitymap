//
// C++ Interface: mapfeature
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MAPFEATURE_H
#define MAPFEATURE_H

#include <QList>
#include <QStringList>

#include "featurename.h"
#include "featurecontainer.h"

class MapFeature
{
    public:
        MapFeature();
        void addContainer(FeatureContainer* container);
        void buildFeature();
        void filter(int);

        QStringList getContainerList();
        QStringList getFeatureList(QString);
        FeatureContainer* getContainer(QString);
        ~MapFeature();

        FeatureContainer *m_highway,*m_natural,*m_cycleway,*m_waterway, *m_railway, *m_amenity;

    private:
        QMap< QString, FeatureContainer * > *m_container;
        int element;
};

#endif
