/****************************************************************************
** Meta object code from reading C++ file 'testEuclideanDistance.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testEuclideanDistance.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testEuclideanDistance.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EuclideanDistanceTest_t {
    QByteArrayData data[9];
    char stringdata[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EuclideanDistanceTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EuclideanDistanceTest_t qt_meta_stringdata_EuclideanDistanceTest = {
    {
QT_MOC_LITERAL(0, 0, 21), // "EuclideanDistanceTest"
QT_MOC_LITERAL(1, 22, 12), // "initTestCase"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "maxEuclideanDistanceTest"
QT_MOC_LITERAL(4, 61, 18), // "sameAppearanceTest"
QT_MOC_LITERAL(5, 80, 23), // "sameAppearanceDiffSizes"
QT_MOC_LITERAL(6, 104, 23), // "differentAppearanceTest"
QT_MOC_LITERAL(7, 128, 22), // "withTransformationTest"
QT_MOC_LITERAL(8, 151, 15) // "cleanupTestCase"

    },
    "EuclideanDistanceTest\0initTestCase\0\0"
    "maxEuclideanDistanceTest\0sameAppearanceTest\0"
    "sameAppearanceDiffSizes\0differentAppearanceTest\0"
    "withTransformationTest\0cleanupTestCase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EuclideanDistanceTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EuclideanDistanceTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EuclideanDistanceTest *_t = static_cast<EuclideanDistanceTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->maxEuclideanDistanceTest(); break;
        case 2: _t->sameAppearanceTest(); break;
        case 3: _t->sameAppearanceDiffSizes(); break;
        case 4: _t->differentAppearanceTest(); break;
        case 5: _t->withTransformationTest(); break;
        case 6: _t->cleanupTestCase(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EuclideanDistanceTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EuclideanDistanceTest.data,
      qt_meta_data_EuclideanDistanceTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EuclideanDistanceTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EuclideanDistanceTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EuclideanDistanceTest.stringdata))
        return static_cast<void*>(const_cast< EuclideanDistanceTest*>(this));
    return QObject::qt_metacast(_clname);
}

int EuclideanDistanceTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
