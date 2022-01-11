#include "message.h"

Message::Message()
{

}

void Message::WarningMessage(QString message){
    QMessageBox msgBox(QMessageBox::Information, "Warning", message);

    ChangeFont(msgBox);
    msgBox.exec();
};

void Message::AboutMessage(QString message){
    QMessageBox msgBox(QMessageBox::Information, "About", message);

    ChangeFont(msgBox);
    msgBox.exec();
};

void Message::ChangeFont(QMessageBox& msgBox){
    //Change background color
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::cyan);
    msgBox.setPalette(palette);

    //Change font
    QFont font( "Arial" );
    font.setPointSize(10);
    font.setBold(true);
    msgBox.setFont(font);
};
