#ifndef MESSAGE_H
#define MESSAGE_H
#include <QMessageBox>
#include <QPalette>

class Message
{
public:
    Message();

    static void WarningMessage(QString message);
    static void AboutMessage(QString message);
    static void ModifyInterface(QMessageBox& msgBox);
};

#endif // MESSAGE_H
