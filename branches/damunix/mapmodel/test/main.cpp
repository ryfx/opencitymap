/***************************************************************************
 *   Copyright (C) 2008 by Michel Claessens   *
 *   michel.claessens@student.denayer.wenk.be   *
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


#include <QCoreApplication>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QLibrary>
#include <getopt.h>
#include <QtScript>
#include <QMap>
#include <QString>

#include "mapModel.h"
#include "dataInterface.h"
#include "gpx.h"
#include "osm.h"
#include "scriptConversion.cpp"

static int osm_flag;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args = QCoreApplication::arguments( );

    QList<Node*> nodes;
    QList<Way*> ways;
    QList<Relation*> relations;
    MapModel *model;
    DataInterface *di;

    QScriptEngine engine;
    QScriptValue result;
    QFile file("print_nodes.js");
    QFile testFile("testFile.js");
    model = new MapModel ( );
    
    QString name_store = "";
    QString name_load = "";
    

    // argument parser source
    // http://www.gnu.org/software/libtool/manual/libc/Getopt.html
    int c;

    while (1)
    {
        static struct option long_options[] =
        {
            {"osm",     no_argument,       &osm_flag, 1},
            {"test",    required_argument,        0, 't'},
            {"print",   no_argument,        0, 'p'},
            {"help",    no_argument,        0, 'h'},
            {"load",    required_argument,  0, 'l'},
            {"store",   required_argument,  0, 's'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long ( argc, argv, "hs:l:t:p", long_options, &option_index );

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'p':
                    if (!file.open(QFile::ReadOnly | QFile::Text)){
                         qDebug( )  << "Error: Cannot open the script file, check permissions ";
                            break;
                    }

                    engine.globalObject().setProperty("model", engine.newQObject( model ));
                    qScriptRegisterMetaType( &engine, nodeToScript, nodeFromScript );
                    qScriptRegisterSequenceMetaType< QList<Node *> >(&engine);
                    qScriptRegisterMetaType( &engine, wayToScript, wayFromScript );
                    qScriptRegisterSequenceMetaType< QList<Way *> >(&engine);

                    file.open(QIODevice::ReadOnly);
                    result = engine.evaluate(file.readAll());
                    file.close();
                    if (engine.hasUncaughtException())
                    {
                        int lineNo = engine.uncaughtExceptionLineNumber();
                        qWarning() << "line" << lineNo << ":" << result.toString();
                    }
                    

                break;
                
            case 't':
                    testFile.setFileName(optarg);
                    if (!testFile.open(QFile::ReadOnly | QFile::Text)){
                         qDebug( )  << "Error: Cannot open the script file, check permissions ";
                            break;
                    }
    
                    engine.globalObject().setProperty("model", engine.newQObject( model ));
                    qScriptRegisterMetaType( &engine, nodeToScript, nodeFromScript );
                    qScriptRegisterSequenceMetaType< QList<Node *> >(&engine);
                    qScriptRegisterMetaType( &engine, wayToScript, wayFromScript );
                    qScriptRegisterSequenceMetaType< QList<Way *> >(&engine);

                    testFile.open(QIODevice::ReadOnly);
                    result = engine.evaluate(testFile.readAll());
                    testFile.close();
                    if (engine.hasUncaughtException())
                    {
                        int lineNo = engine.uncaughtExceptionLineNumber();
                        qWarning() << "line" << lineNo << ":" << result.toString();
                    }
                    

                break;

            case 'h':
                puts ("MapModel test application can be used to:");
                puts ("Load, store, convert OSM & GPX files;");
                puts ("Print the result, manipulate the model using QtScript.\n");
                puts ("-l,   --load fileName \n        loads a file");
                puts ("-s,   --store [fileName] \n        stores a file, if no filename is set, the current time will be used.");
                puts ("        if no extension is set the file will be saved as .gpx unless the --osm flag is set.");
                puts ("-p,   --print \n        prints the model");
                puts ("-t,   --test \n        runs the script");
                puts ("-h,   --help \n        shows the help");
                break;

            case 'l':
                name_load = (QString)optarg;
                if (name_load.endsWith(".osm"))
                {
                    printf ("this command will load the osm file: `%s'\n", optarg);
                    di = new Osm( );
                }
                else if (name_load.endsWith(".gpx"))
                {
                    printf ("this command will load the gpx file: `%s'\n", optarg);
                    di = new Gpx( );
                }
                
                model = di->load( name_load );

                qDebug( ) << "Number of nodes:" << model->getNodes().size( ) << ", memsize (bytes):"
                        << sizeof(*model->getNodes()[0]) * model->getNodes().size( );
                qDebug( ) << "Number of ways:" << model->getWays().size( );
                qDebug( ) << "Number of relations:" << model->getRelations().size( );
                model->updateBounds();
                break;

            case 's':
                //model = new MapModel( );
                name_store = (QString)optarg;
                if (name_store.endsWith(".osm"))
                {
                    printf ("this command will store the osm file: `%s'\n", optarg);
                    di = new Osm( );
                }
                else if (name_store.endsWith(".gpx"))
                {
                    printf ("this command will store the gpx file: `%s'\n", optarg);
                    di = new Gpx( );
                }
                else
                {
                    if (osm_flag)
                    {
                        printf ("this command will store the osm file: `%s'\n", optarg);
                        di = new Osm( );
                    }
                    else
                    {
                        printf ("this command will store the gpx file: `%s'\n", optarg);
                        di = new Gpx( );
                    }
                }

                /*
                nodes.append (new Node (45.849600, 4.956872, 344.240, "2008-04-16T09:78:55Z"));
                nodes.append (new Node (45.849832, 4.956846, 344.255, "2008-04-16T09:78:56Z"));
                nodes.append (new Node (45.849929, 4.956834, 344.255, "2008-04-16T09:78:57Z"));
                nodes.append (new Node (45.849550, 4.956828, 344.255, "2008-04-16T09:78:59Z"));

                nodes[0]->addTag (new Tag ( "key", "valuetest") );

                ways.append(new Way (nodes));

                //Second way
                ways.append(new Way (nodes));
                qDebug() << "size: " << ways.size();
                ways[0]->addTag (new Tag ( "key", "valuetest") );
                ways[1]->addTag (new Tag ( "key", "valuetest") );

                relations.append(new Relation (ways));
                relations[0]->addTag (new Tag ( "key", "valuetest") );

                model->setNodes(nodes);
                model->setWays(ways);
                model->setRelations(relations);
                model->setTimestamp ("2008-04-17T08:52:27Z");
                */
                
                
                //Set filename
                model->setName (name_store);
                di->store(model);
                break;
        }
    }

    return 0;
}
