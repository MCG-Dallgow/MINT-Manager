#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlRecord>

#include "student.h"
#include "editstudentdialog.h"
#include "manageactivitiesdialog.h"

// get student data from database and display it in table view
void MainWindow::displayStudents()
{
    // get student data from database
    Student::model();

    // display data in table view
    ui->tblStudents->setModel(Student::model());
    ui->tblStudents->hideColumn(0);
    ui->tblStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// filter students by name and whether they already have a certificate
void MainWindow::filterStudents()
{
    QStringList filter;

    // if a name filter is set, filter by first or last name
    if (!nameFilter.isEmpty())
    {
        filter.append(QString("firstname LIKE '%%1%' OR lastname LIKE '%%1%'").arg(nameFilter));
    }

    // if active, filter out students that already have a certificate
    if (displayOnlyWithoutCert)
    {
        filter.append("certdate IS NULL");
    }

    // apply filters to student data
    Student::model()->setFilter(filter.join(" AND "));

    /* DEBUG */ qInfo() << Student::model()->filter();
}

// SLOT - enable or disable buttons when called
void MainWindow::onTableSelectionChanged(bool hasSelection)
{
    ui->btnEditStudent->setEnabled(hasSelection);
    ui->btnRemoveStudent->setEnabled(hasSelection);
    ui->btnManageActivities->setEnabled(hasSelection);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displayStudents();

    // execute slot when selection in table view changes
    const QItemSelectionModel *selection = ui->tblStudents->selectionModel();
    connect(selection, &QItemSelectionModel::selectionChanged, this, [=]{ onTableSelectionChanged(selection->hasSelection()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// when search button is clicked, update name filter
void MainWindow::on_btnSearchName_clicked()
{
    nameFilter = ui->leSearchName->text().trimmed();

    filterStudents();
    onTableSelectionChanged(false);
}

// when radio button is selected, only display students without certificate
void MainWindow::on_rbOnlyWithoutCert_toggled(bool checked)
{
    displayOnlyWithoutCert = checked;

    filterStudents();
    onTableSelectionChanged(false);
}

// when remove button is clicked, delete selected student from database
void MainWindow::on_btnRemoveStudent_clicked()
{
    selectedStudent->remove();
    onTableSelectionChanged(false);
}

// when table row is pressed, update selected student
void MainWindow::on_tblStudents_pressed(const QModelIndex &index)
{
    selectedStudent = new Student(index.row());
}

// when add button is clicked, open dialog to add new student
void MainWindow::on_btnAddStudent_clicked()
{
    editStudentDialog = new EditStudentDialog(this);
    editStudentDialog->show();
    onTableSelectionChanged(false);
}

// when edit button is clicked, open dialog to edit selected student
void MainWindow::on_btnEditStudent_clicked()
{
    editStudentDialog = new EditStudentDialog(this, selectedStudent);
    editStudentDialog->show();
    onTableSelectionChanged(false);
}

// when manage activities button is clicked, open
// dialog to manage MINT activities of selected student
void MainWindow::on_btnManageActivities_clicked()
{
    manageActivitiesDialog = new ManageActivitiesDialog(this, selectedStudent);
    manageActivitiesDialog->show();
}

