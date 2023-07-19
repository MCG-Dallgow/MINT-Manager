#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>

EditStudentDialog::EditStudentDialog(int studentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog),
    studentId(studentId)
{
    ui->setupUi(this);

    if (studentId != -1)
    {
        setWindowTitle("Schüler bearbeiten");

        QString query = QString("SELECT * FROM students WHERE id=%1").arg(studentId);
        QSqlQueryModel model;
        model.setQuery(query);

        QString firstname = model.record(0).value("firstname").toString();
        QString lastname = model.record(0).value("lastname").toString();
        QString birthdateString = model.record(0).value("birthdate").toString();
        QDate birthdate = QDate::fromString(birthdateString, "dd.MM.yyyy");

        ui->leFirstname->setText(firstname);
        ui->leLastname->setText(lastname);
        ui->deBirthdate->setDate(birthdate);
    }
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

void EditStudentDialog::on_pushButton_clicked()
{
    QString firstname = ui->leFirstname->text();
    QString lastname = ui->leLastname->text();
    QString birthdate = ui->deBirthdate->date().toString("dd.MM.yyyy");

    QSqlQuery query;

    if (studentId == -1) {
        query.prepare("INSERT INTO students (firstname, lastname, birthdate) "
                      "VALUES (:firstname, :lastname, :birthdate)");
        query.bindValue(":firstname", firstname);
        query.bindValue(":lastname", lastname);
        query.bindValue(":birthdate", birthdate);
    }
    else
    {
        query.prepare("UPDATE students "
                      "SET firstname=:firstname, lastname=:lastname, birthdate=:birthdate "
                      "WHERE id=:id");
        query.bindValue(":firstname", firstname);
        query.bindValue(":lastname", lastname);
        query.bindValue(":birthdate", birthdate);
        query.bindValue(":id", studentId);
    }
    query.exec();

    close();
}

