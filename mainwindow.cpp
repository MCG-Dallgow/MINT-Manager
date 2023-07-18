#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/test.sqlite";
    db.setDatabaseName(path);

    /* DEBUG */ qInfo() << path;

    bool ok = db.open();

    QSqlQuery setupQuery;
    ok = setupQuery.exec("CREATE TABLE IF NOT EXISTS students"
                         "(id INTEGER NOT NULL, "
                         "lastname TEXT NOT NULL, "
                         "firstname TEXT NOT NULL, "
                         "birthdate TEXT NOT NULL,"
                         "certdate TEXT,"
                         "PRIMARY KEY(id AUTOINCREMENT))");

    /* DEBUG */ qInfo() << (ok ? "Successful" : "Failed") << setupQuery.lastError();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

