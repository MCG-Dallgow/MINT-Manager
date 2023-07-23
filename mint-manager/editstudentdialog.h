#pragma once

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudentDialog(QWidget *parent = nullptr, int selectedRow = -1);
    ~EditStudentDialog();

private slots:
    void on_btnSave_clicked();

private:
    Ui::EditStudentDialog *ui;
    QSqlTableModel *model;
    int selectedRow;
};

