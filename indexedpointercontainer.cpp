#include "indexedpointercontainer.h"


template<typename Type, typename IDType>
IndexedPointerContainer<Type, IDType>::IndexedPointerContainer(bool containerIsOwner):
    containerIsOwner(containerIsOwner)
{

}

template<typename Type, typename IDType>
IndexedPointerContainer<Type, IDType>::~IndexedPointerContainer()
{
    clear();
}

template<typename Type, typename IDType>
void IndexedPointerContainer<Type, IDType>::add(const IDType &id, Type *t)
{
    data.push_back(t);
    id2Data[id] = t;
}

template<typename Type, typename IDType>
Type *IndexedPointerContainer<Type, IDType>::getByIndex(const size_t index) const
{
    return data[index];
}

template<typename Type, typename IDType>
Type *IndexedPointerContainer<Type, IDType>::getById(const IDType &id) const
{
    auto it(id2Data.find(id));
    if (it == id2Data.end())
    {
        return 0;
    }
    return it->second;
}

template<typename Type, typename IDType>
size_t IndexedPointerContainer<Type, IDType>::indexById(const IDType &id) const
{
    auto it(id2Data.find(id));
    if (it == id2Data.end())
    {
        return -1;
    }
    for (size_t index(0); index < data.size(); ++index)
    {
        if (data[index] == it->second)
        {
            return index;
        }
    }
    return -1;
}

template<typename Type, typename IDType>
void IndexedPointerContainer<Type, IDType>::deleteByIndex(const size_t index)
{
    if (index >= size())
    {
        return;
    }
    Type *t(data[index]);
    data.erase(vecBegin() + index);
    auto it(id2Data.begin());
    while (it != id2Data.end())
    {
        if (it->second == t)
        {
            id2Data.erase(it);
            break;
        }
        ++it;
    }
    delete t;
}

template<typename Type, typename IDType>
size_t IndexedPointerContainer<Type, IDType>::deleteById(const IDType &id)
{
    auto it(id2Data.find(id));
    if (it == id2Data.end())
    {
        return -1;
    }
    Type *t(it->second);
    id2Data.erase(it);
    size_t index(indexById(id));
    if (index != -1)
    {
        data.erase(data.begin() + index);
    }
    delete t;
    return index;
}

template<typename Type, typename IDType>
void IndexedPointerContainer<Type, IDType>::swap(const size_t indexA,
                                                 const size_t indexB)
{
    Type *t(data[indexA]);
    data[indexA] = data[indexB];
    data[indexB] = t;
}

template<typename Type, typename IDType>
size_t IndexedPointerContainer<Type, IDType>::size() const
{
    return data.size();
}

template<typename Type, typename IDType>
void IndexedPointerContainer<Type, IDType>::clear()
{
    if (containerIsOwner)
    {
        for (auto t: data)
        {
            delete t;
        }
    }
    data.clear();
    id2Data.clear();
}

template<typename Type, typename IDType>
typename IndexedPointerContainer<Type, IDType>::VecIterator IndexedPointerContainer<Type, IDType>::vecBegin()
{
    return data.begin();
}

template<typename Type, typename IDType>
typename IndexedPointerContainer<Type, IDType>::VecIterator IndexedPointerContainer<Type, IDType>::vecEnd()
{

}

template<typename Type, typename IDType>
typename IndexedPointerContainer<Type, IDType>::MapIterator IndexedPointerContainer<Type, IDType>::mapBegin()
{
    return id2Data.begin();
}

template<typename Type, typename IDType>
typename IndexedPointerContainer<Type, IDType>::MapIterator IndexedPointerContainer<Type, IDType>::mapEnd()
{
    return id2Data.end();
}
