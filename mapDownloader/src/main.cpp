


#include <QApplication>
#include "mapdownloader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MapDownloader ta;
    ta.setWindowTitle("MapDownloader");
    ta.show();
    return app.exec();
}

