//
// C++ Implementation: mapfeature
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Cleassens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "mapfeature.h"

MapFeature::MapFeature()
{
    m_container = new QMap<QString, FeatureContainer * >;
}


void MapFeature::addContainer(FeatureContainer* newContainer)
{
     m_container->insert( newContainer->getName(),newContainer);
}
void MapFeature::buildFeature()
{
    addContainer(m_highway = new FeatureContainer("highway"));
        m_highway->addFeature(new FeatureName("bus_stop",   NODE,       "bus_stop.png"));
        m_highway->addFeature(new FeatureName("minor",           WAY,   QPen(QColor(0xff,0xff,0xff,200)))); // white
        m_highway->addFeature(new FeatureName("motorway",        WAY,   QPen(QColor(0x7f,0x9a,0xbf,200)))); // light blue
        m_highway->addFeature(new FeatureName("pedestrian",      WAY,   QPen(QColor(0xff,0xff,0xff,200)))); // white 
        m_highway->addFeature(new FeatureName("primary",         WAY,   QPen(QColor(0xe3,0x6c,0x70,200)))); // red
        m_highway->addFeature(new FeatureName("residential",     WAY,   QPen(QColor(0xff,0xff,0xff,200)))); // white
        m_highway->addFeature(new FeatureName("secondary",       WAY,   QPen(QColor(0xfd,0xbf,0x6f,200)))); // orange
        m_highway->addFeature(new FeatureName("track",           WAY,   QPen(QColor(0xff,0xff,0xff,200)))); // white
        m_highway->addFeature(new FeatureName("tertiary",        WAY,   QPen(QColor(0xff,0xff,0xcc,0xff)))); // very licht yellow
        m_highway->addFeature(new FeatureName("traffic_signals",NODE,   "traffic-light.png"));
        m_highway->addFeature(new FeatureName("trunk",           WAY,   QPen(QColor(0x7f,0xc9,0x7f,200)))); // green

    addContainer(m_cycleway = new FeatureContainer("cycleway"));
         m_cycleway->addFeature(new FeatureName("lane",          WAY,    QPen(QColor(0x7f,0xc9,0x7f,200)))); // green
         m_cycleway->addFeature(new FeatureName("track",         WAY,    QPen(QColor(0x7f,0xc9,0x7f,200))));

    addContainer(m_waterway = new FeatureContainer("waterway"));
        m_waterway->addFeature(new FeatureName("river",         WAY,    QPen(QColor(0,0,255,200))));
        m_waterway->addFeature(new FeatureName("canal",         WAY,    QPen(QColor(0,0,255,200))));
        m_waterway->addFeature(new FeatureName("stream",        WAY,    QPen(QColor(0,0,255,200))));
        m_waterway->addFeature(new FeatureName("drain",         WAY,    QPen(QColor(0,0,255,200))));
        m_waterway->addFeature(new FeatureName("dam",           WAY|AREA,QPen(QColor(0,0,255,200))));

    addContainer(m_railway = new FeatureContainer("railway"));
        m_railway->addFeature(new FeatureName("station",    NODE,       "stationnew.png"));
        m_railway->addFeature(new FeatureName("rail",           WAY,    QPen(QColor(0xe3,0xe1,0xdc,200))));
        m_railway->addFeature(new FeatureName("tram",           WAY,    QPen(QColor(0xe3,0xe1,0xdc,200))));

    addContainer(m_amenity = new FeatureContainer("amenity"));
        m_amenity->addFeature(new FeatureName("bank",        NODE              ,"bank.png"));
        m_amenity->addFeature(new FeatureName("pub",         NODE              ,"pub.png"));
        m_amenity->addFeature(new FeatureName("cafe",        NODE              ,"cafe.png"));
        m_amenity->addFeature(new FeatureName("cinema",      NODE              ,"cinema.png"));
        m_amenity->addFeature(new FeatureName("college",     NODE              ,"college.png"));
        m_amenity->addFeature(new FeatureName("courthouse",  NODE              ,"court_of_law.png"));
        m_amenity->addFeature(new FeatureName("fire station",NODE              ,"firebrigade.png"));
        m_amenity->addFeature(new FeatureName("hospital",    NODE|     AREA    ,"hospital.png"));
        m_amenity->addFeature(new FeatureName("nightclub",   NODE              ,"nightclub.png"));
        m_amenity->addFeature(new FeatureName("parking",     NODE|     AREA    ,"parking.png"));
        m_amenity->addFeature(new FeatureName("place_of_worship",NODE          ,"church.png"));
        m_amenity->addFeature(new FeatureName("police",      NODE              ,"police.png"));
        m_amenity->addFeature(new FeatureName("post_box",    NODE              ,"post_box.png"));
        m_amenity->addFeature(new FeatureName("post office", NODE              ,"post_office.png"));
        m_amenity->addFeature(new FeatureName("recycling",   NODE              ,"recycling.png"));
        m_amenity->addFeature(new FeatureName("restaurant",  NODE              ,"restaurant.png"));
        m_amenity->addFeature(new FeatureName("telephone",   NODE              ,"telephone.png"));
        m_amenity->addFeature(new FeatureName("toilets",     NODE              ,"toilets.png"));

    addContainer(m_natural = new FeatureContainer("natural"));
        m_natural->addFeature(new FeatureName("bach",       NODE|WAY,           QPen(QColor(0xee,0xcc,0x55,255))));
        m_natural->addFeature(new FeatureName("water",      NODE|WAY,           QPen(QColor(0xb5,0xd6,0xf1,200))));
        m_natural->addFeature(new FeatureName("wood",       NODE|WAY,           QPen(QColor(0x72,0xbf,0x81,200))));
}

QStringList MapFeature::getContainerList()
{
        return m_container->keys();
}
QStringList MapFeature::getFeatureList(QString name)
{
    if (m_container->contains(name))
    {
        m_container->value(name)->filter(element);
        return m_container->value(name)->getFeatureList();
    }
    else
    {
        QStringList empty;
        return empty;
    }
}
FeatureContainer* MapFeature::getContainer(QString name)
{
    if (m_container->contains(name))
        return m_container->value( name );
    else
    {
        return new FeatureContainer("");
    }
}
void MapFeature::filter(int mask)
{
    element = mask;
}
MapFeature::~MapFeature()
{
    delete m_container;
}


