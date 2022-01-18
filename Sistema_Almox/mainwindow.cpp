#include "mainwindow.h"
#include "ui_mainwindow.h"

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

//------------------------------------------Inventory------------------------------------------

void MainWindow::on_pushButtonInvAdd_clicked()
{
    this->GetValues();

    QSqlQuery query;

    query.prepare("INSERT INTO Inventory (nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem)"
                  "VALUES (:nameItem, :valueItem, :quantityItem, :minQuantityItem, :typeItem, :localItem, :descriptionItem)");

    query.bindValue(":nameItem", invName);
    query.bindValue(":valueItem", QString::number(invValue) + invValueMagnitude + invValueType);
    query.bindValue(":quantityItem", QString::number(invQuantity));
    query.bindValue(":minQuantityItem", QString::number(invMinQuantity));
    query.bindValue(":typeItem", invType);
    query.bindValue(":localItem", invLocal);
    query.bindValue(":descriptionItem", invDescription);

    if(!query.exec())
    {
        Message::WarningMessage("Erro na conexão com o banco de dados");
    }

    this->CleanLines();
}

void MainWindow::on_pushButtonInvRemove_clicked()
{

}

void MainWindow::on_pushButtonInvFilter_clicked()
{

}

void MainWindow::CleanLines()
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

void MainWindow::GetValues()
{
    invName = ui->comboBoxInvName->currentText();
    invValue = ui->lineEditInvValue->text().toInt();
    invValueMagnitude = ui->comboBoxInvValueMagnitude->currentText();
    invValueType = ui->comboBoxInvValueType->currentText();
    invQuantity = ui->lineEditInvQuantity->text().toInt();
    invMinQuantity = ui->lineEditInvMinQuantity->text().toInt();
    invLocal = ui->lineEditInvLocal->text();
    invDescription = ui->lineEditInvDescription->text();
    invType = ui->lineEditInvType->text();
}

//--------------------------------------------------------------------------------------------
