#pragma once

#include <QObject>
#include <QSqlTableModel>
#include <QDate>
#include <QSqlRecord>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(const int selectedRow);

    static QSqlTableModel* model();
    static Student* addStudent(const QString &firstname, const QString &lastname, const QDate &birthdate);

    QString firstname();
    QString lastname();
    QDate birthdate();
    int tableRow();
    void edit(const QString &newFirstname, const QString &newLastname, const QDate &newBirthdate);
    void remove();

private:
    explicit Student(const int id, const QString &firstname, const QString &lastname, const QDate &birthdate, QObject *parent = nullptr);

    static QSqlRecord studentRecord(const QString &firstname, const QString &lastname, const QDate &birthdate);

private:
    inline static QSqlTableModel *m_model;

    int m_id;
    QString m_firstname;
    QString m_lastname;
    QDate m_birthdate;

signals:

};

