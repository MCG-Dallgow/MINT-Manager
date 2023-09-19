#include "scientificworkdialog.h"
#include "ui_scientificworkdialog.h"

ScientificWorkDialog::ScientificWorkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScientificWorkDialog)
{
    ui->setupUi(this);

    setup();
}

ScientificWorkDialog::~ScientificWorkDialog()
{
    delete ui;
}

// SLOT - show or hide edit widgets
void ScientificWorkDialog::showEdit(ScientificWork type)
{
    // hide all relevant widgets by default
    QList<QWidget*> widgets = ui->groupEdit->findChildren<QWidget*>(Qt::FindDirectChildrenOnly);
    for (QWidget *widget : widgets)
    {
        widget->setVisible(false);
    }
    widgets.clear();

    // select widgets that are always visible
    widgets << ui->gbTemplates;
    if (type != ScientificWork::NOTHING)
    {
        widgets << ui->btnSave;
        widgets << ui->groupActivity;
        widgets << ui->gbLevel;
    }

    // select widgets based on type of scientific work
    switch (type)
    {
    case ScientificWork::FACHWISSENSCHAFTLICHE_ARBEIT:
    case ScientificWork::BESONDERE_LERNLEISTUNG:
        widgets << ui->groupGrade;
        break;
    case ScientificWork::WISSENSCHAFTSPROPAEDEUTISCHES_FACH:
        widgets << ui->gbSubjectGrades;
        break;
    }

    // show selected widgets
    for (QWidget *widget : widgets)
    {
        widget->setVisible(true);
    }
}

// setup widgets
void ScientificWorkDialog::setup()
{
    // hide edit widgets
    showEdit();

    QList<QSpinBox*> spinBoxes = ui->groupEdit->findChildren<QSpinBox*>();
    for (QSpinBox *spinBox : spinBoxes)
    {
        // set default value of spin box to " "
        spinBox->setSpecialValueText(" ");

        // when value of spin box changes, call slot to display average
        connect(spinBox, &QSpinBox::valueChanged, this, &ScientificWorkDialog::displayGradeAverage);
    }

    QList<QRadioButton*> rbTemplates = ui->gbTemplates->findChildren<QRadioButton*>();
    for (QRadioButton *rbTemplate : rbTemplates)
    {
        int templateInt = rbTemplate->objectName().at(10).digitValue();
        ScientificWork templateValue = static_cast<ScientificWork>(templateInt);
        connect(rbTemplate, &QRadioButton::clicked, this, [=]{
            showEdit(templateValue);
        });
    }
}

void ScientificWorkDialog::displayGradeAverage()
{
    // get spin boxes displaying subject grades
    QRegularExpression pattern = QRegularExpression("sbSubjectGrade[1-4]");
    QList<QSpinBox*> sbSubjects = this->findChildren<QSpinBox*>(pattern);

    // get line edit displaying subject average
    QLineEdit *leAverage = this->findChild<QLineEdit*>("leSubjectAvg");

    // get list of grades from spin boxes
    QList<int> grades;
    for (QSpinBox *sbSubject : sbSubjects)
    {
        grades << sbSubject->value();
    }

    // calculate subject average
    float average = Util::average(grades);

    // format average to two decimal places
    QString averageString = average < 0
            ? ""
            : Util::formatDecimal(average, 2);

    // display average in line edit
    leAverage->setText(averageString);
}
