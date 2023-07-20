#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

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
    void on_pushButton_clicked();

private:
    Ui::EditStudentDialog *ui;
    QSqlTableModel *model;
    int selectedRow;
};

#endif // EDITSTUDENTDIALOG_H
