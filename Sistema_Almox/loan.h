#ifndef LOAN_H
#define LOAN_H

#include <QDialog>

namespace Ui {
class Loan;
}

class Loan : public QDialog
{
    Q_OBJECT

public:
    explicit Loan(QWidget *parent = nullptr);
    ~Loan();

private:
    Ui::Loan *ui;
};

#endif // LOAN_H
