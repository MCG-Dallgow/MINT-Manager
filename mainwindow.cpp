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

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    db.setDatabaseName(path + "/database.sqlite");

    /* DEBUG */ qInfo() << path;

    bool ok = db.open();

    QSqlQuery setupQuery;
    ok = setupQuery.exec("CREATE TABLE IF NOT EXISTS students"
                         "(id INTEGER NOT NULL, "
                         "lastname TEXT NOT NULL, "
                         "firstname TEXT NOT NULL, "
                         "birthdate TEXT NOT NULL,"
                         "certdate TEXT,"
                         "PRIMARY KEY(id AUTOINCREMENT))");

    /* DEBUG */ qInfo() << (ok ? "Successful" : "Failed") << setupQuery.lastError();
}

void MainWindow::displayStudents()
{
    model->setTable("students");
    model->setSort(1, Qt::AscendingOrder);
    model->select();

    model->setHeaderData(1, Qt::Horizontal, "Nachname");
    model->setHeaderData(2, Qt::Horizontal, "Vorname");
    model->setHeaderData(3, Qt::Horizontal, "Geburtsdatum");
    model->setHeaderData(4, Qt::Horizontal, "Zertifikat");

    ui->tblStudents->setModel(model);
    ui->tblStudents->hideColumn(0);
    ui->tblStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::filterStudents()
{
    QStringList filter;

    if (!nameFilter.isEmpty())
    {
        filter.append(QString("firstname LIKE '%%1%' OR lastname LIKE '%%1%'").arg(nameFilter));
    }

    if (displayOnlyWithoutCert)
    {
        filter.append("certdate IS NULL");
    }

    model->setFilter(filter.join(" AND "));

    /* DEBUG */ qInfo() << model->filter();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupDatabase();

    model = new QSqlTableModel;
    displayStudents();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSearchName_clicked()
{
    nameFilter = ui->leSearchName->text().trimmed();

    filterStudents();
}


void MainWindow::on_rbOnlyWithoutCert_toggled(bool checked)
{
    displayOnlyWithoutCert = checked;

    filterStudents();
}


void MainWindow::on_btnRemoveStudent_clicked()
{
    model->removeRow(selectedTableIndex.row());
    model->select();
}


void MainWindow::on_tblStudents_pressed(const QModelIndex &index)
{
    selectedTableIndex = index;
}


void MainWindow::on_btnAddStudent_clicked()
{
    dialog = new EditStudentDialog(this, -1);
    dialog->open();
}


void MainWindow::on_btnEditStudent_clicked()
{
    qInfo() << selectedTableIndex;
    int studentId = selectedTableIndex.row() == -1
                        ? -1
                        : model->record(selectedTableIndex.row()).value(0).value<int>();
    qInfo() << studentId;

    dialog = new EditStudentDialog(this, selectedTableIndex.row());
    dialog->open();
}

