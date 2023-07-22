#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlRecord>

#include "editstudentdialog.h"

// get student data from database and display it in table view
void MainWindow::displayStudents()
{
    // get student data from database
    model->setTable("students");
    model->setSort(1, Qt::AscendingOrder);
    model->select();

    // set header labels to increase readability
    model->setHeaderData(1, Qt::Horizontal, "Nachname");
    model->setHeaderData(2, Qt::Horizontal, "Vorname");
    model->setHeaderData(3, Qt::Horizontal, "Geburtsdatum");
    model->setHeaderData(4, Qt::Horizontal, "Zertifikat");

    // display data in table view
    ui->tblStudents->setModel(model);
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
    model->setFilter(filter.join(" AND "));

    /* DEBUG */ qInfo() << model->filter();
}

// SLOT - enable or disable buttons when called
void MainWindow::onTableSelectionChanged(bool hasSelection)
{
    ui->btnEditStudent->setEnabled(hasSelection);
    ui->btnRemoveStudent->setEnabled(hasSelection);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel;
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
    model->removeRow(selectedTableIndex.row());
    model->select();
    onTableSelectionChanged(false);
}

// when table row is pressed, update selected student
void MainWindow::on_tblStudents_pressed(const QModelIndex &index)
{
    selectedTableIndex = index;
}

// when add button is clicked, open dialog to add new student
void MainWindow::on_btnAddStudent_clicked()
{
    dialog = new EditStudentDialog(this, -1);
    dialog->show();
    onTableSelectionChanged(false);
}

// when edit button is clicked, open dialog to edit selected student
void MainWindow::on_btnEditStudent_clicked()
{
    dialog = new EditStudentDialog(this, selectedTableIndex.row());
    dialog->show();
    onTableSelectionChanged(false);
}

