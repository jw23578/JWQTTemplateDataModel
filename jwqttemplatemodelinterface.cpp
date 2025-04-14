#include "jwqttemplatemodelinterface.h"
#include "jwqtobjectinterface.h"

template <class T, class IDType>
JWQTTemplateModelInterface<T, IDType>::JWQTTemplateModelInterface(QQmlApplicationEngine &engine,
                                          const QString &modelName,
                                          const QString &objectName,
                                          const DirectionType direction):
    JWQTModelInterface(engine, modelName, objectName, direction)
{
}

template <class T, class IDType>
JWQTTemplateModelInterface<T, IDType>::JWQTTemplateModelInterface(const QString &objectName,
                                          const DirectionType direction):
    JWQTModelInterface(objectName, direction)
{
}

template <class T, class IDType>
QVariant JWQTTemplateModelInterface<T, IDType>::data(const QModelIndex &index, int role) const
{
    QVariant result;
    int row(getDirection() == reverse ? size() - 1 - index.row() : index.row());
    if (notObjectData(row, role, result))
    {
        return result;
    }
    return QVariant::fromValue<QObject *>(internalGetObject(static_cast<size_t>(row)));
}

template <class T, class IDType>
bool JWQTTemplateModelInterface<T, IDType>::append(T *object)
{
    if (!canAppend(object))
    {
        delete object;
        return false;
    }
    if (getDirection() == reverse)
    {
        beginInsertRows(QModelIndex(), 0, 0);
    }
    else
    {
        beginInsertRows(QModelIndex(), size(), size());
    }
    internalAppend(object);
    endInsertRows();
    setCount(size());
    return true;
}

template <class T, class IDType>
const T &JWQTTemplateModelInterface<T, IDType>::get(size_t index) const
{
    return *internalGetObject(index);
}

template <class T, class IDType>
T *JWQTTemplateModelInterface<T, IDType>::getObject(size_t index) const
{
    return internalGetObject(index);
}

template <class T, class IDType>
const T &JWQTTemplateModelInterface<T, IDType>::operator[](const size_t index) const
{
    return *internalGetObject(index);
}

template<class T, class IDType>
size_t JWQTTemplateModelInterface<T, IDType>::oneBubbleSort(bool withSwapUpdates, compareFunction cf)
{
    size_t swapped(0);
    for (size_t i(0); i < size() - 1; ++i)
    {
        T *a(internalGetObject(i));
        T *b(internalGetObject(i + 1));
        if (cf(*a, *b))
        {
            swap(i, i + 1, withSwapUpdates);
            ++swapped;
        }
    }
    return swapped;
}

template<class T, class IDType>
void JWQTTemplateModelInterface<T, IDType>::bubbleSort(bool withUpdatePerSort, bool withSwapUpdates, compareFunction cf)
{
    if (!withUpdatePerSort && !withSwapUpdates)
    {
        JWQTTemplateModelInterface<T, IDType>::beginResetModel();
    }
    bool done(false);
    while (!done)
    {
        if (withUpdatePerSort)
        {
            JWQTTemplateModelInterface<T, IDType>::beginResetModel();
        }
        done = oneBubbleSort(withSwapUpdates, cf) == 0;
        if (withUpdatePerSort)
        {
            JWQTTemplateModelInterface<T, IDType>::endResetModel();
        }
    }
    if (!withUpdatePerSort && !withSwapUpdates)
    {
        JWQTTemplateModelInterface<T, IDType>::endResetModel();
    }
}

template<class T, class IDType>
void JWQTTemplateModelInterface<T, IDType>::deleteById(const IDType &id)
{
    internalDeleteById(id);
    setCount(size());
}
