/***************************************************************************
 *   Copyright (C) 2007 by Kai Winter   *
 *   kaiwinter@gmx.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "mapcontrol.h"
namespace qmapcontrol
{
	MapControl::MapControl(QSize size, MouseMode mousemode)
	: size(size), mymousemode(mousemode)
	{
		layermanager = new LayerManager(this, size);
		screen_middle = QPoint(size.width()/2, size.height()/2);
	
		mousepressed = false;
	
		connect(ImageManager::instance(), SIGNAL(imageReceived()),
				  this, SLOT(updateRequestNew()));
	
		connect(ImageManager::instance(), SIGNAL(loadingFinished()),
				  this, SLOT(loadingFinished()));
	
		this->setMaximumSize(size.width()+1, size.height()+1);
        m_highLightNodeSet = false;
        m_loadingFlag = false;
	}
    MapControl::MapControl(QWidget* parent)
    : QWidget(parent)
    {
        mymousemode = Panning;
        mousepressed = false;
        m_highLightNodeSet = false;
        m_loadingFlag = false;
        
    
    }
	MapControl::~MapControl()
	{
		delete layermanager;	
	}

    void MapControl::init()
    {
        size=QSize(QWidget::size());
        qDebug()<< "is visible ?"<< isVisible();
        qDebug() << "size :" << size;
        qDebug() << "geometry :" << QWidget::geometry();
        qDebug() << "sizeHint:" << QWidget::sizeHint();

		
    }
	QPointF	MapControl::currentCoordinate() const
	{
		return layermanager->currentCoordinate();
	}

	Layer* MapControl::layer(const QString& layername) const
	{
		return layermanager->layer(layername);
	}

	QList<QString> MapControl::layers() const
	{
		return layermanager->layers();
	}

	int MapControl::numberOfLayers() const
	{
		return layermanager->layers().size();
	}

	void MapControl::followGeometry(const Geometry* geom) const
	{
		connect(geom, SIGNAL(positionChanged(Geometry*)),
				  this, SLOT(positionChanged(Geometry*)));
	}

	void MapControl::positionChanged(Geometry* geom)
	{
		QPoint start = layermanager->layer()->mapadapter()->coordinateToDisplay(currentCoordinate());
		QPoint dest = layermanager->layer()->mapadapter()->coordinateToDisplay(((Point*)geom)->coordinate());

		QPoint step = (dest-start);

		layermanager->scrollView(step);
	
// 	setView(geom);
		update();
	}

	void MapControl::moveTo(QPointF coordinate)
	{
		target = coordinate;
		steps = 25;
		if (moveMutex.tryLock())
		{
			QTimer::singleShot(40, this, SLOT(tick()));	
		}
		else
		{
// 		stopMove(coordinate);
		}
	}
	void MapControl::tick()
	{
		QPoint start = layermanager->layer()->mapadapter()->coordinateToDisplay(currentCoordinate());
		QPoint dest = layermanager->layer()->mapadapter()->coordinateToDisplay(target);
	
		QPoint step = (dest-start)/steps;
		QPointF next = currentCoordinate()- step;

// 	setView(Coordinate(next.x(), next.y()));
		layermanager->scrollView(step);
	
		update();
		steps--;
		if (steps>0)
		{
			QTimer::singleShot(40, this, SLOT(tick()));
		}
		else
		{
			moveMutex.unlock();
		}
	}
    // added by wolf
    QSize MapControl::getScreenSize()
    {
        return size; 
    }
    // added by wolf
    void MapControl::setHighLightNode(HighLightNode * highLightNode)
    {
        m_highLightNode = highLightNode;
        m_highLightNode->setMapControl(this);
        m_highLightNodeSet = true;
    }

	void MapControl::paintEvent(QPaintEvent* evnt)
	{
		QWidget::paintEvent(evnt);
		QPainter painter(this);
	
		layermanager->drawImage(&painter);
		layermanager->drawGeoms(&painter);

        if (m_highLightNodeSet) 
        {
            m_highLightNode->setPainter(&painter);
            m_highLightNode->paint();
        }
        // draw scale
        QList<double> distanceList;
        distanceList<<5000000<<2000000<<1000000<<1000000<<1000000<<100000<<100000<<50000<<50000<<10000<<10000<<10000<<1000<<1000<<500<<200<<100<<50<<25;
        double line;
        if (currentZoom() < distanceList.size() && currentZoom()>=0)
        {
            line = distanceList.at( currentZoom() ) / pow(2, 18-currentZoom() ) / 0.597164;

            // draw the scale
            painter.setPen(Qt::black);
            QPoint p1(10,size.height()-20);
            QPoint p2(line,size.height()-20);
            painter.drawLine(p1,p2);
    
            painter.drawLine(10,size.height()-15, 10,size.height()-25); 
            painter.drawLine(line,size.height()-15, line,size.height()-25); 
    
            QString distance;
            if (distanceList.at(currentZoom()) >= 1000) 
            {
                distance = QVariant( distanceList.at(currentZoom())/1000 ).toString()+ " Km";
            }
            else
            {
                distance = QVariant( distanceList.at(currentZoom()) ).toString() + " m";
            }
    
            painter.drawText(QPoint(line+10,size.height()-15), distance);
        }

        // Draw map cross
		painter.drawLine(screen_middle.x(), screen_middle.y()-10,
							  screen_middle.x(), screen_middle.y()+10); // |
		painter.drawLine(screen_middle.x()-10, screen_middle.y(),
							  screen_middle.x()+10, screen_middle.y()); // -
	

	
		painter.drawRect(0,0, size.width(), size.height());

        if (m_loadingFlag) 
        {
            painter.setPen(Qt::black);
            painter.drawText(QPoint(size.width()/2-11*3,size.height()/2), "Loading...");
            m_loadingFlag = false;
        }

		if (mousepressed && mymousemode == Dragging)
		{
			QRect rect = QRect(pre_click_px, current_mouse_pos);
			painter.drawRect(rect);
		}
 	}

// mouse events
	void MapControl::mousePressEvent(QMouseEvent* evnt)
	{
	//rotating
	
// 	QMouseEvent* me = new QMouseEvent(evnt->type(), qm.map(QPoint(evnt->x(),evnt->y())), evnt->button(), evnt->buttons(), evnt->modifiers());
// 	evnt = me;
// 	qDebug() << "evnt: " << evnt->x() << ", " << evnt->y() << ", " << evnt->pos();

	
		layermanager->mouseEvent(evnt);
	
		if (layermanager->layers().size()>0)
		{
			if (evnt->button() == 1)
			{
				mousepressed = true;
				pre_click_px = QPoint(evnt->x(), evnt->y());
			}
			else if (evnt->button() == 2 && mymousemode != None)	// zoom in
			{
				zoomIn();
			} else if  (evnt->button() == 4 && mymousemode != None)	// zoom out
			{
				zoomOut();
			}
		}
	
// 	emit(mouseEvent(evnt));
		emit(mouseEventCoordinate(evnt, clickToWorldCoordinate(evnt->pos())));
	}

	void MapControl::mouseReleaseEvent(QMouseEvent* evnt)
	{
		mousepressed = false;
		if (mymousemode == Dragging)
		{
			QPointF ulCoord = clickToWorldCoordinate(pre_click_px);
			QPointF lrCoord = clickToWorldCoordinate(current_mouse_pos);
		
			QRectF coordinateBB = QRectF(ulCoord, QSizeF( (lrCoord-ulCoord).x(), (lrCoord-ulCoord).y()));

			emit(boxDragged(coordinateBB));
		}
	
		emit(mouseEventCoordinate(evnt, clickToWorldCoordinate(evnt->pos())));
	}

	void MapControl::mouseMoveEvent(QMouseEvent* evnt)
	{
// 	emit(mouseEvent(evnt));
	
	/*
	// rotating
		QMouseEvent* me = new QMouseEvent(evnt->type(), qm.map(QPoint(evnt->x(),evnt->y())), evnt->button(), evnt->buttons(), evnt->modifiers());
		evnt = me;
	*/
		if (mousepressed && mymousemode == Panning)
		{
			QPoint offset = pre_click_px - QPoint(evnt->x(), evnt->y());
			layermanager->scrollView(offset);
			pre_click_px = QPoint(evnt->x(), evnt->y());
		}
		else if (mousepressed && mymousemode == Dragging)
		{
			current_mouse_pos = QPoint(evnt->x(), evnt->y());
		}
