#include "jwqtmodelinterface.h"
#include "jwqtobjectinterface.h"
#include <QQmlContext>

bool JWQTModelInterface::first(true);

void JWQTModelInterface::init()
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    if (first)
    {
        first = false;
        qmlRegisterType<JWQTObjectInterface>("DataObjectInterface", 1, 0, "DataObjectInterface");
    }
}

QHash<int, QByteArray> JWQTModelInterface::customRoleNames() const
{
    return QHash<int, QByteArray>();
}

QVariant JWQTModelInterface::customData(int row, int role) const
{
    Q_UNUSED(row);
    Q_UNUSED(role);
    return QVariant();
}

bool JWQTModelInterface::notObjectData(const int row, const int role, QVariant &result) const
{
    if (row >= static_cast<int>(size()) || row < 0)
    {
        return true;
    }
    result = customData(row, role);
    if (result != QVariant())
    {
        return true;
    }
    if (role != ObjectRole && role != DefaultObjectRole)
    {
        return true;
    }
    return false;
}

QHash<int, QByteArray> JWQTModelInterface::roleNames() const
{
    QHash<int, QByteArray> roles(customRoleNames());
    if (objectName.length())
    {
        roles[ObjectRole] = objectName.toLatin1();
    }
    roles[DefaultObjectRole] = "dataObject";
    return roles;
}


JWQTModelInterface::JWQTModelInterface(QQmlApplicationEngine &engine,
                                       const QString &modelName,
                                       const QString &objectName,
                                       const DirectionType direction):
    QAbstractItemModel(),
    modelName(modelName),
    objectName(objectName),
    direction(direction)
{
    init();
    engine.rootContext()->setContextProperty(modelName, QVariant::fromValue(this));
}

JWQTModelInterface::JWQTModelInterface(const QString &objectName,
                                       const DirectionType direction):
    QAbstractItemModel(),
    objectName(objectName),
    direction(direction)
{
    init();
}

const JWQTModelInterface::DirectionType &JWQTModelInterface::getDirection() const
{
    return direction;
}

QModelIndex JWQTModelInterface::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column);
}

QModelIndex JWQTModelInterface::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int JWQTModelInterface::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(size());
}

int JWQTModelInterface::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

void JWQTModelInterface::removeByIndex(const size_t index)
{
    internalRemoveByIndex(index);
}

void JWQTModelInterface::filter(const QString &needle)
{
    internalFilter(needle);
}

void JWQTModelInterface::clear()
{
    if (!size())
    {
        return;
    }
    beginResetModel();
    internalClear();
    endResetModel();
}
