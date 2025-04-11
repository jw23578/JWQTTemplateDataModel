#ifndef TEMPLATEDDATAMODEL_H
#define TEMPLATEDDATAMODEL_H

#include "jwqttemplatemodelinterface.h"
#include "indexedpointercontainer.h"

template <class T>
class JWQTTemplateModel : public JWQTTemplateModelInterface<T>
{
    IndexedPointerContainer<T, QString> objects;
protected:
    T *internalGetObject(size_t index) const override;
    bool canAppend(T *object) const override;
    void internalRemoveByIndex(const size_t index) override;
    void internalAppend(T *object)  override;
    T *previousObject(int index) const override;
    void internalClear() override;
    void swap(size_t i1, size_t i2, bool update) override;
    void internalDeleteById(const QString &id) override;

public:
    JWQTTemplateModel(QQmlApplicationEngine &engine,
                       const QString &modelName,
                       const QString &objectName,
                       typename JWQTTemplateModelInterface<T>::DirectionType const direction = JWQTTemplateModelInterface<T>::forward);

    JWQTTemplateModel(const QString &objectName,
                       typename JWQTTemplateModelInterface<T>::DirectionType const direction = JWQTTemplateModelInterface<T>::forward);

    virtual ~JWQTTemplateModel() {}

    size_t size() const override;
    T *getById(const QString &id);
    void removeById(const QString &id);

    // QAbstractItemModel interface
protected:
    typedef std::function<void(JWQTTemplateModel<T> &)> fetchMoreFunctionPointer;
    fetchMoreFunctionPointer theFetchMoreFunction = {0};
    bool moreDataAvailable = {false};
    void fetchMore(const QModelIndex &parent) override;
    bool canFetchMore(const QModelIndex &parent) const override;
public:
    void setFetchMoreFuntion(fetchMoreFunctionPointer fmfp);
    void lastObjectFetched();
};

#include "jwqttemplatemodel.cpp"

#endif // TEMPLATEDDATAMODEL_H
