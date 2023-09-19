#pragma once

#include <QDialog>

#include "constants.h"
#include "util.h"

namespace Ui {
class ScientificWorkDialog;
}

class ScientificWorkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScientificWorkDialog(QWidget *parent = nullptr);
    ~ScientificWorkDialog();

private:
    void setup();

private slots:
    void showEdit(ScientificWork type = ScientificWork::FACHWISSENSCHAFTLICHE_ARBEIT);
    void displayGradeAverage();

private:
    Ui::ScientificWorkDialog *ui;
};

