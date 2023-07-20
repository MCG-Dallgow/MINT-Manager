#pragma once

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDir>
#include <QSqlQuery>

void setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    db.setDatabaseName(path + "/database.sqlite");

    /* DEBUG */ qInfo() << "Application Directory:" << path;

    bool ok = db.open();

    QSqlQuery setupQuery;
    ok = setupQuery.exec("CREATE TABLE IF NOT EXISTS students"
                         "(id INTEGER NOT NULL,"
                         "lastname TEXT NOT NULL,"
                         "firstname TEXT NOT NULL,"
                         "birthdate TEXT NOT NULL,"
                         "certdate TEXT,"
                         "PRIMARY KEY(id AUTOINCREMENT))");

    /* DEBUG */ qInfo() << "Database Setup" << (ok ? "Successful" : "Failed");
}

