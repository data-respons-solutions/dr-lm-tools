/****************************************************************************
** Meta object code from reading C++ file 'testpulsedriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "testpulsedriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testpulsedriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestPulseDriver_t {
    QByteArrayData data[7];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestPulseDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestPulseDriver_t qt_meta_stringdata_TestPulseDriver = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TestPulseDriver"
QT_MOC_LITERAL(1, 16, 13), // "actualChannel"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "channel"
QT_MOC_LITERAL(4, 39, 11), // "setPwmValue"
QT_MOC_LITERAL(5, 51, 5), // "value"
QT_MOC_LITERAL(6, 57, 18) // "receivedAdcMessage"

    },
    "TestPulseDriver\0actualChannel\0\0channel\0"
    "setPwmValue\0value\0receivedAdcMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestPulseDriver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    2,   32,    2, 0x08 /* Private */,
       6,    2,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::UShort, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    3,    5,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    2,    5,

       0        // eod
};

void TestPulseDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestPulseDriver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { quint16 _r = _t->actualChannel((*reinterpret_cast< quint16(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setPwmValue((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 2: _t->receivedAdcMessage((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TestPulseDriver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TestPulseDriver.data,
    qt_meta_data_TestPulseDriver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestPulseDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestPulseDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestPulseDriver.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ITestCase"))
        return static_cast< ITestCase*>(this);
    return QObject::qt_metacast(_clname);
}

int TestPulseDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
