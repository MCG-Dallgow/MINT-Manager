#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlField>

#include "mainwindow.h"

EditStudentDialog::EditStudentDialog(QWidget *parent, int selectedRow) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog),
    selectedRow(selectedRow)
{
    ui->setupUi(this);

    model = ((MainWindow*) parent)->model;

    if (selectedRow != -1)
    {
        setWindowTitle("Schüler bearbeiten");

        QString firstname = model->record(selectedRow).value("firstname").toString();
        QString lastname = model->record(selectedRow).value("lastname").toString();
        QString birthdateString = model->record(selectedRow).value("birthdate").toString();
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

    QSqlRecord record = model->record();
    record.setValue("firstname", firstname);
    record.setValue("lastname", lastname);
    record.setValue("birthdate", birthdate);
    record.setGenerated("id", false);

    if (selectedRow == -1) {
        model->insertRecord(-1, record);
    }
    else
    {
        model->setRecord(selectedRow, record);
    }

    model->sort(1, Qt::AscendingOrder);

    close();
}

