#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Sistema Almox");
    const QIcon icon(":/new/Icons/icons/ifsc.png");
    this->setWindowIcon(icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}
