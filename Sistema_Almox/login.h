#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include <QApplication>

#include "database.h"
#include "mainwindow.h"
#include "message.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    bool logged = false;

private slots:
    void on_pushButton_Login_clicked();
    void on_pushButton_Exit_clicked();

    void CheckLogin();
    void CheckDataBase(QString username,QString password);
    void CleanLines();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
