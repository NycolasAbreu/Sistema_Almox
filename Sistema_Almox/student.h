#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include "message.h"
#include "database.h"

class Student
{
public:
    Student();

    void SetName(QString n);
    void SetRegistry(QString r);
    void SetCourse(QString c);

    QString GetName();
    QString GetRegistry();
    QString GetCourse();

    void SaveStudent();

    private:

    QString name;
    QString registry;
    QString course;
};

#endif // STUDENT_H
