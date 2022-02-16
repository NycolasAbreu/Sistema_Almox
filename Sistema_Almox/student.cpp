#include "student.h"

Student::Student()
{
}

//---------------------------------------------------------------------------------------------

void Student::SaveStudent(Student& stud)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Students (nameStudent,registryStudent,courseStudent)"
                  "VALUES (:nameStudent, :registryStudent, :courseStudent)");

    query.bindValue(":nameStudent", stud.GetName());
    query.bindValue(":registryStudent", stud.GetRegistry());
    query.bindValue(":courseStudent", stud.GetCourse());

    if(!query.exec())
    {
        Message::WarningMessage("Erro na conexão com o banco de dados");
    }
}

//--------------------------------------------Sets---------------------------------------------

void Student::SetName(QString n)
{
    name = n;
}
void Student::SetCourse(QString c)
{
    course = c;
}
void Student::SetRegistry(QString r)
{
    registry = r;
}

//--------------------------------------------Gets---------------------------------------------

QString Student::GetName()
{
    return name;
}
QString Student::GetCourse()
{
    return course;
}
QString Student::GetRegistry()
{
    return registry;
}
