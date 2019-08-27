#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{

    QApplication app(argc,argv);
    MainWindow m;
    app.setActiveWindow(&m);
     m.show();
    m.resize(640,480);

    return app.exec();
}
