#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>
#include <QFile>
#include <string>
#include <fstream>

#include "mainwindow.h"

class DataBase
{
public:
    DataBase(QString name);
    QString DataBaseLocal();
    bool Open();
    void Close();

    QSqlDatabase dataBase;

private:
    QString name;
};

#endif // DATABASE_H
