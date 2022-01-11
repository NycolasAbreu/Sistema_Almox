#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_Login_clicked()
{
    DataBase db("DataBase.db");

    if(!db.Open()){
        QMessageBox::warning(this,"error","Erro ao abrir banco de dados. Conferir se o arquivo DataBase.db está na pasta");
        return;
    }

    QString username;
    QString password;

    username = ui->lineEdit_Username->text();
    password = ui->lineEdit_Password->text();

    QSqlQuery query;

    if(query.exec("select * from Login where usernameColab='"+username+"' and passwordColab='"+password+"'")){
        if(query.next()){
            logged = true;
            close();
        }
        else{
            QMessageBox::warning(this,"error","Login ou senha errado");
        }
    }
        else{
            ui->lineEdit_Password->clear();
            ui->lineEdit_Username->clear();
            ui->lineEdit_Username->setFocus();
        }

    db.Close();
}

void login::on_pushButton_Exit_clicked()
{
    close();
}

