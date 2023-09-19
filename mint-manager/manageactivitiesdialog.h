#pragma once

#include <QDialog>
#include <QList>

#include "constants.h"
#include "student.h"
#include "scientificworkdialog.h"
#include "util.h"

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
    void setupTab1();
    void setupWidgets();

private slots:
    void toggleSubject(int subject, bool state);
    void displayGradeAverage(int subject);
    void displayTotalAverage();

    void on_tab2_btnAddEntry_clicked();

private:
    Ui::ManageActivitiesDialog *ui;
    ScientificWorkDialog *scientificWorkDialog;
    Student *student;
    QList<float> subjectAverages = QList<float>(5, -1.0);
};

