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

    void InitLoanInvTable();
    void AddLabel();

private slots:
    void on_pushButtonLoanRefresh_clicked();

    void on_tableWidgetLoanInv_itemSelectionChanged();

private:
    Ui::Loan *ui;

    void RefreshLoanInvTable();
    void CleanLoanInvTable();

    QString studentName;
    QString studentRegistry;
};

#endif // LOAN_H
