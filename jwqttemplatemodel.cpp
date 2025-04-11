#include "jwqttemplatemodel.h"

template<class T>
size_t JWQTTemplateModel<T>::size() const
{
    return objects.size();
}

template<class T>
T *JWQTTemplateModel<T>::internalGetObject(size_t index) const
{
    return objects.getByIndex(index);
}

template<class T>
bool JWQTTemplateModel<T>::canAppend(T *object) const
{
    T *alreadyAdded(objects.getById(object->id()));
    if (alreadyAdded)
    {
        alreadyAdded->assign(*object);
        return false;
    }
    return true;
}

template<class T>
void JWQTTemplateModel<T>::internalRemoveByIndex(const size_t index)
{
    if (index >= objects.size())
    {
        return;
    }
    size_t visibleIndex(index);
    if (JWQTTemplateModelInterface<T>::getDirection() == JWQTTemplateModelInterface<T>::reverse)
    {
        visibleIndex = size() - 1 - index;
    }
    JWQTTemplateModelInterface<T>::beginRemoveRows(QModelIndex(), visibleIndex, visibleIndex);
    objects.deleteByIndex(index);
    JWQTTemplateModelInterface<T>::endRemoveRows();
}

template<class T>
void JWQTTemplateModel<T>::internalAppend(T *object)
{
    objects.add(object->id(), object);
}

template<class T>
T *JWQTTemplateModel<T>::previousObject(int index) const
{
    if (index == 0)
    {
        return 0;
    }
    return objects.getByIndex(index - 1);
}

template <class T>
JWQTTemplateModel<T>::JWQTTemplateModel(QQmlApplicationEngine &engine,
                                          const QString &modelName,
                                          const QString &objectName,
                                          typename JWQTTemplateModelInterface<T>::DirectionType const direction):
    JWQTTemplateModelInterface<T>(engine,
                          modelName,
                          objectName,
                          direction),
    objects(true)
{

}

template<class T>
JWQTTemplateModel<T>::JWQTTemplateModel(const QString &objectName,
                                          const typename JWQTTemplateModelInterface<T>::DirectionType direction):
    JWQTTemplateModelInterface<T>(objectName,
                          direction)
  ,
    objects(true)
{

}

template<class T>
T *JWQTTemplateModel<T>::getById(const QString &id)
{
    return objects.getById(id);
}

template<class T>
void JWQTTemplateModel<T>::removeById(const QString &id)
{
    size_t index(objects.indexById(id));
    if (index >= objects.size())
    {
        return;
    }
    this->removeByIndex(index);
}

template<class T>
void JWQTTemplateModel<T>::internalClear()
{
    objects.clear();
    moreDataAvailable = true;
}

template<class T>
void JWQTTemplateModel<T>::swap(size_t i1,
                                 size_t i2,
                                 bool update)
{
    if (i2 <= i1)
    {
        return;
    }
    if (update)
    {
        JWQTTemplateModelInterface<T>::beginMoveRows(QModelIndex(), i2, i2, QModelIndex(), i1);
    }
    objects.swap(i1, i2);
    if (update)
    {
        JWQTTemplateModelInterface<T>::endMoveRows();
    }
}

template<class T>
void JWQTTemplateModel<T>::internalDeleteById(const QString &id)
{
    size_t index(objects.indexById(id));
    if (index == static_cast<size_t>(-1))
    {
        return;
    }
    JWQTTemplateModelInterface<T>::beginRemoveRows(QModelIndex(), index, index);
    objects.deleteByIndex(index);
    JWQTTemplateModelInterface<T>::endRemoveRows();
}

template<class T>
void JWQTTemplateModel<T>::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (theFetchMoreFunction)
    {
        theFetchMoreFunction(*this);
    }
}

template<class T>
bool JWQTTemplateModel<T>::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return moreDataAvailable;
}

template<class T>
void JWQTTemplateModel<T>::setFetchMoreFuntion(fetchMoreFunctionPointer fmfp)
{
    theFetchMoreFunction = fmfp;
    moreDataAvailable = true;
}

template<class T>
void JWQTTemplateModel<T>::lastObjectFetched()
{
    moreDataAvailable = false;
}
