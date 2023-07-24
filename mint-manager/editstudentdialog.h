#pragma once

#include <QDialog>
#include <QSqlTableModel>

#include "student.h"

namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudentDialog(QWidget *parent = nullptr, Student *student = nullptr);
    ~EditStudentDialog();

private slots:
    void on_btnSave_clicked();

private:
    Ui::EditStudentDialog *ui;
    QSqlTableModel *model;
    Student *student;
};

