/****************************************************************************
** Meta object code from reading C++ file 'transformationsTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "transformationsTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'transformationsTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TransformationsTest_t {
    QByteArrayData data[4];
    char stringdata[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransformationsTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransformationsTest_t qt_meta_stringdata_TransformationsTest = {
    {
QT_MOC_LITERAL(0, 0, 19), // "TransformationsTest"
QT_MOC_LITERAL(1, 20, 31), // "rotatePositionByZeroDegreesTest"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 33) // "rotatePositionByNinetyDegrees..."

    },
    "TransformationsTest\0rotatePositionByZeroDegreesTest\0"
    "\0rotatePositionByNinetyDegreesTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransformationsTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TransformationsTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransformationsTest *_t = static_cast<TransformationsTest *>(_o);
        switch (_id) {
        case 0: _t->rotatePositionByZeroDegreesTest(); break;
        case 1: _t->rotatePositionByNinetyDegreesTest(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TransformationsTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TransformationsTest.data,
      qt_meta_data_TransformationsTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TransformationsTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransformationsTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TransformationsTest.stringdata))
        return static_cast<void*>(const_cast< TransformationsTest*>(this));
    return QObject::qt_metacast(_clname);
}

int TransformationsTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
