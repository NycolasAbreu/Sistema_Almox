#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString dataBaseLocal = qApp->applicationDirPath();
    QString dataBaseName = dataBaseLocal+"/DataBase.db";

    dataBase.setDatabaseName(dataBaseName);

    if(!dataBase.open()){
        QMessageBox::warning(this,"Data base eror","Erro ao abrir a base de dados/nConferir se o arquivo DataBase.db está na pasta");
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
