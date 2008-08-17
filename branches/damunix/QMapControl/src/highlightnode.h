//
// C++ Interface: highlightnode
//
// Description: 
//
//
// Author: wolfgang Ostes <wolfostes@hotmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef HIGHLIGHTNODE_H
#define HIGHLIGHTNODE_H

#include "node.h"
#include <QPainter>
#include <QPointF>
#include <QPoint>

#include "osmmapadapter.h"
#include "mapcontrol.h"
/**
	@author wolfgang Ostes <wolfostes@hotmail.com>
*/

namespace qmapcontrol
{
class MapControl;
class HighLightNode :  public QObject
{
    Q_OBJECT
    public:
        friend class MapControl;
        HighLightNode();
        Q_INVOKABLE  void add(Node *);
        Q_INVOKABLE  void remove(Node *);
        void clear();
        void paint();
        void setMapAdapter(MapAdapter*);
        int calcDistance(QPointF,QPointF);
        int distance(Node*);
        int distance(QPointF);
        void drawDistance(double,double,int,Node*);
        ~HighLightNode();
    private:
        void drawArrow( int, int, Qt::Alignment);
        void drawCarre(int x, int y, int size);
        bool inRange(QPointF ,QPointF, QPointF );
        QPen* pen;
        MapAdapter* m_mapadapter;
        MapControl* m_mapControl;
        QList<Node *>* m_nodes;
        QPointF m_coordinate;
        QPainter*  m_painter;
        double m_longitude;
        double m_latitude;
    protected:
        void setPainter(QPainter *);
        void setMapControl(MapControl*);
    public slots:
        void setCoordinate(QPointF point);
    signals:
        Q_INVOKABLE void destinationReach(Node*);
};
}
#endif
