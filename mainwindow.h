#pragma once

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "editstudentdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void displayStudents();
    void filterStudents();

private slots:
    void on_btnSearchName_clicked();
    void on_rbOnlyWithoutCert_toggled(bool checked);
    void on_btnRemoveStudent_clicked();
    void on_tblStudents_pressed(const QModelIndex &index);
    void on_btnAddStudent_clicked();
    void on_btnEditStudent_clicked();

    void onTableSelectionChanged(bool hasSelection);

public:
    QSqlTableModel *model;

private:
    Ui::MainWindow *ui;
    QString nameFilter;
    bool displayOnlyWithoutCert = false;
    QModelIndex selectedTableIndex;
    EditStudentDialog *dialog;
};

