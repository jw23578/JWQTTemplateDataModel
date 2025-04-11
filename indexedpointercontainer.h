#ifndef INDEXEDPOINTERCONTAINER_H
#define INDEXEDPOINTERCONTAINER_H

#include <vector>
#include <map>
#include <cstddef>

template<typename Type, typename IDType>
class IndexedPointerContainer
{
    std::vector<Type*> data;
    std::map<IDType, Type*> id2Data;
    bool containerIsOwner;
public:
    typedef typename std::vector<Type*>::iterator VecIterator;
    typedef typename std::map<IDType, Type*> MapIterator;

    IndexedPointerContainer(bool containerIsOwner);
    ~IndexedPointerContainer();

    void add(IDType const &id, Type *t);

    Type *getByIndex(const size_t index) const;
    Type *getById(const IDType &id) const;

    size_t indexById(const IDType &id) const;

    void deleteByIndex(const size_t index);
    size_t deleteById(const IDType &id);

    void swap(const size_t indexA,
              const size_t indexB);

    size_t size() const;

    void clear();

    VecIterator vecBegin();
    VecIterator vecEnd();

    MapIterator mapBegin();
    MapIterator mapEnd();
};

#include "indexedpointercontainer.cpp"

#endif // INDEXEDPOINTERCONTAINER_H
