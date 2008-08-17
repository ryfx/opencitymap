//
// C++ Implementation: featurecontainer
//
// Description: 
//
//
// Author: wolf,,, <wolf@laptop>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "featurecontainer.h"

FeatureContainer::FeatureContainer(QString cname)
:containername(cname)
{
    filterResult = new QStringList;
    m_feature = new QMap<QString, FeatureName * >;
}
void FeatureContainer::addFeature(FeatureName* newFeature)
{
    m_feature->insert( newFeature->getName(), newFeature);
}
QString FeatureContainer::getName()
{
    return containername;
}
QStringList FeatureContainer::getFeatureList()
{
    filterResult->clear();
    QMap<QString, FeatureName*>::const_iterator FeatureCounter = m_feature->constBegin();
    while (FeatureCounter != m_feature->constEnd())
    {
        if ( FeatureCounter.value()->isNode()&filterNode || FeatureCounter.value()->isWay()&filterWay || FeatureCounter.value()->isArea()&filterArea )
        {
            filterResult->append( FeatureCounter.value()->getName() );
        }
        ++FeatureCounter;
    }
    return *filterResult;
}
FeatureName* FeatureContainer::getFeature(QString name)
{
    if(m_feature->contains(name))
        return m_feature->value(name);
    else
        return new FeatureName("",false,"");
}
void FeatureContainer::filter(int element)
{
    filterNode = NODE & element;
    filterWay  = WAY  & element;
    filterArea = AREA & element;
}

FeatureContainer::~FeatureContainer()
{
    delete filterResult;
    delete m_feature;
}


