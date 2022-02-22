#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//---------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Sistema Almox");
    InitInvTable();
    InitStudentTable();
    InitLoanTable();
}

//---------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {
        ui->tableWidgetInv->reset();
        CleanInvTable();
        RefreshInvTable();
    }

    else if(index == 1)
    {
        ui->tableWidgetLoan->reset();
        CleanLoanTable();
        RefreshLoanTable();
    }

    else if(index == 2)
    {
        ui->tableWidgetStudent->reset();
        CleanStudentTable();
        RefreshStudentTable();
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_actionSair_triggered()
{
    close();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_actionEstoque_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_actionEmprestimos_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_actionAlunos_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
}

//---------------------------------------------------------------------------------------------

//------------------------------------------Inventory------------------------------------------

void MainWindow::on_pushButtonInvAdd_clicked()
{
    ui->tableWidgetInv->reset();

    Inventory inv;
    SetInvValues(inv);
    inv.SaveComponent(inv);

    CleanInvLines();
    CleanInvTable();
    RefreshInvTable();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonInvRemove_clicked()
{
    int line = ui->tableWidgetInv->currentRow();

    if(line == -1)
    {
        Message::AboutMessage("Selecione um componente para remover");
        return;
    }

    QString id = ui->tableWidgetInv->item(line,0)->text();
    ui->tableWidgetInv->reset();

    QSqlQuery query;
    query.prepare("delete from Inventory where idItem ="+id);

    if(query.exec())
    {
        ui->tableWidgetInv->removeRow(line);
        ui->tableWidgetInv->setCurrentItem(0);
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonInvEdit_clicked()
{
    int line = ui->tableWidgetInv->currentRow();

    if(line == -1)
    {
        Message::AboutMessage("Selecione um componente para editar");
        return;
    }
    else
    {
        int id = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),0)->text().toInt();
        QString name = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),1)->text();
        QString value = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),2)->text();
        QString type = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),5)->text();
        QString description = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),7)->text();
        QString quantity = ui->lineEditEditInvQuantity->text();
        QString minQuantity = ui->lineEditEditInvMinQuantity->text();
        QString local = ui->lineEditEditInvLocal->text();

        ui->tableWidgetInv->reset();

        QSqlQuery query;
        query.prepare("UPDATE Inventory SET idItem=:id, nameItem=:name, valueItem=:value, quantityItem=:quant,"
                      " minQuantityItem=:minquant, typeItem=:type, localItem=:local, descriptionItem=:desc WHERE"
                      " idItem=:id ");

        query.bindValue(":name", name);
        query.bindValue(":value", value);
        query.bindValue(":quant", quantity);
        query.bindValue(":minquant", minQuantity);
        query.bindValue(":type", type);
        query.bindValue(":local", local);
        query.bindValue(":desc", description);
        query.bindValue(":id", id);

        if(query.exec())
        {
            Message::AboutMessage("Atualizado");
            CleanInvTable();
            RefreshInvTable();
        }
        else
        {
            Message::WarningMessage("Não foi possível atualizar");
        }
    }

}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonInvFilter_clicked()
{
    ui->tableWidgetInv->reset();
    CleanInvTable();

    QString search;

    if(ui->comboBoxInvFilter->currentText() == "Nome")
    {
        search = "select idItem,nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem \
                    from Inventory where nameItem like '%"+ui->lineEditInvFilter->text()+"%' order by nameItem";
    }
    else if(ui->comboBoxInvFilter->currentText() == "Tipo")
    {
        search = "select idItem,nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem \
                    from Inventory where typeItem like '%"+ui->lineEditInvFilter->text()+"%' order by typeItem";
    }
    else if(ui->comboBoxInvFilter->currentText() == "Valor")
    {
        search = "select idItem,nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem \
                    from Inventory where valueItem like '%"+ui->lineEditInvFilter->text()+"%' order by valueItem";
    }

    int cont = 0;
    QSqlQuery query;

    query.prepare(search);

    if(query.exec())
    {
        while(query.next()){
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
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonInvRefresh_clicked()
{
    ui->tableWidgetInv->reset();
    CleanInvTable();
    RefreshInvTable();
}

//---------------------------------------------------------------------------------------------


void MainWindow::on_tableWidgetInv_itemSelectionChanged()
{
    int id = ui->tableWidgetInv->item(ui->tableWidgetInv->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from Inventory where idItem="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->lineEditEditInvQuantity->setText(query.value(3).toString());
        ui->lineEditEditInvMinQuantity->setText(query.value(4).toString());
        ui->lineEditEditInvLocal->setText(query.value(6).toString());
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::InitInvTable()
{
    ui->tableWidgetInv->setColumnCount(8);

    ui->tableWidgetInv->setColumnWidth(0,10);
    ui->tableWidgetInv->setColumnWidth(1,150);
    ui->tableWidgetInv->setColumnWidth(2,120);
    ui->tableWidgetInv->setColumnWidth(3,120);
    ui->tableWidgetInv->setColumnWidth(4,130);
    ui->tableWidgetInv->setColumnWidth(5,120);
    ui->tableWidgetInv->setColumnWidth(6,120);
    ui->tableWidgetInv->setColumnWidth(7,420);

    RefreshInvTable();

    ui->tableWidgetInv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetInv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetInv->verticalHeader()->setVisible(false);
    ui->tableWidgetInv->setStyleSheet("QTableView {selection-background-color:blue}");
}

//---------------------------------------------------------------------------------------------

void MainWindow::RefreshInvTable()
{
    QSqlQuery query;
    query.prepare("select * from Inventory");

    if(query.exec())
    {
        int cont = 0;
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

    QStringList cabecalho = {"Id","Componente","Valor","Quantidade","Quantidade mínima","Tipo","Local","Descrição"};
    ui->tableWidgetInv->setHorizontalHeaderLabels(cabecalho);
}

//---------------------------------------------------------------------------------------------

void MainWindow::CleanInvTable()
{
    while (ui->tableWidgetInv->rowCount()>0)
    {
        ui->tableWidgetInv->removeRow(0);
    }
}

//---------------------------------------------------------------------------------------------

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
}

//---------------------------------------------------------------------------------------------

void MainWindow::SetInvValues(Inventory& inv)
{
    inv.SetName(ui->comboBoxInvName->currentText());
    inv.SetValue(ui->lineEditInvValue->text().toFloat());
    inv.SetValueMagnitute(ui->comboBoxInvValueMagnitude->currentText());
    inv.SetvalueType(ui->comboBoxInvValueType->currentText());
    inv.SetQuantity(ui->lineEditInvQuantity->text().toInt());
    inv.SetMinQuantity(ui->lineEditInvMinQuantity->text().toInt());
    inv.SetLocal(ui->lineEditInvLocal->text());
    inv.SetDescription(ui->lineEditInvDescription->text());
    inv.SetType(ui->lineEditInvType->text());
}

//--------------------------------------------------------------------------------------------

//------------------------------------------Students------------------------------------------

void MainWindow::on_pushButtonStudentAdd_clicked()
{
    ui->tableWidgetStudent->reset();

    Student student;
    SetStudentValues(student);
    student.SaveStudent(student);

    CleanStudentLines();
    CleanStudentTable();
    RefreshStudentTable();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonStudentRemove_clicked()
{
    int line = ui->tableWidgetStudent->currentRow();

    if(line == -1)
    {
        Message::AboutMessage("Selecione um componente para remover");
        return;
    }

    QString id = ui->tableWidgetStudent->item(line,0)->text();
    ui->tableWidgetStudent->reset();

    QSqlQuery query;
    query.prepare("delete from Students where idStudent ="+id);

    if(query.exec())
    {
        ui->tableWidgetStudent->removeRow(line);
        ui->tableWidgetStudent->setCurrentItem(0);
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonStudentFilter_clicked()
{
    ui->tableWidgetStudent->reset();
    CleanStudentTable();

    QString search;

    if(ui->comboBoxStudentFilter->currentText() == "Nome")
    {
        search = "select idStudent,nameStudent,registryStudent,courseStudent \
                    from Students where nameStudent like '%"+ui->lineEditStudentFilter->text()+"%' order by nameStudent";
    }
    else if(ui->comboBoxStudentFilter->currentText() == "Matrícula")
    {
        search = "select idStudent,nameStudent,registryStudent,courseStudent \
                    from Students where registryStudent like '%"+ui->lineEditStudentFilter->text()+"%' order by registryStudent";
    }

    QSqlQuery query;

    query.prepare(search);

    if(query.exec())
    {
        int cont = 0;
        while(query.next())
        {
            ui->tableWidgetStudent->insertRow(cont);
            ui->tableWidgetStudent->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetStudent->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetStudent->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetStudent->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetStudent->setRowHeight(cont,20);
            cont++;
        }
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonStudentRefresh_clicked()
{
    ui->tableWidgetStudent->reset();
    CleanStudentTable();
    RefreshStudentTable();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonStudentAddLoan_clicked()
{
    int line = ui->tableWidgetStudent->currentRow();

    if(line == -1)
    {
        Message::AboutMessage("Selecione um aluno para adicionar empréstimo");
        return;
    }

    QString name;
    QString registry;

    int id = ui->tableWidgetStudent->item(line,0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from Students where idStudent="+QString::number(id));
    if(query.exec())
    {
        query.first();
        name = query.value(1).toString();
        registry = query.value(2).toString();
    }

    Loan l(nullptr, name, registry);
    l.setModal(true);
    l.exec();

    ui->labelName->setText("");
    ui->labelRegistry->setText("");
    ui->tableWidgetStudent->reset();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_tableWidgetStudent_itemSelectionChanged()
{
    int id = ui->tableWidgetStudent->item(ui->tableWidgetStudent->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from Students where idStudent="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->labelName->setText(query.value(1).toString());
        ui->labelRegistry->setText(query.value(2).toString());
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::SetStudentValues(Student& student)
{
    student.SetName(ui->lineEditStudentName->text());
    student.SetRegistry(ui->lineEditStudentRegistry->text());
    student.SetCourse(ui->lineEditStudentCourse->text());
}

//---------------------------------------------------------------------------------------------

void MainWindow::InitStudentTable()
{
    ui->tableWidgetStudent->setColumnCount(4);

    ui->tableWidgetStudent->setColumnWidth(0,10);
    ui->tableWidgetStudent->setColumnWidth(1,300);
    ui->tableWidgetStudent->setColumnWidth(2,300);
    ui->tableWidgetStudent->setColumnWidth(3,300);

    RefreshStudentTable();

    ui->tableWidgetStudent->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetStudent->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetStudent->verticalHeader()->setVisible(false);
    ui->tableWidgetStudent->setStyleSheet("QTableView {selection-background-color:blue}");
}

//---------------------------------------------------------------------------------------------

void MainWindow::RefreshStudentTable()
{
    QSqlQuery query;
    query.prepare("select * from Students");

    if(query.exec())
    {
        int cont = 0;
        while(query.next())
        {
            ui->tableWidgetStudent->insertRow(cont);
            ui->tableWidgetStudent->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetStudent->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetStudent->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetStudent->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetStudent->setRowHeight(cont,20);
            cont++;
        }
    }

    QStringList cabecalho = {"Id","Nome","Matrícula","Curso"};
    ui->tableWidgetStudent->setHorizontalHeaderLabels(cabecalho);
}

//---------------------------------------------------------------------------------------------

void MainWindow::CleanStudentTable()
{
    while (ui->tableWidgetStudent->rowCount()>0)
    {
        ui->tableWidgetStudent->removeRow(0);
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::CleanStudentLines()
{
    ui->lineEditStudentName->clear();
    ui->lineEditStudentRegistry->clear();
    ui->lineEditStudentCourse->clear();
    ui->lineEditStudentName->setFocus();
}

//---------------------------------------------------------------------------------------------

//--------------------------------------------Loan---------------------------------------------


void MainWindow::on_pushButtonLoanRefresh_clicked()
{
    ui->tableWidgetLoan->reset();
    CleanLoanTable();
    RefreshLoanTable();
}

//---------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonLoanFilter_clicked()
{
    ui->tableWidgetLoan->reset();
    CleanLoanTable();

    QString search;

    if(ui->comboBoxLoanFilter->currentText() == "Nome")
    {
        search = "select idLoan,nameStudent,registryStudent,nameItem,localItem,quantityLoan,returned \
                    from Loan where nameStudent like '%"+ui->lineEditLoanFilter->text()+"%' order by nameStudent";
    }
    else if(ui->comboBoxLoanFilter->currentText() == "Matrícula")
    {
        search = "select idLoan,nameStudent,registryStudent,nameItem,localItem,quantityLoan,returned \
                    from Loan where registryStudent like '%"+ui->lineEditLoanFilter->text()+"%' order by registryStudent";
    }

    QSqlQuery query;

    query.prepare(search);

    if(query.exec())
    {
        int cont = 0;
        while(query.next())
        {
            ui->tableWidgetLoan->insertRow(cont);
            ui->tableWidgetLoan->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetLoan->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetLoan->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetLoan->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetLoan->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetLoan->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidgetLoan->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetLoan->setRowHeight(cont,20);
            cont++;
        }
    }

}

//---------------------------------------------------------------------------------------------

void MainWindow::on_tableWidgetLoan_itemSelectionChanged()
{
    int id = ui->tableWidgetLoan->item(ui->tableWidgetLoan->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from Loan where idLoan="+QString::number(id));
    if(query.exec())
    {
        query.first();
        ui->labelLoanName->setText(query.value(1).toString());
        ui->labelLoanItem->setText(query.value(3).toString());
        ui->labelLoanQuantity->setText(query.value(5).toString());
    }
}

//---------------------------------------------------------------------------------------------

void MainWindow::InitLoanTable()
{
    ui->tableWidgetLoan->setColumnCount(7);

    ui->tableWidgetLoan->setColumnWidth(0,10);
    ui->tableWidgetLoan->setColumnWidth(1,230);
    ui->tableWidgetLoan->setColumnWidth(2,80);
    ui->tableWidgetLoan->setColumnWidth(3,350);
    ui->tableWidgetLoan->setColumnWidth(4,70);
    ui->tableWidgetLoan->setColumnWidth(5,90);
    ui->tableWidgetLoan->setColumnWidth(6,80);

    RefreshLoanTable();

    ui->tableWidgetLoan->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetLoan->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLoan->verticalHeader()->setVisible(false);
    ui->tableWidgetLoan->setStyleSheet("QTableView {selection-background-color:blue}");
}

//---------------------------------------------------------------------------------------------

void MainWindow::RefreshLoanTable()
{
    QSqlQuery query;
    query.prepare("select * from Loan");

    if(query.exec())
    {
        int cont = 0;
        while(query.next())
        {
            ui->tableWidgetLoan->insertRow(cont);
            ui->tableWidgetLoan->setItem(cont,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidgetLoan->setItem(cont,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidgetLoan->setItem(cont,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tableWidgetLoan->setItem(cont,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tableWidgetLoan->setItem(cont,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tableWidgetLoan->setItem(cont,5,new QTableWidgetItem(query.value(5).toString()));
            ui->tableWidgetLoan->setItem(cont,6,new QTableWidgetItem(query.value(6).toString()));
            ui->tableWidgetLoan->setRowHeight(cont,20);
            cont++;
        }
    }

    QStringList cabecalho = {"Id","Aluno","Matrícula","Item","Local","Quantidade","Retornado"};
    ui->tableWidgetLoan->setHorizontalHeaderLabels(cabecalho);
}

//---------------------------------------------------------------------------------------------

void MainWindow::CleanLoanTable()
{
    while (ui->tableWidgetLoan->rowCount()>0)
    {
        ui->tableWidgetLoan->removeRow(0);
    }
}
