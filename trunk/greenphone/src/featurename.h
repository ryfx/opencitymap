//
// C++ Interface: FeatureName
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef FEATURENAME_H
#define FEATURENAME_H

/**
    @author wolf,,, <wolf@laptop>
*/
#include<QString>
#include<QPen>
#include<QPicture>
#include<QDebug>

#define NODE    0x001
#define WAY     0x010
#define AREA    0x100

class FeatureName
{
    public:
        FeatureName(QString,int,QString);
        FeatureName(QString,int,QPen);
        QString getName();
        QString getPicture();
        QPen getPen();
        bool isNode();
        bool isArea();
        bool isWay();
        ~FeatureName();

    private:
        QString name,picture;
        bool node,area,way;
        QPen m_pen;
};

#endif
