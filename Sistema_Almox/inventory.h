#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>
#include "message.h"
#include "database.h"

class Inventory
{
public:
    Inventory();

    void SetValue(float v);
    void SetQuantity(int q);
    void SetMinQuantity(int m);
    void SetFilter(QString f);
    void SetName(QString n);
    void SetType(QString t);
    void SetLocal(QString l);
    void SetDescription(QString d);
    void SetValueMagnitute(QString v);
    void SetvalueType(QString v);

    float GetValue();
    int GetQuantity();
    int GetMinQuantity();
    QString GetFilter();
    QString GetName();
    QString GetType();
    QString GetLocal();
    QString GetDescription();
    QString GetValueMagnitute();
    QString GetValueType();

    void SaveComponent(Inventory& inv);

private:

    float value;
    int quantity;
    int minQuantity;
    QString filter;
    QString name;
    QString type;
    QString local;
    QString description;
    QString valueMagnitude;
    QString valueType;
};

#endif // INVENTORY_H
