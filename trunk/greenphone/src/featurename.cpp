//
// C++ Implementation: FeatureName
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Cleassens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "featurename.h"

FeatureName::FeatureName(QString nm,int elementType,QString pic)
{
    name = nm;
    node = elementType & NODE;
    area = elementType & AREA;
    way =  elementType & WAY;
    picture = pic;
    QPen m_pen;
}
FeatureName::FeatureName(QString nm,int elementType,QPen pen)
{
    name = nm;
    node = elementType & NODE;
    area = elementType & AREA;
    way =  elementType & WAY;
    QPicture picture;
    m_pen = pen;
}
QPen FeatureName::getPen()
{
    return m_pen;
}
QString FeatureName::getName()
{
    return name;
}
bool FeatureName::isNode()
{
    return node;
}
bool FeatureName::isArea()
{
    return area;
}
bool FeatureName::isWay()
{
    return way;
}
QString FeatureName::getPicture()
{
    return picture;
}
FeatureName::~FeatureName()
{
}


