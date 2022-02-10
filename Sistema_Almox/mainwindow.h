#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "database.h"
#include "inventory.h"
#include "loan.h"
#include "message.h"
#include "student.h"

namespace Ui {
class MainWindow;
}

class Inventory;
class Student;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitInvTable();
    void InitStudentTable();

private slots:
//------------------------------------------Inventory------------------------------------------
    void on_pushButtonInvAdd_clicked();
    void on_pushButtonInvFilter_clicked();
    void on_pushButtonInvRemove_clicked();

    void CleanInvLines();
    void CleanInvTable();
    void RefreshInvTable();
    void SetInvValues(Inventory& inv);

    void CleanStudentLines();
    void CleanStudentTable();
    void RefreshStudentTable();
    void SetStudentValues(Student& student);


    void on_tabWidget_currentChanged(int index);

    void on_pushButtonInvRefresh_clicked();

    void on_pushButtonInvEdit_clicked();

    void on_tableWidgetInv_itemSelectionChanged();

    void on_actionSair_triggered();

    void on_actionAlunos_triggered();

    void on_actionEstoque_triggered();

    void on_actionEmprestimos_triggered();

    void on_pushButtonStudentAdd_clicked();

    void on_pushButtonStudentRefresh_clicked();

    void on_pushButtonStudentRemove_clicked();

    void on_pushButtonStudentFilter_clicked();

    void on_tableWidgetStudent_itemSelectionChanged();

    void on_pushButtonStudentAddLoan_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
