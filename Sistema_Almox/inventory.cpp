#include "inventory.h"

Inventory::Inventory()
{
}

//---------------------------------------------------------------------------------------------

void Inventory::SaveComponent(Inventory& inv)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Inventory (nameItem,valueItem,quantityItem,minQuantityItem,typeItem,localItem,descriptionItem)"
                  "VALUES (:nameItem, :valueItem, :quantityItem, :minQuantityItem, :typeItem, :localItem, :descriptionItem)");

    query.bindValue(":nameItem", inv.GetName());
    query.bindValue(":valueItem", QString::number(inv.GetValue()) + inv.GetValueMagnitute() + inv.GetValueType());
    query.bindValue(":quantityItem", QString::number(inv.GetQuantity()));
    query.bindValue(":minQuantityItem", QString::number(inv.GetMinQuantity()));
    query.bindValue(":typeItem", inv.GetType());
    query.bindValue(":localItem", inv.GetLocal());
    query.bindValue(":descriptionItem", inv.GetDescription());

    if(!query.exec())
    {
        Message::WarningMessage("Erro na conexão com o banco de dados");
    }
}

//--------------------------------------------Sets---------------------------------------------

void Inventory::SetValue(int v)
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

int Inventory::GetValue()
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
