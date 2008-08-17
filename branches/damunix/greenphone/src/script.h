//
// C++ Interface:
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef SCRIPT_H
#define SCRIPT_H

#include <QObject>
#include <QDebug>
#include <QtGui>
#include <QtScript>
#include <QVariantMap>
#include <QFile>
#include <QString>
#include <QSoftMenuBar>

#include "mapModel.h"
#include "dataInterface.h"
#include "gpx.h"
#include "osm.h"
#include "../QMapControl/src/highlightnode.h"

/**
    @author wolf,,, <wolf@laptop>
*/
using namespace qmapcontrol;
Q_DECLARE_METATYPE( Node * )
Q_DECLARE_METATYPE( QList<Node *> )
Q_DECLARE_METATYPE( Tag * )
Q_DECLARE_METATYPE( QList<Tag *> )
Q_DECLARE_METATYPE( QAction * )


class Script : public QObject
{
    Q_OBJECT
    
    public:
        Script(MapModel* mapmodel, QMenu* m_gameMenu, HighLightNode* highlightnode, QListView* view);
        ~Script();
        
        Q_INVOKABLE void addHighlightNode(int nodeNumber);
        Q_INVOKABLE void removeHighlightNode(int nodeNumber);
        Q_INVOKABLE void setGameMenuTitle(QString title);
        Q_INVOKABLE void addMenuItem(QString name);
        Q_INVOKABLE void removeMenuItem(QString actionText);
        Q_INVOKABLE void clearMenu();
        Q_INVOKABLE void showMessage(QString title, QString message);
        Q_INVOKABLE void dispListView(QString items);
        Q_INVOKABLE void clearListView();
        Q_INVOKABLE QList<int> listViewSelectedIndexes();
        
    private:
        QMenu* m_gameMenu;
        MapModel* m_mapmodel;
        HighLightNode* m_highlightnode;
        QListView* m_view;
        
        
        QMenu* viewMenu;
        QList<int> listViewSelected;
        QScriptEngine engine;
        QScriptValue result;
        QList <QAction*> newAction;
        

    public slots:
        void viewactivated(const QModelIndex & index);
        
    signals:
        void showMessageBox(QString title, QString message);

};

#endif

