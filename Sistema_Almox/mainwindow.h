#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "database.h"
#include "message.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//------------------------------------------Inventory------------------------------------------
    void on_pushButtonInvAdd_clicked();
    void on_pushButtonInvFilter_clicked();
    void on_pushButtonInvRemove_clicked();
    void CleanLines();
    void GetValues();

private:
    Ui::MainWindow *ui;

//------------------------------------------Inventory------------------------------------------
    int invValue;
    int invQuantity;
    int invMinQuantity;
    QString invFilter;
    QString invName;
    QString invType;
    QString invLocal;
    QString invDescription;
    QString invValueMagnitude;
    QString invValueType;

};

#endif // MAINWINDOW_H
