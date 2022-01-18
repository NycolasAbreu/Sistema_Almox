#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "database.h"
#include "message.h"
#include "inventory.h"

namespace Ui {
class MainWindow;
}

class Inventory;

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
    void CleanInvLines();
    void SetInvValues(Inventory& inv);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
