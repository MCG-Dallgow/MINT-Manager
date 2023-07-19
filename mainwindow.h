#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void setupDatabase();
    void displayStudents();

private slots:
    void on_btnSearchName_clicked();

    void on_rbOnlyWithoutCert_toggled(bool checked);

    void on_btnRemoveStudent_clicked();

    void on_tblStudents_pressed(const QModelIndex &index);

    void on_btnAddStudent_clicked();

    void on_btnEditStudent_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QString nameFilter = "";
    bool displayOnlyWithoutCert = false;
    QModelIndex selectedTableIndex;
    EditStudentDialog *dialog;
};
#endif // MAINWINDOW_H
