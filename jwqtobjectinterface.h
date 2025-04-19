#ifndef JWQTOBJECTINTERFACE_H
#define JWQTOBJECTINTERFACE_H

#include <QObject>
#include "jwqt_macros.h"

class JWQTObjectInterface : public QObject
{
    Q_OBJECT
    JWQT_PROPERTY(bool, notInFilter, NotInFilter, false)
protected:
public:
    explicit JWQTObjectInterface(QObject *parent = nullptr);
    virtual void handleNeedle(const QString &needle) {setNotInFilter(false);}
    virtual bool hasPropertyWithValue(const QString &property, const QString &value) {return false;}

signals:

};

#endif // JWQTOBJECTINTERFACE_H
