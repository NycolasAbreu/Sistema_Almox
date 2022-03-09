#ifndef LOAN_H
#define LOAN_H

#include <QDialog>
#include "database.h"

namespace Ui {
class Loan;
}

class Loan : public QDialog
{
    Q_OBJECT

public:
    explicit Loan(QWidget *parent = nullptr, QString name = "", QString registry = "");
    ~Loan();

    void InitLoanInvTab();
    void InitLoanInvTable();
    void AddLabel();

private slots:
    void on_pushButtonLoanRefresh_clicked();
    void on_tableWidgetLoanInv_itemSelectionChanged();
    void on_pushButtonLoanAdd_clicked();

    void on_pushButtonLoanFilter_clicked();

private:
    Ui::Loan *ui;

    void RefreshLoanInvTable();
    void CleanLoanInvTable();
    void SaveLoan();
    void RemoveItemFromInv();

    int quantity;
    int idItem;
    int quantityItem;
    int minQuantityItem;
    QString nameItem;
    QString valueItem;
    QString typeItem;
    QString localItem;

    QString studentName;
    QString studentRegistry;
};

#endif // LOAN_H
