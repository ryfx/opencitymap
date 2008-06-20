//
// C++ Implementation: highlightnode
//
// Description: 
//
//
// Author: wolfgang Ostes <wolfostes@hotmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "highlightnode.h"
namespace qmapcontrol
{
HighLightNode::HighLightNode()
{
    m_nodes = new QList<Node *>;
}
void HighLightNode::paint()
{
    int screen_x = m_mapControl->getScreenSize().width();
    int screen_y = m_mapControl->getScreenSize().height();
    int screenMiddle_x = screen_x/2;
    int screenMiddle_y = screen_y/2;
    for(int loop=0; loop<m_nodes->size(); loop++) 
    {
        double y = m_nodes->at(loop)->getLatitude();
        double x = m_nodes->at(loop)->getLongitude();

        QPoint p2 (screenMiddle_x,screenMiddle_y); // map center
        QPoint p1 = m_mapadapter->coordinateToDisplay(QPointF(x,y) ) - m_mapadapter->coordinateToDisplay(m_mapControl->currentCoordinate()) +p2;

        double y1 =p1.y()-screenMiddle_y;
        double x1 =p1.x()-screenMiddle_x;

        double divderx =(double) x1/screenMiddle_x;
        if (divderx==0)
            divderx++;
        double doty = y1/divderx;

        double divdery =(double) y1/screenMiddle_y;
        if (divdery==0)
            divdery++;
        double doty_x = x1/divdery;

        m_painter->setPen(Qt::red);
        if (x1>screenMiddle_x)
        {
            drawArrow(screen_x-18   , screen_y+doty-screenMiddle_y,Qt::AlignRight);
            drawDistance(screen_x-18, screen_y+doty-screenMiddle_y,Qt::AlignRight,m_nodes->at(loop));
        }
        if (x1+screenMiddle_x<0)
        {
            drawArrow(10    , screen_y-doty-screenMiddle_y, Qt::AlignLeft);
            drawDistance(10 , screen_y-doty-screenMiddle_y,Qt::AlignLeft,m_nodes->at(loop));
        }
        if (y1+screenMiddle_x>screen_y)
        {
            drawArrow(+doty_x+screenMiddle_x, screen_y-10, Qt::AlignTop);
            drawDistance(+doty_x+screenMiddle_x, screen_y-10,Qt::AlignTop,m_nodes->at(loop));
        }
        if (y1+screenMiddle_x <0)
        {
            drawArrow(-doty_x+screenMiddle_x, 0+10, Qt::AlignBottom);
            drawDistance(-doty_x+screenMiddle_x, 0+10,Qt::AlignBottom,m_nodes->at(loop));
        }
        // draw a marker when de Node is visable
        if (p1.y()>0 && p1.y()<screen_y && p1.x()>0 && p1.y()<screen_y) 
        {
            drawCarre(x1+screenMiddle_x,    y1+screenMiddle_y,8);
        }
    }
}
void HighLightNode::drawCarre(int x, int y, int size)
{
    pen = new QPen(QColor(Qt::red));
    pen->setWidth(5);
    m_painter->setPen(*pen);
//     m_painter->drawRect(QRect( x-size, y-size, size, size )); //
//     size = m_mapadapter->coordinateToDisplay(QPointF(0.0002-180,0.0002-180) ).x();
//     qDebug()<<size;
    m_painter->drawRect(QRect( x, y, size, size ));
}
void HighLightNode::drawArrow(int x, int y, Qt::Alignment Alignment)
{
    int size = 6;
    pen = new QPen(QColor(Qt::red));
    pen->setWidth(5);
    m_painter->setPen(*pen);
    switch(Alignment)
    {
        case Qt::AlignLeft:
            m_painter->drawLine(x,y,x+size,y+size);
            m_painter->drawLine(x,y,x+size,y-size);
        break;
        case Qt::AlignRight:
            m_painter->drawLine(x,y,x-size,y+size);
            m_painter->drawLine(x,y,x-size,y-size);
        break;
        case Qt::AlignTop:
            m_painter->drawLine(x,y,x-size,y-size);
            m_painter->drawLine(x,y,x+size,y-size);
        break;
        case Qt::AlignBottom:
            m_painter->drawLine(x,y,x+size,y+size);
            m_painter->drawLine(x,y,x-size,y+size);
        break;
        default:
        break;
    }
}
bool HighLightNode::inRange(QPointF p1,QPointF p2, QPointF range)
{
    if( p1.x()+range.x() > p2.x()   &&   p2.x() > p1.x()-range.x())
        if( p1.y()+range.y() > p2.y()  &&  p2.y() > p1.y()-range.y())
            return true;
    return false;
}
void HighLightNode::setCoordinate(QPointF point)
{   // set GPS position 
    for(int loop=0; loop<m_nodes->size(); loop++) 
    {
        double y = m_nodes->at(loop)->getLatitude();
        double x = m_nodes->at(loop)->getLongitude();

        if( inRange(m_mapControl->currentCoordinate(), QPointF(x,y), QPointF(0.0002,0.0002)) ) {
                emit(destinationReach(m_nodes->at(loop)));
                //qDebug()<<"signal bestemming bereikt";
                 m_nodes->removeAt(loop); // delete destination
                loop--;
        }
    }
}
void HighLightNode::drawDistance(double x,double y,int flag,Node* node)
{
    int r = distance(node);
    QString strDistance;
    if (r >1000) 
        strDistance = QVariant(r/1000 ).toString()+ "Km"; 
    else
        strDistance = QVariant(r).toString() + "m";

    switch(flag)
    {
        case Qt::AlignRight:
            m_painter->drawText(QRect(x-50,y-10,40,20),Qt::AlignRight,strDistance);
        break;
        case Qt::AlignLeft:
            m_painter->drawText(x+10,y+5,strDistance);
        break;
        case Qt::AlignTop:
            m_painter->drawText(QRect(x-20,y-25,40,20),Qt::AlignCenter,strDistance);
        break;
        case Qt::AlignBottom:
            m_painter->drawText(QRect(x-20,y+10,40,20),Qt::AlignCenter,strDistance);
        break;
    }
}
int HighLightNode::distance(Node* node)
{
    return calcDistance( m_mapControl->currentCoordinate(), QPointF(node->getLongitude(),node->getLatitude()));
}
int HighLightNode::distance(QPointF point)
{
    return calcDistance( m_mapControl->currentCoordinate(), point);
}
int HighLightNode::calcDistance(QPointF coord1, QPointF coord2)
{
    double PI = acos(-1.0);
    double a1 = coord1.x()* (PI/180.0);;
    double b1 = coord1.y()* (PI/180.0);;
    double a2 = coord2.x()* (PI/180.0);;
    double b2 = coord2.y()* (PI/180.0);;
    double r = 6378103; 
    double km = acos(cos(a1)*cos(b1)*cos(a2)*cos(b2) + cos(a1)*sin(b1)*cos(a2)*sin(b2) + sin(a1)*sin(a2)) * r;
    return km;
}
void HighLightNode::add(Node * node)
{
    m_nodes->append(node);
}
void HighLightNode::setPainter(QPainter* painter)
{
    m_painter = painter;
}
void HighLightNode::setMapAdapter(MapAdapter* mapadapter)
{
    m_mapadapter = mapadapter;
}
void HighLightNode::setMapControl(MapControl* co)
{
    m_mapControl = co;
}
void HighLightNode::remove(Node* node)
{
    int index=m_nodes->indexOf(node);
    if(index>-1)
        m_nodes->removeAt(index);
}
void HighLightNode::clear()
{
    m_nodes->clear();
}
HighLightNode::~HighLightNode()
{
}

}
