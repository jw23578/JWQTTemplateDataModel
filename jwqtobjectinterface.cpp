#include "jwqtobjectinterface.h"
#include <QQmlEngine>

JWQTObjectInterface::JWQTObjectInterface(QObject *parent)
    : QObject{parent}
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}
