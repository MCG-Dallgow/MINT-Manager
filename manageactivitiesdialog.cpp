#include "manageactivitiesdialog.h"
#include "ui_manageactivitiesdialog.h"

ManageActivitiesDialog::ManageActivitiesDialog(QWidget *parent, QString studentName) :
    QDialog(parent),
    ui(new Ui::ManageActivitiesDialog),
    studentName(studentName)
{
    ui->setupUi(this);

    ui->lblStudentName->setText(studentName);
}

ManageActivitiesDialog::~ManageActivitiesDialog()
{
    delete ui;
}
