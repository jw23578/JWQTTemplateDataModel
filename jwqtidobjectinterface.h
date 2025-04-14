#ifndef JWQTIDOBJECTINTERFACE_H
#define JWQTIDOBJECTINTERFACE_H

#include "jwqtobjectinterface.h"
#include <QUuid>

class JWQTIdObjectInterface : public JWQTObjectInterface
{
    Q_OBJECT
    JWQT_PROPERTY(QUuid, id, Id, QUuid::createUuid())
public:
    explicit JWQTIdObjectInterface(QObject *parent = nullptr);

    void assign(const JWQTIdObjectInterface &other);
};

#endif // JWQTIDOBJECTINTERFACE_H
