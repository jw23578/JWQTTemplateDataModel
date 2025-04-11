#ifndef DATAOBJECTINTERFACE_H
#define DATAOBJECTINTERFACE_H

#include <QObject>
#include "jwqt_macros.h"

class DataObjectInterface : public QObject
{
    Q_OBJECT
protected:
public:
    explicit DataObjectInterface(QObject *parent = nullptr);

signals:

};

#endif // DATAOBJECTINTERFACE_H
