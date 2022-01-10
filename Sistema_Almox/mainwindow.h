#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE");

    bool log;
    QString colabName;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
