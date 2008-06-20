//
// C++ Implementation:
//
// Description: 
//
//
// Author: Wolfgang Ostes Michel Claessens 
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "script.h"

//Conversion fucntions
QVariantMap tagsToQVariantMap( Node* node )
{
    QVariantMap tagsMap;
    QList<Tag *> tags = node->getTags();
    QListIterator<Tag *> i(tags);
    while( i.hasNext() )
    {
        Tag * tag = i.next();
        tagsMap[tag->getKey()] = QVariant(tag->getValue());
    }

    return tagsMap;
}

qulonglong nodeToAddress( Node* node )
{
    qulonglong address;
    address = (unsigned long)node;
    
    return address;
}

QScriptValue nodeToScript( QScriptEngine *engine, Node* const & node )
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("latitude", QScriptValue( engine, node->getLatitude() ) );
    obj.setProperty("longitude", QScriptValue( engine, node->getLongitude() ) );
    obj.setProperty("timestamp", QScriptValue( engine, node->getTimestamp() ) );

    obj.setProperty("address", engine->toScriptValue( nodeToAddress( node ) ) );
    obj.setProperty("tags", engine->toScriptValue( tagsToQVariantMap( node ) ) );

    return obj;
}

void nodeFromScript( const QScriptValue &obj, Node* &node )
{
    node->setLatitude( obj.property("latitude").toNumber() );
    node->setLongitude( obj.property("longitude").toNumber() );
    node->setTimestamp( obj.property("timestamp").toString() );
    //node->setTimestamp( obj.property("address").toNumber() );
}

QScriptValue qActionToScript( QScriptEngine *engine, QAction* const & qAction )
{
    QScriptValue obj = engine->newObject();
    obj.setProperty("text", QScriptValue( engine, qAction->text() ) );

    return obj;
}

void qActionFromScript( const QScriptValue &obj, QAction* &qAction )
{
    qAction->setText( obj.property("text").toString() );
}



//Constructor
Script::Script(MapModel *mapmodel, QMenu *gameMenu, HighLightNode* highlightnode, QListView* view )
{
    m_mapmodel = mapmodel;
    m_gameMenu = gameMenu;
    m_highlightnode = highlightnode;
    m_view = view;
    
    //QSoftMenuBar::setLabel ( m_view, 0, QSoftMenuBar::Ok, QSoftMenuBar::AnyFocus);
    viewMenu = QSoftMenuBar::menuFor(m_view); 
    viewMenu->addAction( tr("Go!"));
    viewMenu->setTitle("listViewMenu");
    
    QFile scriptFile("/mnt/documents/scripts/main.qs");

    if (!scriptFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug( )  << "Error: Cannot open the script file, check permissions ";
        return;
    }

    //Specify conversion functions
    qScriptRegisterMetaType( &engine, nodeToScript, nodeFromScript );
    qScriptRegisterMetaType( &engine, qActionToScript, qActionFromScript );
    
    //Specify object lists
    qScriptRegisterSequenceMetaType< QList<Node *> >(&engine);

    
    //Making the object accessible in QtScript. 
    engine.globalObject().setProperty("mapmodel", engine.newQObject( m_mapmodel ));
    engine.globalObject().setProperty("gameMenu", engine.newQObject( m_gameMenu ));
    engine.globalObject().setProperty("highlightnode", engine.newQObject( m_highlightnode ));
    engine.globalObject().setProperty("listView", engine.newQObject( m_view ));
    engine.globalObject().setProperty("listViewMenu", engine.newQObject( viewMenu ));
    engine.globalObject().setProperty("script", engine.newQObject( this ));
    //engine.globalObject().setProperty("highlightnode", engine.newQObject( highlightnode ));
    

    result = engine.evaluate(scriptFile.readAll());
    scriptFile.close();
    
    
    if (engine.hasUncaughtException())
    {
        int lineNo = engine.uncaughtExceptionLineNumber();
        qWarning() << "line" << lineNo << ":" << result.toString();
    }
}

Q_INVOKABLE void Script::dispListView(QString items)
{
    QStringList itemList = items.split(",");
    QAbstractItemModel *model = new QStringListModel(itemList);
    listViewSelected.clear();
    for (int i=0; i < itemList.size(); ++i)
    {
        listViewSelected << 0; 
    }
    m_view->setWindowTitle("Items");
    m_view->setModel(model); 
    m_view->showMaximized();

    connect(m_view,SIGNAL(activated(const QModelIndex &)),
                    this,SLOT(viewactivated(const QModelIndex & )));
}

Q_INVOKABLE void Script::clearListView()
{
    m_view->hide();
    //m_view->showMinimized();
}

void Script::viewactivated(const QModelIndex & index)
{
    if (listViewSelected[index.row()])
    {
        listViewSelected[index.row()] = 0;
    }
    else
    {
        listViewSelected[index.row()] = 1;
    }
}


Q_INVOKABLE void Script::addMenuItem(QString name)
{
    newAction << new QAction( name, m_gameMenu);
    m_gameMenu->addAction( newAction.last() );
}

Q_INVOKABLE void Script::removeMenuItem(QString actionText)
{
    for (int i=0; i < newAction.size( ); ++i)
    {
        if (newAction[i]->text() == actionText)
            m_gameMenu->removeAction( newAction[i] );
    }
}

Q_INVOKABLE void Script::addHighlightNode(int nodeNumber)
{
    m_highlightnode->add( m_mapmodel->getNodes()[nodeNumber] );
}

Q_INVOKABLE void Script::removeHighlightNode(int nodeNumber)
{
    m_highlightnode->remove( m_mapmodel->getNodes()[nodeNumber] );
}

Q_INVOKABLE void Script::setGameMenuTitle(QString title)
{
    m_gameMenu->setTitle(title);
}

Q_INVOKABLE void Script::clearMenu()
{
    m_gameMenu->clear();
}


Q_INVOKABLE void Script::showMessage(QString title, QString message)
{
    emit showMessageBox(title, message);
}


Q_INVOKABLE QList<int> Script::listViewSelectedIndexes()
{
    disconnect ( m_view, SIGNAL(activated(const QModelIndex &)), this,SLOT(viewactivated(const QModelIndex & )));
    return listViewSelected;
}

Script::~Script()
{

}

