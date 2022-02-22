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

void Loan::on_pushButtonLoanAdd_clicked()
{
    int line = ui->tableWidgetLoanInv->currentRow();

    if(line == -1)
    {
        Message::AboutMessage("Selecione um item para adicionar");
        return;
    }

    ui->tableWidgetLoanInv->reset();

    quantity = ui->lineEditLoanQuatity->text().toInt();
    SaveLoan();

    CleanLoanInvTable();
    RefreshLoanInvTable();
    ui->lineEditLoanQuatity->clear();
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
        idItem = query.value(0).toInt();
        nameItem = query.value(1).toString();
        valueItem = query.value(2).toString();
        quantityItem = query.value(3).toInt();
        minQuantityItem = query.value(4).toInt();
        typeItem = query.value(5).toString();
        localItem = query.value(6).toString();

        ui->labelLoanItemName->setText(nameItem);
        ui->labelLoanItemValue->setText(valueItem);
        ui->labelLoanInvQuantity->setText(QString::number(quantityItem));
        ui->labelLoanItemType->setText(typeItem);
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

//---------------------------------------------------------------------------------------------

void Loan::SaveLoan()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Loan (nameStudent,registryStudent,nameItem,localItem,quantityLoan)"
                  "VALUES (:nameStudent, :registryStudent, :nameItem, :localItem, :quantityLoan)");

    query.bindValue(":nameStudent", studentName);
    query.bindValue(":registryStudent", studentRegistry);
    query.bindValue(":nameItem", QString::number(idItem) + " - " + nameItem + " - " + valueItem + " - " + typeItem);
    query.bindValue(":localItem", localItem);
    query.bindValue(":quantityLoan", quantity);

    if(!query.exec())
    {
        Message::WarningMessage("Erro na conexão com o banco de dados");
    }
}
