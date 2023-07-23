#include "manageactivitiesdialog.h"
#include "ui_manageactivitiesdialog.h"

#include "constants.h"

// get average of given grades or averages
float ManageActivitiesDialog::gradeAverage(QList<float> grades)
{
    // remove negative values and return 0 if empty
    grades.removeIf([](float grade) { return grade < 0; });
    if (grades.isEmpty()) return 0;

    // calculate sum of grades
    float sum = 0;
    for (float grade : grades)
    {
        if (grade >= 0) sum += grade;
    }

    // calculate and return average
    return sum / (float)grades.length();
}

// OVERLOAD - get average of given grades
float ManageActivitiesDialog::gradeAverage(QList<int> grades)
{
    // cast int list to float list
    QList<float> gradesFloat;
    for (int grade : grades)
    {
        gradesFloat << (float)grade;
    }

    return gradeAverage(gradesFloat);
}

// format grade average to two decimal places
QString ManageActivitiesDialog::formatAverage(float average)
{
    return QString::number(QString::number(average, 'f', 2).toDouble(), 'g', 10);
}

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
    QList<QSpinBox*> sbSubjects;
    for (int i = 1; i <= 4; i++)
    {
        QString objectName = QString("sbSubject%1Grade%2").arg(subject).arg(i);
        sbSubjects << this->findChild<QSpinBox*>(objectName);
    }

    // get line edit displaying subject average
    QString objectName = QString("leSubject%1Avg").arg(subject);
    QLineEdit *leAverage = this->findChild<QLineEdit*>(objectName);

    // get list of grades from spin boxes
    QList<int> grades;
    for (QSpinBox *sbSubject : sbSubjects)
    {
        grades.append(sbSubject->value());
    }

    // calculate subject average
    float average = gradeAverage(grades);

    // format average to two decimal places
    QString averageString = formatAverage(average);

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
    float totalAverage = gradeAverage(subjectAverages);

    // format total average to two decimal places
    QString totalAverageString = formatAverage(totalAverage);

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
