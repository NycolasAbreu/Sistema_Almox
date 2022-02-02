#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");
    QApplication a(argc, argv);

    login l;
    MainWindow m;

    QApplication::setWindowIcon(QIcon(":/new/Icons/Icons/ifsc.png"));

    l.exec();

    if(l.logged){
        m.show();
    }
    return a.exec();
}
