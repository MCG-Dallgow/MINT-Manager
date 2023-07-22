#include "mainwindow.h"

#include <QApplication>

#include "database.h"

#define APPLICATION_NAME "MINT-Verwaltung"
#define APPLICATION_VERSION "0.1.0"

int main(int argc, char *argv[])
{
    // set application name and version
    QCoreApplication::setApplicationName(APPLICATION_NAME);
    QCoreApplication::setApplicationVersion(APPLICATION_VERSION);

    QApplication a(argc, argv);

    setupDatabase();

    MainWindow w;
    w.show();

    return a.exec();
}
