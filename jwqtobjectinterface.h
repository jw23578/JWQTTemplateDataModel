#ifndef JWQTOBJECTINTERFACE_H
#define JWQTOBJECTINTERFACE_H

#include <QObject>
#include "jwqt_macros.h"

class JWQTObjectInterface : public QObject
{
    Q_OBJECT
protected:
public:
    explicit JWQTObjectInterface(QObject *parent = nullptr);

signals:

};

#endif // JWQTOBJECTINTERFACE_H