// 	emit(mouseEventCoordinate(evnt, clickToWorldCoordinate(evnt->pos())));

		update();
// 	emit(mouseEventCoordinate(evnt, clickToWorldCoordinate(evnt->pos())));
	}


	QPointF MapControl::clickToWorldCoordinate(QPoint click)
	{
	// click coordinate to image coordinate
		QPoint displayToImage= QPoint(click.x()-screen_middle.x()+layermanager->getMapmiddle_px().x(),
												click.y()-screen_middle.y()+layermanager->getMapmiddle_px().y());
	// image coordinate to world coordinate
		return layermanager->layer()->mapadapter()->displayToCoordinate(displayToImage);
	}

	void MapControl::updateRequest(QRect rect)
	{
		update(rect);
	}
	void MapControl::updateRequestNew()
	{
// 	qDebug() << "MapControl::updateRequestNew()";
		layermanager->forceRedraw();
		update();
	}
// slots
	void MapControl::zoomIn()
	{
        m_loadingFlag=true;
        update();
		layermanager->zoomIn();
		update();
	}
	void MapControl::zoomOut()
	{
        m_loadingFlag=true;
        update();
 		layermanager->zoomOut();
 		update();
	}
	void MapControl::setZoom(int zoomlevel)
	{
		layermanager->setZoom(zoomlevel);
		update();
	}
	int MapControl::currentZoom() const
	{
		return layermanager->currentZoom();
	}
	void MapControl::scrollLeft(int pixel)
	{
		layermanager->scrollView(QPoint(-pixel,0));
		update();
	}
	void MapControl::scrollRight(int pixel)
	{
		layermanager->scrollView(QPoint(pixel,0));
		update();
	}
	void MapControl::scrollUp(int pixel)
	{
		layermanager->scrollView(QPoint(0,-pixel));
		update();
	}
	void MapControl::scrollDown(int pixel)
	{
		layermanager->scrollView(QPoint(0,pixel));
		update();
	}
	void MapControl::scroll(const QPoint scroll)
	{
		layermanager->scrollView(scroll);
		update();
	}

	void MapControl::setView(const QPointF& coordinate) const
	{
		layermanager->setView(coordinate);
	}

	void MapControl::setView(const QList<QPointF> coordinates) const
	{
		layermanager->setView(coordinates);
	}

	void MapControl::setViewAndZoomIn(const QList<QPointF> coordinates) const
	{
		layermanager->setViewAndZoomIn(coordinates);
	}

	void MapControl::setView(const Point* point) const
	{
		layermanager->setView(point->coordinate());
	}

	void MapControl::loadingFinished()
	{
// 	qDebug() << "MapControl::loadingFinished()";
		layermanager->removeZoomImage();
	}
	void MapControl::addLayer(Layer* layer)
	{
		layermanager->addLayer(layer);
	}

	void MapControl::setMouseMode(MouseMode mousemode)
	{
		mymousemode = mousemode;
	}
	MapControl::MouseMode MapControl::mouseMode()
	{
		return mymousemode;
	}

	void MapControl::stopFollowing(Geometry* geom)
	{
		geom->disconnect(SIGNAL(positionChanged(Geometry*)));
	}
	
	void MapControl::showEvent ( QShowEvent * event ) 
	{
		QWidget::showEvent(event);
		qDebug("Show event !");
		//TODO : check if this is really the first one
		size=QSize(QWidget::size());
		qDebug()<< "is visible ?"<< isVisible();
		qDebug() << "size :" << size;
		qDebug() << "geometry :" << QWidget::geometry();
		qDebug() << "sizeHint:" << QWidget::sizeHint();
		connect(ImageManager::instance(), SIGNAL(imageReceived()),
				this, SLOT(updateRequestNew()));
    
		connect(ImageManager::instance(), SIGNAL(loadingFinished()),
				this, SLOT(loadingFinished()));
		
		layermanager = new LayerManager(this, size);
		screen_middle = QPoint(size.width()/2, size.height()/2);
    
		this->setMaximumSize(size.width()+1, size.height()+1);
		emit mcReady();
        
	}
}
