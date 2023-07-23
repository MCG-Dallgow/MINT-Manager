#pragma once

#include <QDialog>

namespace Ui {
class ManageActivitiesDialog;
}

class ManageActivitiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageActivitiesDialog(QWidget *parent = nullptr, QString studentName = "Student");
    ~ManageActivitiesDialog();

private:
    Ui::ManageActivitiesDialog *ui;
    QString studentName;
};

