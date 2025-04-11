#ifndef JWQTMODELINTERFACE_H
#define JWQTMODELINTERFACE_H

#include <QAbstractItemModel>
#include <QAbstractItemModel>
#include <QQmlApplicationEngine>
#include "jwqt_macros.h"

/* Diese Klasse existiert, weil in einer template-Klasse Q_OBJECT nicht erlaubt ist.
 * Hier können als alle Sachen implementiert werden die nichts mit dem DatenObjekt zu tun haben.
 * */

class JWQTModelInterface : public QAbstractItemModel
{
    Q_OBJECT
    JWQT_PROPERTY(int, count, Count, 0);
    static bool first;
    void init();
    enum OLMRoles {
        ObjectRole = Qt::UserRole + 1,
        DefaultObjectRole
    };
    virtual QHash<int, QByteArray> customRoleNames() const;
    virtual QVariant customData(int row, int role) const;
protected:
    bool notObjectData(const int row, const int role, QVariant &result) const;
public:
    enum DirectionType
    {
        forward,
        reverse
    };
private:
    const QString modelName;
    const QString objectName;
    const DirectionType direction;
protected:
    virtual void internalDeleteById(const QString &id) = 0;
public:

    explicit JWQTModelInterface(QQmlApplicationEngine &engine,
                                const QString &modelName,
                                const QString &objectName,
                                DirectionType const direction);
    explicit JWQTModelInterface(const QString &objectName,
                                DirectionType const direction);
    virtual ~JWQTModelInterface() {}

    const DirectionType &getDirection() const;
    QHash<int, QByteArray> roleNames() const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    virtual size_t size() const = 0;
    Q_INVOKABLE void deleteById(const QString &id);
};

#endif // JWQTMODELINTERFACE_H
