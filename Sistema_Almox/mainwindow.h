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
    void InitInvTable();

private slots:
//------------------------------------------Inventory------------------------------------------
    void on_pushButtonInvAdd_clicked();
    void on_pushButtonInvFilter_clicked();
    void on_pushButtonInvRemove_clicked();
    void CleanInvLines();
    void SetInvValues(Inventory& inv);
    void CleanInvTable();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonInvRefresh_clicked();

    void on_pushButtonInvEdit_clicked();

    void on_tableWidgetInv_itemSelectionChanged();

    void on_actionSair_triggered();

    void on_actionAlunos_triggered();

    void on_actionEstoque_triggered();

    void on_actionEmprestimos_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
