#ifndef STRINGANDINTOBJECT_H
#define STRINGANDINTOBJECT_H

#include <dataobjectinterface.h>

class StringAndIntObject : public DataObjectInterface
{
    Q_OBJECT
    JWQT_PROPERTY(QString, id, Id, "")
    JWQT_PROPERTY(QString, name, Name, "")
    JWQT_PROPERTY(int, age, Age, 0)
public:
    explicit StringAndIntObject(QObject *parent = nullptr);
    StringAndIntObject(const QString &name, const int &age);

    void assign(const StringAndIntObject &other);
};

#endif // STRINGANDINTOBJECT_H
