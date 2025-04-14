#ifndef JWQT_MACROS_H
#define JWQT_MACROS_H

#define JWQT_SINGLE_ARG2(a, b) a, b

#define JWQT_PROPERTY(type, name, uppercasename, defaultvalue) \
private: \
    type m_##name = {defaultvalue}; \
    public: \
    Q_PROPERTY(type name READ name WRITE set##uppercasename NOTIFY name##Changed) \
    type name() const {return m_##name;} \
    void set##uppercasename(type n){if (m_##name == n) return; m_##name = n; emit name##Changed();} \
    Q_SIGNAL \
    void name##Changed(); \
    private:

#endif // JWQT_MACROS_H
