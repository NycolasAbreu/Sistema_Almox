#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
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
