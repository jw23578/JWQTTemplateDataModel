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
    virtual void internalRemoveByIndex(const size_t index) = 0;
    virtual void internalClear() = 0;
    virtual void internalFilter(const QString &needle) = 0;
    virtual void swap(size_t i1, size_t i2, bool update) = 0;
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

    void clear();
    void removeByIndex(const size_t index);

    Q_INVOKABLE void filter(const QString &needle);
};

#endif // JWQTMODELINTERFACE_H
