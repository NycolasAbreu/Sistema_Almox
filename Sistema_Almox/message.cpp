#include "message.h"

Message::Message()
{
}

//---------------------------------------------------------------------------------------------

void Message::WarningMessage(QString message){
    QMessageBox msgBox(QMessageBox::Information, "Atenção", message);

    ModifyInterface(msgBox);
    msgBox.exec();
};

//---------------------------------------------------------------------------------------------

void Message::AboutMessage(QString message){
    QMessageBox msgBox(QMessageBox::Information, "Informação", message);

    ModifyInterface(msgBox);
    msgBox.exec();
};

//---------------------------------------------------------------------------------------------

void Message::ModifyInterface(QMessageBox& msgBox){
    //Muda cor do background
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    msgBox.setPalette(palette);

    //Muda fonte
    QFont font( "Arial" );
    font.setPointSize(10);
    font.setBold(true);
    msgBox.setFont(font);

    //Adiciona icone
    msgBox.setIconPixmap(QPixmap("qrc:/new/Icons/Icons/ifsc.png"));
};
