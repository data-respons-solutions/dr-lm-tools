/****************************************************************************
** Meta object code from reading C++ file 'textreporter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "textreporter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textreporter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextReporter_t {
    QByteArrayData data[11];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextReporter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextReporter_t qt_meta_stringdata_TextReporter = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TextReporter"
QT_MOC_LITERAL(1, 13, 18), // "setCurrentTestName"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "name"
QT_MOC_LITERAL(4, 38, 13), // "testHasFailed"
QT_MOC_LITERAL(5, 52, 3), // "why"
QT_MOC_LITERAL(6, 56, 10), // "testHasRun"
QT_MOC_LITERAL(7, 67, 14), // "allTestsPassed"
QT_MOC_LITERAL(8, 82, 16), // "printTestResults"
QT_MOC_LITERAL(9, 99, 7), // "verbose"
QT_MOC_LITERAL(10, 107, 14) // "getFailedCount"

    },
    "TextReporter\0setCurrentTestName\0\0name\0"
    "testHasFailed\0why\0testHasRun\0"
    "allTestsPassed\0printTestResults\0verbose\0"
    "getFailedCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextReporter[] = {

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
       1,    1,   44,    2, 0x0a /* Public */,
       4,    1,   47,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    1,   52,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::UInt,

       0        // eod
};

void TextReporter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextReporter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setCurrentTestName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->testHasFailed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->testHasRun(); break;
        case 3: { bool _r = _t->allTestsPassed();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->printTestResults((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: { quint32 _r = _t->getFailedCount();
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TextReporter::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TextReporter.data,
    qt_meta_data_TextReporter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TextReporter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextReporter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextReporter.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ITestReporter"))
        return static_cast< ITestReporter*>(this);
    return QObject::qt_metacast(_clname);
}

int TextReporter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
