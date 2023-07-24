#include "student.h"

// PRIVATE - construct student object from values
Student::Student(const int id, const QString &firstname, const QString &lastname, const QDate &birthdate, QObject *parent)
    : QObject{parent},
      m_id(id),
      m_firstname(firstname),
      m_lastname(lastname),
      m_birthdate(birthdate)
{}

// get student object from table row
Student::Student(const int tableRow)
{
    QSqlRecord record = m_model->record(tableRow);

    m_id = record.value("id").toInt();
    m_firstname = record.value("firstname").toString();
    m_lastname = record.value("lastname").toString();
    m_birthdate = QDate::fromString(record.value("birthdate").toString(), "dd.MM.yyyy");
}

// get student table model
QSqlTableModel* Student::model()
{
    // create and setup model if not already defined
    if (m_model == nullptr)
    {
        m_model = new QSqlTableModel;

        // get student data from database
        m_model->setTable("students");
        m_model->setSort(1, Qt::AscendingOrder);
        m_model->select();

        // set header labels to increase readability
        m_model->setHeaderData(1, Qt::Horizontal, "Nachname");
        m_model->setHeaderData(2, Qt::Horizontal, "Vorname");
        m_model->setHeaderData(3, Qt::Horizontal, "Geburtsdatum");
        m_model->setHeaderData(4, Qt::Horizontal, "Zertifikat");
    }

    return m_model;
}

// create SQL record from student data
QSqlRecord Student::studentRecord(const QString &firstname, const QString &lastname, const QDate &birthdate)
{
    QSqlRecord record = m_model->record();
    record.setValue("firstname", firstname);
    record.setValue("lastname", lastname);
    record.setValue("birthdate", birthdate.toString("dd.MM.yyyy"));
    record.setGenerated("id", false);

    return record;
}

// add student to database and return student object
Student* Student::addStudent(const QString &firstname, const QString &lastname, const QDate &birthdate)
{
    // create SQL record from student data
    QSqlRecord record = studentRecord(firstname, lastname, birthdate);

    // insert record into database
    m_model->insertRecord(0, record);

    // create student object
    int id = m_model->record(0).value("id").toInt();
    Student *student = new Student(id, firstname, lastname, birthdate);

    // sort students by name
    m_model->sort(1, Qt::AscendingOrder);

    return student;
}

// get student's first name
QString Student::firstname()
{
    return m_firstname;
}

// get student's last name
QString Student::lastname()
{
    return m_lastname;
}

// get student's birthdate
QDate Student::birthdate()
{
    return m_birthdate;
}

// get table row that student is displayed in
int Student::tableRow()
{
    QModelIndex index;
    for (int i = 0; i < m_model->rowCount(); i++)
    {
        index = m_model->index(i, 0);
        if (index.data().toInt() == m_id)
        {
            return i;
        }
    }
    return -1;
}

// edit values of student in database
void Student::edit(const QString &newFirstname, const QString &newLastname, const QDate &newBirthdate)
{
    // create SQL record from student data
    QSqlRecord record = studentRecord(newFirstname, newLastname, newBirthdate);

    // update record in database
    m_model->setRecord(tableRow(), record);

    // sort students by name
    m_model->sort(1, Qt::AscendingOrder);
}

// remove student from database
void Student::remove()
{
    // remove student from database
    m_model->removeRow(tableRow());
    m_model->select();

    // delete student object
    delete this;
}

