#include "stringandintobject.h"
#include <QUuid>

StringAndIntObject::StringAndIntObject(QObject *parent)
    : DataObjectInterface{parent}
{}

StringAndIntObject::StringAndIntObject(const QString &name, const int &age): DataObjectInterface(0),
    m_id(QUuid::createUuid().toString()),
    m_name(name),
    m_age(age)
{
}

void StringAndIntObject::assign(const StringAndIntObject &other)
{
    setId(other.id());
    setName(other.name());
    setAge(other.age());
}
