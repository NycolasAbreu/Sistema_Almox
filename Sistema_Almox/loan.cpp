#include "loan.h"
#include "ui_loan.h"

Loan::Loan(QWidget *parent, QString name, QString registry) :
    QDialog(parent),
    ui(new Ui::Loan),
    studentName(name),
    studentRegistry(registry)
{
    ui->setupUi(this);

    setWindowTitle("Empréstimo");
    InitLoanInvTable();
    AddLabel();
}

//---------------------------------------------------------------------------------------------

Loan::~Loan()
{
    delete ui;
}

//---------------------------------------------------------------------------------------------

void Loan::on_pushButtonLoanRefresh_clicked()
{
    ui->tableWidgetLoanInv->reset();
    CleanLoanInvTable();
    RefreshLoanInvTable();
}

//---------------------------------------------------------------------------------------------

void Loan::on_tableWidgetLoanInv_itemSelectionChanged()
{
    int id = ui->tableWidgetLoanInv->item(ui->tableWidgetLoanInv->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from Inventory where idItem="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->labelLoanItemName->setText(query.value(1).toString());
        ui->labelLoanItemValue->setText(query.value(2).toString());
        ui->labelLoanInvQuantity->setText(query.value(3).toString());
        ui->labelLoanItemType->setText(query.value(5).toString());
    }
}

//---------------------------------------------------------------------------------------------

void Loan::InitLoanInvTable()
{
    ui->tableWidgetLoanInv->setColumnCount(8);

    ui->tableWidgetLoanInv->setColumnWidth(0,10);
    ui->tableWidgetLoanInv->setColumnWidth(1,150);
    ui->tableWidgetLoanInv->setColumnWidth(2,120);
    ui->tableWidgetLoanInv->setColumnWidth(3,120);
    ui->tableWidgetLoanInv->setColumnWidth(4,130);
    ui->tableWidgetLoanInv->setColumnWidth(5,120);
    ui->tableWidgetLoanInv->setColumnWidth(6,120);
    ui->tableWidgetLoanInv->setColumnWidth(7,420);

    RefreshLoanInvTable();

    ui->tableWidgetLoanInv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetLoanInv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLoanInv->verticalHeader()->setVisible(false);
    ui->tableWidgetLoanInv->setStyleSheet("QTableView {selection-background-color:blue}");
}

//---------------------------------------------------------------------------------------------

void Loan::RefreshLoanInvTable()
{
    QSqlQuery query;
    query.prepare("select * from Inventory");

    if(query.exec())
    {
        int cont = 0;
        while(query.next())
        {
            ui->tableWidgetLoanInv->insertRow(cont);
            ui->tableWidgetLoanInv->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetLoanInv->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetLoanInv->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetLoanInv->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetLoanInv->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetLoanInv->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidgetLoanInv->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetLoanInv->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidgetLoanInv->setRowHeight(cont,20);
            cont++;
        }
    }

    QStringList cabecalho = {"Id","Componente","Valor","Quantidade","Quantidade mínima","Tipo","Local","Descrição"};
    ui->tableWidgetLoanInv->setHorizontalHeaderLabels(cabecalho);
}

//---------------------------------------------------------------------------------------------

void Loan::CleanLoanInvTable()
{
    while (ui->tableWidgetLoanInv->rowCount()>0)
    {
        ui->tableWidgetLoanInv->removeRow(0);
    }
}

//---------------------------------------------------------------------------------------------

void Loan::AddLabel()
{
    ui->labelLoanStudentName->setText(studentName);
    ui->labelLoanStudentRegistry->setText(studentRegistry);
}


