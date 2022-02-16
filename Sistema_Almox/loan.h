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
    explicit Loan(QWidget *parent = nullptr);
    ~Loan();

    void InitLoanInvTable();
private slots:
    void on_pushButtonLoanRefresh_clicked();

private:
    Ui::Loan *ui;

    void RefreshLoanInvTable();
    void CleanLoanInvTable();
};

#endif // LOAN_H
