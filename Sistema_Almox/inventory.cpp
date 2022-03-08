#include "inventory.h"

Inventory::Inventory()
{
}

//---------------------------------------------------------------------------------------------

void Inventory::SaveComponent()
{
    QSqlQuery query;

    query.prepare("INSERT INTO Inventory (nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem)"
                  "VALUES (:nameItem, :valueItem, :quantityItem, :minQuantityItem, :typeItem, :localItem, :descriptionItem)");

    query.bindValue(":nameItem", GetName());
    query.bindValue(":valueItem", QString::number(GetValue()) + GetValueMagnitute() + GetValueType());
    query.bindValue(":quantityItem", QString::number(GetQuantity()));
    query.bindValue(":minQuantityItem", QString::number(GetMinQuantity()));
    query.bindValue(":typeItem", GetType());
    query.bindValue(":localItem", GetLocal());
    query.bindValue(":descriptionItem", GetDescription());

    if(!query.exec())
    {
        Message::WarningMessage("Erro na conexão com o banco de dados");
    }
}

//--------------------------------------------Sets---------------------------------------------

void Inventory::SetValue(float v)
{
    value = v;
}
void Inventory::SetQuantity(int q)
{
    quantity = q;
}
void Inventory::SetMinQuantity(int m)
{
    minQuantity = m;
}
void Inventory::SetFilter(QString f)
{
    filter = f;
}
void Inventory::SetName(QString n)
{
    name = n;
}
void Inventory::SetType(QString t)
{
    type = t;
}
void Inventory::SetLocal(QString l)
{
    local = l;
}
void Inventory::SetDescription(QString d)
{
    description = d;
}
void Inventory::SetValueMagnitute(QString v)
{
    valueMagnitude = v;
}
void Inventory::SetvalueType(QString v)
{
    valueType = v;
}

//--------------------------------------------Gets---------------------------------------------

float Inventory::GetValue()
{
    return value;
}
int Inventory::GetQuantity()
{
    return quantity;
}
int Inventory::GetMinQuantity()
{
    return minQuantity;
}
QString Inventory::GetFilter()
{
    return filter;
}
QString Inventory::GetName()
{
    return name;
}
QString Inventory::GetType()
{
    return type;
}
QString Inventory::GetLocal()
{
    return local;
}
QString Inventory::GetDescription()
{
    return description;
}
QString Inventory::GetValueMagnitute()
{
    return valueMagnitude;
}
QString Inventory::GetValueType()
{
    return valueType;
}
