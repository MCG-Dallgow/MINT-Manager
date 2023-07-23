#include "mainwindow.h"

#include <QApplication>

#include "constants.h"
#include "database.h"

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
