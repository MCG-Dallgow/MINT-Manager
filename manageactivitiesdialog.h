#pragma once

#include <QDialog>
#include <QList>

namespace Ui {
class ManageActivitiesDialog;
}

class ManageActivitiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManageActivitiesDialog(QWidget *parent = nullptr, QString studentName = "Schüler");
    ~ManageActivitiesDialog();

private:
    float gradeAverage(QList<float> grades);
    float gradeAverage(QList<int> grades);
    QString formatAverage(float average);
    void setupWidgets();

private slots:
    void toggleSubject(int subject, bool state);
    void displayGradeAverage(int subject);
    void displayTotalAverage();

private:
    Ui::ManageActivitiesDialog *ui;
    QString studentName;
    QList<float> subjectAverages = QList<float>(4, -1.0);
};

