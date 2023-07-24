#pragma once

#include <QDialog>
#include <QList>

#include "student.h"

namespace Ui {
class ManageActivitiesDialog;
}

class ManageActivitiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageActivitiesDialog(QWidget *parent = nullptr, Student *student = nullptr);
    ~ManageActivitiesDialog();

private:
    void setupWidgets();

private slots:
    void toggleSubject(int subject, bool state);
    void displayGradeAverage(int subject);
    void displayTotalAverage();

private:
    Ui::ManageActivitiesDialog *ui;
    Student *student;
    QList<float> subjectAverages = QList<float>(5, -1.0);
};

