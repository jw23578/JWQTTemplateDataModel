#include "jwqttemplatemodel.h"

template<class T, class IDType>
size_t JWQTTemplateModel<T, IDType>::size() const
{
    return objects.size();
}

template<class T, class IDType>
T *JWQTTemplateModel<T, IDType>::internalGetObject(size_t index) const
{
    return objects.getByIndex(index);
}

template<class T, class IDType>
bool JWQTTemplateModel<T, IDType>::canAppend(T *object) const
{
    T *alreadyAdded(objects.getById(object->id()));
    if (alreadyAdded)
    {
        alreadyAdded->assign(*object);
        return false;
    }
    return true;
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::internalRemoveByIndex(const size_t index)
{
    if (index >= objects.size())
    {
        return;
    }
    size_t visibleIndex(index);
    if (JWQTTemplateModelInterface<T, IDType>::getDirection() == JWQTTemplateModelInterface<T, IDType>::reverse)
    {
        visibleIndex = size() - 1 - index;
    }
    JWQTTemplateModelInterface<T, IDType>::beginRemoveRows(QModelIndex(), visibleIndex, visibleIndex);
    objects.deleteByIndex(index);
    JWQTTemplateModelInterface<T, IDType>::endRemoveRows();
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::internalAppend(T *object)
{
    objects.add(object->id(), object);
}

template<class T, class IDType>
T *JWQTTemplateModel<T, IDType>::previousObject(int index) const
{
    if (index == 0)
    {
        return 0;
    }
    return objects.getByIndex(index - 1);
}

template<class T, class IDType>
JWQTTemplateModel<T, IDType>::JWQTTemplateModel(QQmlApplicationEngine &engine,
                                          const QString &modelName,
                                          const QString &objectName,
                                          typename JWQTTemplateModelInterface<T, IDType>::DirectionType const direction):
    JWQTTemplateModelInterface<T, IDType>(engine,
                          modelName,
                          objectName,
                          direction),
    objects(true)
{

}

template<class T, class IDType>
JWQTTemplateModel<T, IDType>::JWQTTemplateModel(const QString &objectName,
                                          const typename JWQTTemplateModelInterface<T, IDType>::DirectionType direction):
    JWQTTemplateModelInterface<T, IDType>(objectName,
                          direction)
  ,
    objects(true)
{

}

template<class T, class IDType>
T *JWQTTemplateModel<T, IDType>::getById(const IDType &id)
{
    return objects.getById(id);
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::removeById(const IDType &id)
{
    size_t index(objects.indexById(id));
    if (index >= objects.size())
    {
        return;
    }
    this->removeByIndex(index);
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::internalClear()
{
    objects.clear();
    moreDataAvailable = true;
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::swap(size_t i1,
                                 size_t i2,
                                 bool update)
{
    if (i2 <= i1)
    {
        return;
    }
    if (update)
    {
        JWQTTemplateModelInterface<T, IDType>::beginMoveRows(QModelIndex(), i2, i2, QModelIndex(), i1);
    }
    objects.swap(i1, i2);
    if (update)
    {
        JWQTTemplateModelInterface<T, IDType>::endMoveRows();
    }
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::internalDeleteById(const IDType &id)
{
    size_t index(objects.indexById(id));
    if (index == static_cast<size_t>(-1))
    {
        return;
    }
    JWQTTemplateModelInterface<T, IDType>::beginRemoveRows(QModelIndex(), index, index);
    objects.deleteByIndex(index);
    JWQTTemplateModelInterface<T, IDType>::endRemoveRows();
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if (theFetchMoreFunction)
    {
        theFetchMoreFunction(*this);
    }
}

template<class T, class IDType>
bool JWQTTemplateModel<T, IDType>::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return moreDataAvailable;
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::setFetchMoreFuntion(fetchMoreFunctionPointer fmfp)
{
    theFetchMoreFunction = fmfp;
    moreDataAvailable = true;
}

template<class T, class IDType>
void JWQTTemplateModel<T, IDType>::lastObjectFetched()
{
    moreDataAvailable = false;
}
