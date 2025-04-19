#ifndef JWQTTEMPLATEMODELINTERFACE_H
#define JWQTTEMPLATEMODELINTERFACE_H

#include "jwqtmodelinterface.h"

template <class T, class IDType>
class JWQTTemplateModelInterface : public JWQTModelInterface
{
protected:
    virtual T *internalGetObject(size_t index) const = 0;
    virtual void internalAppend(T *object) = 0;
    virtual bool canAppend(T *object) const = 0;
    virtual T *previousObject(int index) const = 0;
    virtual void internalDeleteById(const IDType &id) = 0;
    void internalFilter(const QString &needle);
public:
    explicit JWQTTemplateModelInterface(QQmlApplicationEngine &engine,
                                const QString &modelName,
                                const QString &objectName,
                                DirectionType const direction);
    explicit JWQTTemplateModelInterface(const QString &objectName,
                                DirectionType const direction);

    virtual ~JWQTTemplateModelInterface() {}

    QVariant data(const QModelIndex &index, int role) const override;

    void deleteById(const IDType &id);
    bool append(T *object);
    const T& get(const size_t index) const;
    const T& operator[](const size_t index) const;

    T *getObject(const size_t index) const;
    T *getObjectByPropertyValue(const QString &property, const QString &value) const;

    typedef std::function<bool(const T &,const T &)> compareFunction;
    size_t oneBubbleSort(bool withSwapUpdates, compareFunction cf);
    void bubbleSort(bool withUpdatePerSort, bool withSwapUpdates, compareFunction cf);
};

template<class T, class IDType>
inline void JWQTTemplateModelInterface<T, IDType>::internalFilter(const QString &needle)
{
    for (size_t i(0); i < size(); ++i)
    {
        T *o(getObject(i));
        o->handleNeedle(needle);
    }
}

template<class T, class IDType>
inline T *JWQTTemplateModelInterface<T, IDType>::getObjectByPropertyValue(const QString &property, const QString &value) const
{
    for (size_t i(0); i < size(); ++i)
    {
        T *o(getObject(i));
        if (o->hasPropertyWithValue(property, value))
        {
            return o;
        }
    }
    return 0;
}

#include "jwqttemplatemodelinterface.cpp"

#endif // JWQTTEMPLATEMODELINTERFACE_H
