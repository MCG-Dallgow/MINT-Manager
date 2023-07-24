#include "manageactivitiesdialog.h"
#include "ui_manageactivitiesdialog.h"

#include "constants.h"
#include "util.h"

// SLOT - enable given subject
void ManageActivitiesDialog::toggleSubject(int subject, bool state)
{
    // get widgets corresponding to subject
    QString pattern = QString("(cmb|sb|le)Subject%1.*").arg(subject);
    QList<QWidget*> widgets = this->findChildren<QWidget*>(QRegularExpression(pattern));

    // enable or disable widgets
    for (QWidget *widget : widgets)
    {
        widget->setEnabled(state);
    }
}

// SLOT - display grade average of subject in corresponding line edit
void ManageActivitiesDialog::displayGradeAverage(int subject)
{
    // get spin boxes displaying subject grades
    QString pattern = QString("sbSubject%1Grade[1-4]").arg(subject);
    QList<QSpinBox*> sbSubjects =  this->findChildren<QSpinBox*>(pattern);

    // get line edit displaying subject average
    QString objectName = QString("leSubject%1Avg").arg(subject);
    QLineEdit *leAverage = this->findChild<QLineEdit*>(objectName);

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

    // calculate and display total average
    subjectAverages[subject - 1] = average;
    displayTotalAverage();
}

// SLOT - calculate and display total average in corresponding line edit
void ManageActivitiesDialog::displayTotalAverage()
{
    // calculate total average
    float totalAverage = Util::average(subjectAverages);

    // format total average to two decimal places
    QString totalAverageString = totalAverage < 0
            ? ""
            : Util::formatDecimal(totalAverage, 2);

    // display total average in line edit
    ui->leTotalAvg->setText(totalAverageString);
}

// setup widgets
void ManageActivitiesDialog::setupWidgets()
{
    // set label text to name of student
    ui->lblStudentName->setText(studentName);

    // iterate through all widgets in grid layout
    for (int i = 0; i < ui->gridLayout->count(); i++)
    {
        QWidget *widget = ui->gridLayout->itemAt(i)->widget();

        // if widget is radio button, setup signal to enable subject widgets
        if (QRadioButton *radioButton = qobject_cast<QRadioButton*>(widget))
        {
            // get subject number of radio button
            int subject = radioButton->objectName().at(9).digitValue();

            // when radion button is toggled, call slot to enable subject
            connect(radioButton, &QRadioButton::toggled, this, [=]{
                toggleSubject(subject, true);
            });
        }

        // if widget is check box, setup signal to toggle subject widgets
        if (QCheckBox *checkBox = qobject_cast<QCheckBox*>(widget))
        {
            // get subject number of check box
            int subject = checkBox->objectName().at(9).digitValue();

            // when radion button is toggled, call slot to toggle subject
            connect(checkBox, &QCheckBox::toggled, this, [=]{
                toggleSubject(subject, checkBox->isChecked());
            });
        }

        // if widget is combo box, setup subjects as items
        if (QComboBox *comboBox = qobject_cast<QComboBox*>(widget))
        {
            comboBox->addItem("");
            comboBox->addItems(MINT_SUBJECTS);
        }

        // if widget is spin box, set default value and setup signal to display average
        if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(widget))
        {
            // set default value of spin box to " "
            spinBox->setSpecialValueText(" ");

            // get subject number of spin box
            int subject = spinBox->objectName().at(9).digitValue();

            // when value of spin box changes, call slot to display average
            connect(spinBox, &QSpinBox::valueChanged, this, [=]{
                displayGradeAverage(subject);
            });
        }
    }
}

ManageActivitiesDialog::ManageActivitiesDialog(QWidget *parent, QString studentName) :
    QDialog(parent),
    ui(new Ui::ManageActivitiesDialog),
    studentName(studentName)
{
    ui->setupUi(this);

    setupWidgets();
}

ManageActivitiesDialog::~ManageActivitiesDialog()
{
    delete ui;
}
