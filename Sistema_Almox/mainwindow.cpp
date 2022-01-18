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
    Inventory inv;

    this->SetInvValues(inv);

    inv.SaveComponent(inv);

    this->CleanInvLines();
}

void MainWindow::on_pushButtonInvRemove_clicked()
{

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

//--------------------------------------------------------------------------------------------
