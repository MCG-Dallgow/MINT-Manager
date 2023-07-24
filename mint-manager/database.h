#pragma once

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>

void setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // get path to valid application data directory
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // create appdata directory in file system, if not already present
    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    // create or access database in appdata directory
    db.setDatabaseName(path + "/database.sqlite");

    qInfo() << "Application Directory:" << path;

    bool ok = db.open();

    // create tables in database if not already present
    QSqlQuery setupQuery;
    ok = setupQuery.exec("CREATE TABLE IF NOT EXISTS students"
                         "(id INTEGER NOT NULL,"
                         "lastname TEXT NOT NULL,"
                         "firstname TEXT NOT NULL,"
                         "birthdate TEXT NOT NULL,"
                         "certdate TEXT,"
                         "PRIMARY KEY(id AUTOINCREMENT))");

    qInfo() << "Database Setup" << (ok ? "Successful" : "Failed");
}

