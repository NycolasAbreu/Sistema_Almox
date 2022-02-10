#include "loan.h"
#include "ui_loan.h"

Loan::Loan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Loan)
{
    ui->setupUi(this);
    setWindowTitle("Empréstimo");
}

Loan::~Loan()
{
    delete ui;
}
