#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setFixedSize(311,198);
    this->setWindowTitle("Login");
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_Login_clicked()
{
    DataBase db("DataBase.db");

    if(!db.Open()){
        Message::WarningMessage("Erro ao abrir banco de dados. Conferir se o arquivo DataBase.db está na pasta");
        return;
    }

    this->CheckLogin();
}

void login::on_pushButton_Exit_clicked()
{
    this->close();
}

void login::CheckLogin()
{
    QString username;
    QString password;

    username = ui->lineEdit_Username->text();
    password = ui->lineEdit_Password->text();

    this->CheckDataBase(username, password);
}

void login::CheckDataBase(QString username,QString password)
{
    QSqlQuery query;

    if(query.exec("select * from Login where usernameColab='"+username+"' and passwordColab='"+password+"'")){
        if(query.next()){
            logged = true;
            this->close();
        }
        else{
            Message::WarningMessage("Login ou senha errado");
        }
    }
    this->CleanLines();
}

void login::CleanLines(){
    ui->lineEdit_Password->clear();
    ui->lineEdit_Username->clear();
    ui->lineEdit_Username->setFocus();
}
