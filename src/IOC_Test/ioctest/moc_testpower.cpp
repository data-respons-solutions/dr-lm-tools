/****************************************************************************
** Meta object code from reading C++ file 'testpower.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "testpower.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testpower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestPower_t {
    QByteArrayData data[10];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestPower_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestPower_t qt_meta_stringdata_TestPower = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TestPower"
QT_MOC_LITERAL(1, 10, 15), // "receivedMessage"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "channel"
QT_MOC_LITERAL(4, 35, 5), // "value"
QT_MOC_LITERAL(5, 41, 15), // "signalSemaphore"
QT_MOC_LITERAL(6, 57, 8), // "readGPIO"
QT_MOC_LITERAL(7, 66, 8), // "runTest0"
QT_MOC_LITERAL(8, 75, 8), // "runTest1"
QT_MOC_LITERAL(9, 84, 8) // "runTest2"

    },
    "TestPower\0receivedMessage\0\0channel\0"
    "value\0signalSemaphore\0readGPIO\0runTest0\0"
    "runTest1\0runTest2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestPower[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x08 /* Private */,
       5,    1,   49,    2, 0x08 /* Private */,
       6,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    3,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TestPower::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestPower *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receivedMessage((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 1: _t->signalSemaphore((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->readGPIO((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->runTest0(); break;
        case 4: _t->runTest1(); break;
        case 5: _t->runTest2(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TestPower::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TestPower.data,
    qt_meta_data_TestPower,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestPower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestPower::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestPower.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ITestCase"))
        return static_cast< ITestCase*>(this);
    return QObject::qt_metacast(_clname);
}

int TestPower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
