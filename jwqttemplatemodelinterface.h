#ifndef JWQTTEMPLATEMODELINTERFACE_H
#define JWQTTEMPLATEMODELINTERFACE_H

#include "jwqtmodelinterface.h"

template <class T>
class JWQTTemplateModelInterface : public JWQTModelInterface
{
protected:
    virtual T *internalGetObject(size_t index) const = 0;
    virtual void internalRemoveByIndex(const size_t index) = 0;
    virtual void internalAppend(T *object) = 0;
    virtual bool canAppend(T *object) const = 0;
    virtual T *previousObject(int index) const = 0;
    virtual void internalClear() = 0;
    virtual void swap(size_t i1, size_t i2, bool update) = 0;
public:
    explicit JWQTTemplateModelInterface(QQmlApplicationEngine &engine,
                                const QString &modelName,
                                const QString &objectName,
                                DirectionType const direction);
    explicit JWQTTemplateModelInterface(const QString &objectName,
                                DirectionType const direction);

    virtual ~JWQTTemplateModelInterface() {}

    QVariant data(const QModelIndex &index, int role) const override;

    bool append(T *object);
    void removeByIndex(const size_t index);
    void clear();
    const T& get(const size_t index) const;
    const T& operator[](const size_t index) const;

    typedef std::function<bool(const T &,const T &)> compareFunction;
    size_t oneBubbleSort(bool withSwapUpdates, compareFunction cf);
    void bubbleSort(bool withUpdatePerSort, bool withSwapUpdates, compareFunction cf);
};

#include "jwqttemplatemodelinterface.cpp"

#endif // JWQTTEMPLATEMODELINTERFACE_H
