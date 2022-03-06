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
    void InitLoanTable();

private slots:

 //-----------------------------------------MainWindow-----------------------------------------

    void on_tabWidget_currentChanged(int index);
    void on_actionSair_triggered();
    void on_actionAlunos_triggered();
    void on_actionEstoque_triggered();
    void on_actionEmprestimos_triggered();

//------------------------------------------Inventory------------------------------------------

    void CleanInvLines();
    void CleanInvTable();
    void RefreshInvTable();
    void SetInvValues(Inventory& inv);

    void on_pushButtonInvAdd_clicked();
    void on_pushButtonInvEdit_clicked();
    void on_pushButtonInvFilter_clicked();
    void on_pushButtonInvRemove_clicked();
    void on_pushButtonInvRefresh_clicked();
    void on_tableWidgetInv_itemSelectionChanged();


//-------------------------------------------Students------------------------------------------

    void CleanStudentLines();
    void CleanStudentTable();
    void RefreshStudentTable();
    void SetStudentValues(Student& student);

    void on_pushButtonStudentAdd_clicked();
    void on_pushButtonStudentAddLoan_clicked();
    void on_pushButtonStudentFilter_clicked();
    void on_pushButtonStudentRefresh_clicked();
    void on_pushButtonStudentRemove_clicked();
    void on_tableWidgetStudent_itemSelectionChanged();


//---------------------------------------------Loan--------------------------------------------

    void RefreshLoanTable();
    void CleanLoanTable();
    void ReturnItemToInv(int id, int quantity);
    void AddItemToLoan(int itemId, int quantity, int loanId);
    void RemoveItemToLoan(int itemId, int quantity, int loanId);

    void on_pushButtonLoanRefresh_clicked();
    void on_tableWidgetLoan_itemSelectionChanged();
    void on_pushButtonLoanFilter_clicked();
    void on_pushButtonLoanReturned_clicked();
    void on_pushButtonLoanMore_clicked();
    void on_pushButtonLoanLess_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
