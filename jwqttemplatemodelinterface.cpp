#include "jwqttemplatemodelinterface.h"
#include "dataobjectinterface.h"

template <class T>
JWQTTemplateModelInterface<T>::JWQTTemplateModelInterface(QQmlApplicationEngine &engine,
                                          const QString &modelName,
                                          const QString &objectName,
                                          const DirectionType direction):
    JWQTModelInterface(engine, modelName, objectName, direction)
{
}

template<class T>
JWQTTemplateModelInterface<T>::JWQTTemplateModelInterface(const QString &objectName,
                                          const DirectionType direction):
    JWQTModelInterface(objectName, direction)
{
}

template <class T>
QVariant JWQTTemplateModelInterface<T>::data(const QModelIndex &index, int role) const
{
    QVariant result;
    int row(getDirection() == reverse ? size() - 1 - index.row() : index.row());
    if (notObjectData(row, role, result))
    {
        return result;
    }
    return QVariant::fromValue<QObject *>(internalGetObject(static_cast<size_t>(row)));
}

template <class T>
bool JWQTTemplateModelInterface<T>::append(T *object)
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

template<class T>
void JWQTTemplateModelInterface<T>::removeByIndex(const size_t index)
{
    internalRemoveByIndex(index);
}

template<class T>
void JWQTTemplateModelInterface<T>::clear()
{
    if (!size())
    {
        return;
    }
    beginResetModel();
    internalClear();
    endResetModel();
}

template<class T>
const T &JWQTTemplateModelInterface<T>::get(size_t index) const
{
    return *internalGetObject(index);
}

template<class T>
const T &JWQTTemplateModelInterface<T>::operator[](const size_t index) const
{
    return internalGetObject(index);
}

template<class T>
size_t JWQTTemplateModelInterface<T>::oneBubbleSort(bool withSwapUpdates, compareFunction cf)
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

template<class T>
void JWQTTemplateModelInterface<T>::bubbleSort(bool withUpdatePerSort, bool withSwapUpdates, compareFunction cf)
{
    if (!withUpdatePerSort && !withSwapUpdates)
    {
        JWQTTemplateModelInterface<T>::beginResetModel();
    }
    bool done(false);
    while (!done)
    {
        if (withUpdatePerSort)
        {
            JWQTTemplateModelInterface<T>::beginResetModel();
        }
        done = oneBubbleSort(withSwapUpdates, cf) == 0;
        if (withUpdatePerSort)
        {
            JWQTTemplateModelInterface<T>::endResetModel();
        }
    }
    if (!withUpdatePerSort && !withSwapUpdates)
    {
        JWQTTemplateModelInterface<T>::endResetModel();
    }
}
