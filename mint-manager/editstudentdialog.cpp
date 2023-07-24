#include "editstudentdialog.h"
#include "ui_editstudentdialog.h"

#include "mainwindow.h"
#include "student.h"

EditStudentDialog::EditStudentDialog(QWidget *parent, Student *student) :
    QDialog(parent),
    ui(new Ui::EditStudentDialog),
    student(student)
{
    ui->setupUi(this);

    // if student is selected in table view, edit that student
    if (student != nullptr)
    {
        setWindowTitle("Schüler bearbeiten");

        // display student data in UI
        ui->leFirstname->setText(student->firstname());
        ui->leLastname->setText(student->lastname());
        ui->deBirthdate->setDate(student->birthdate());
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
    QDate birthdate = ui->deBirthdate->date();

    if (student == nullptr) {
        // add student to database if in add mode
        Student::addStudent(firstname, lastname, birthdate);
    }
    else
    {
        // update student if in edit mode
        student->edit(firstname, lastname, birthdate);
    }

    close();
}

