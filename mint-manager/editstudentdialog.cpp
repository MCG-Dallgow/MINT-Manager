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

    // get student data from main window
    model = ((MainWindow*) parent)->model;

    // if student is selected in table view, edit that student
    if (selectedRow != -1)
    {
        setWindowTitle("Schüler bearbeiten");

        // get student data from database
        QString firstname = model->record(selectedRow).value("firstname").toString();
        QString lastname = model->record(selectedRow).value("lastname").toString();
        QString birthdateString = model->record(selectedRow).value("birthdate").toString();
        QDate birthdate = QDate::fromString(birthdateString, "dd.MM.yyyy");

        // display student data in UI
        ui->leFirstname->setText(firstname);
        ui->leLastname->setText(lastname);
        ui->deBirthdate->setDate(birthdate);
    }
}

EditStudentDialog::~EditStudentDialog()
{
    delete ui;
}

// when save button is clicked, save new/edited student to database
void EditStudentDialog::on_btnSave_clicked()
{
    // get new/edited student data from UI
    QString firstname = ui->leFirstname->text().trimmed();
    QString lastname = ui->leLastname->text().trimmed();
    QString birthdate = ui->deBirthdate->date().toString("dd.MM.yyyy");

    // create SQL record from student data
    QSqlRecord record = model->record();
    record.setValue("firstname", firstname);
    record.setValue("lastname", lastname);
    record.setValue("birthdate", birthdate);
    record.setGenerated("id", false);

    if (selectedRow == -1) {
        // add student to database if in add mode
        model->insertRecord(-1, record);
    }
    else
    {
        // update student if in edit mode
        model->setRecord(selectedRow, record);
    }

    model->sort(1, Qt::AscendingOrder);

    close();
}

