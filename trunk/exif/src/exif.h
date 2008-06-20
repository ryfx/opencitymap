

#ifndef EXIF_H
#define EXIF_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFile>

class QAction;
class QMenu;
class QTextEdit;

class exif:public QMainWindow
{
      Q_OBJECT

public:
      exif();

private:
//     QByteArray* exifData;
	QFile *file3;
   
};

#endif
