#include "mainwindow.h"

#include <QApplication>

#define APPLICATION_NAME "MINT-Verwaltung"
#define APPLICATION_VERSION "0.1.0"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
