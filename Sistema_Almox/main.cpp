#include "mainwindow.h"
#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");
    QApplication a(argc, argv);
    login l;
    MainWindow m;

    l.exec();

    if(l.logged){
        m.show();
    }
    return a.exec();
}
