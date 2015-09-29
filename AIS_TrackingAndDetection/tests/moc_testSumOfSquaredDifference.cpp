/****************************************************************************
** Meta object code from reading C++ file 'testSumOfSquaredDifference.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testSumOfSquaredDifference.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testSumOfSquaredDifference.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SumOfSquaredDifferenceTest_t {
    QByteArrayData data[8];
    char stringdata[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SumOfSquaredDifferenceTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SumOfSquaredDifferenceTest_t qt_meta_stringdata_SumOfSquaredDifferenceTest = {
    {
QT_MOC_LITERAL(0, 0, 26), // "SumOfSquaredDifferenceTest"
QT_MOC_LITERAL(1, 27, 12), // "initTestCase"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 29), // "maxSumOfSquaredDifferenceTest"
QT_MOC_LITERAL(4, 71, 18), // "sameAppearanceTest"
QT_MOC_LITERAL(5, 90, 23), // "sameAppearanceDiffSizes"
QT_MOC_LITERAL(6, 114, 23), // "differentAppearanceTest"
QT_MOC_LITERAL(7, 138, 15) // "cleanupTestCase"

    },
    "SumOfSquaredDifferenceTest\0initTestCase\0"
    "\0maxSumOfSquaredDifferenceTest\0"
    "sameAppearanceTest\0sameAppearanceDiffSizes\0"
    "differentAppearanceTest\0cleanupTestCase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SumOfSquaredDifferenceTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SumOfSquaredDifferenceTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SumOfSquaredDifferenceTest *_t = static_cast<SumOfSquaredDifferenceTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->maxSumOfSquaredDifferenceTest(); break;
        case 2: _t->sameAppearanceTest(); break;
        case 3: _t->sameAppearanceDiffSizes(); break;
        case 4: _t->differentAppearanceTest(); break;
        case 5: _t->cleanupTestCase(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SumOfSquaredDifferenceTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SumOfSquaredDifferenceTest.data,
      qt_meta_data_SumOfSquaredDifferenceTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SumOfSquaredDifferenceTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SumOfSquaredDifferenceTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SumOfSquaredDifferenceTest.stringdata))
        return static_cast<void*>(const_cast< SumOfSquaredDifferenceTest*>(this));
    return QObject::qt_metacast(_clname);
}

int SumOfSquaredDifferenceTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
