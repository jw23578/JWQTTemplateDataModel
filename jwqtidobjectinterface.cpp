#include "jwqtidobjectinterface.h"

JWQTIdObjectInterface::JWQTIdObjectInterface(QObject *parent)
    : JWQTObjectInterface{parent}
{}

void JWQTIdObjectInterface::assign(const JWQTIdObjectInterface &other)
{
    setId(other.id());
}
