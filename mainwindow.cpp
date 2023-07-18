#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QSqlRecord>

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/test.sqlite";
    db.setDatabaseName(path);

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

    if (nameFilter != "")
        model->setFilter(QString("firstname LIKE '%%1%' OR lastname LIKE '%%1%'").arg(nameFilter));

    if (displayOnlyWithoutCert)
        model->setFilter("certdate IS NULL");

    model->setSort(1, Qt::AscendingOrder);
    model->select();

    model->setHeaderData(1, Qt::Horizontal, "Nachname");
    model->setHeaderData(2, Qt::Horizontal, "Vorname");
    model->setHeaderData(3, Qt::Horizontal, "Geburtsdatum");
    model->setHeaderData(4, Qt::Horizontal, "Zertifikat");

    ui->tblStudents->setModel(model);
    ui->tblStudents->hideColumn(0);
    ui->tblStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblStudents->show();
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
    displayStudents();

    /* DEBUG */ qInfo() <<  "Search:" << nameFilter;
}


void MainWindow::on_rbOnlyWithoutCert_toggled(bool checked)
{
    displayOnlyWithoutCert = checked;
    displayStudents();
}


void MainWindow::on_btnRemoveStudent_clicked()
{
    int studentId = model->record(selectedTableIndex.row()).value(0).value<int>();

    /* DEBUG */ qInfo() << " Deleted Student ID:" << studentId;

    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id=:id");
    query.bindValue(":id", studentId);
    query.exec();

    displayStudents();
}


void MainWindow::on_tblStudents_pressed(const QModelIndex &index)
{
    selectedTableIndex = index;
}

