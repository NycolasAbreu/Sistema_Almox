#include "database.h"
#include <QtDebug>
#include <unistd.h>
#include <string>
#include <fstream>


DataBase::DataBase(QString name) : name(name)
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
}

QString DataBase::DataBaseLocal()
{
    QString local = qApp->applicationDirPath();
    QString completeDir = local + "/" + name;

    return completeDir;
}

bool DataBase::Open()
{
    QString dataBaseDir = DataBase::DataBaseLocal();

    QFileInfo check_file(dataBaseDir);

    if (!check_file.exists()) {
        return false;
    }

    dataBase.setDatabaseName(dataBaseDir);
    dataBase.open();

    return dataBase.isOpen();
}

void DataBase::Close()
{
    dataBase.close();
}

