#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class EditStudentDialog;
}

class EditStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStudentDialog(int studentId = -1, QWidget *parent = nullptr);
    ~EditStudentDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EditStudentDialog *ui;
    int studentId;
};

#endif // EDITSTUDENTDIALOG_H
