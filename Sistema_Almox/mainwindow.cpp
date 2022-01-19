#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Sistema Almox");
    const QIcon icon(":/new/Icons/Icons/ifsc.png");
    this->setWindowIcon(icon);
    ui->lineEditInvFilter->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {
        InitInvTable();
    }
}

//------------------------------------------Inventory------------------------------------------

void MainWindow::on_pushButtonInvAdd_clicked()
{
    Inventory inv;

    this->SetInvValues(inv);

    inv.SaveComponent(inv);

    this->CleanInvLines();
}

void MainWindow::on_pushButtonInvRemove_clicked()
{
    int linha = ui->tableWidgetInv->currentRow();
    QString id = ui->tableWidgetInv->item(linha,0)->text();

    QSqlQuery query;
    query.prepare("delete from Inventory where idItem ="+id);

    if(query.exec())
    {
        ui->tableWidgetInv->removeRow(linha);
    }
}

void MainWindow::on_pushButtonInvFilter_clicked()
{

}

void MainWindow::CleanInvLines()
{
    ui->lineEditInvValue->clear();
    ui->lineEditInvQuantity->clear();
    ui->lineEditInvMinQuantity->clear();
    ui->lineEditInvType->clear();
    ui->lineEditInvLocal->clear();
    ui->lineEditInvDescription->clear();
    ui->comboBoxInvName->setCurrentIndex(0);
    ui->comboBoxInvValueMagnitude->setCurrentIndex(0);
    ui->comboBoxInvValueType->setCurrentIndex(0);
    ui->lineEditInvFilter->setFocus();
}

void MainWindow::SetInvValues(Inventory& inv)
{
    inv.SetName(ui->comboBoxInvName->currentText());
    inv.SetValue(ui->lineEditInvValue->text().toInt());
    inv.SetValueMagnitute(ui->comboBoxInvValueMagnitude->currentText());
    inv.SetvalueType(ui->comboBoxInvValueType->currentText());
    inv.SetQuantity(ui->lineEditInvQuantity->text().toInt());
    inv.SetMinQuantity(ui->lineEditInvMinQuantity->text().toInt());
    inv.SetLocal(ui->lineEditInvLocal->text());
    inv.SetDescription(ui->lineEditInvDescription->text());
    inv.SetType(ui->lineEditInvType->text());
}

void MainWindow::InitInvTable()
{
    QSqlQuery query;
    query.prepare("select * from Inventory");

    if(query.exec())
    {
        int cont = 0;
        ui->tableWidgetInv->setColumnCount(7);
        while(query.next())
        {
            ui->tableWidgetInv->insertRow(cont);
            ui->tableWidgetInv->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetInv->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetInv->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetInv->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetInv->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetInv->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidgetInv->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetInv->setItem(cont,7,new QTableWidgetItem(query.value(7).toString()));
            ui->tableWidgetInv->setRowHeight(cont,20);
            cont++;
        }
    }
    ui->tableWidgetInv->setColumnWidth(0,40);
    ui->tableWidgetInv->setColumnWidth(1,150);
    ui->tableWidgetInv->setColumnWidth(2,120);
    ui->tableWidgetInv->setColumnWidth(3,120);
    ui->tableWidgetInv->setColumnWidth(4,130);
    ui->tableWidgetInv->setColumnWidth(5,120);
    ui->tableWidgetInv->setColumnWidth(6,120);

    QStringList cabecalho = {"Id","Componente","Valor","Quantidade","Quantidade mínima","Tipo","Local","Descrição"};
    ui->tableWidgetInv->setHorizontalHeaderLabels(cabecalho);

    ui->tableWidgetInv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetInv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetInv->verticalHeader()->setVisible(false);
    ui->tableWidgetInv->setStyleSheet("QTableView {selection-background-color:blue}");
}

void MainWindow::on_pushButtonInvRefresh_clicked()
{
    InitInvTable();
}

//--------------------------------------------------------------------------------------------




