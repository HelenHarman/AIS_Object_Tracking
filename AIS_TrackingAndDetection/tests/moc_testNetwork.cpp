/****************************************************************************
** Meta object code from reading C++ file 'testNetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testNetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testNetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NetworkTest_t {
    QByteArrayData data[10];
    char stringdata[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkTest_t qt_meta_stringdata_NetworkTest = {
    {
QT_MOC_LITERAL(0, 0, 11), // "NetworkTest"
QT_MOC_LITERAL(1, 12, 12), // "initTestCase"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 24), // "initialSizeOfNetworkTest"
QT_MOC_LITERAL(4, 51, 37), // "addNewAppearanceWithLargeDist..."
QT_MOC_LITERAL(5, 89, 37), // "addNewAppearanceWithSmallDist..."
QT_MOC_LITERAL(6, 127, 21), // "getAllAppearancesTest"
QT_MOC_LITERAL(7, 149, 25), // "getLastAndHighestARBsTest"
QT_MOC_LITERAL(8, 175, 29), // "getARBsWithAboveAverageRLTest"
QT_MOC_LITERAL(9, 205, 24) // "getPredictedLocationTest"

    },
    "NetworkTest\0initTestCase\0\0"
    "initialSizeOfNetworkTest\0"
    "addNewAppearanceWithLargeDistanceTest\0"
    "addNewAppearanceWithSmallDistanceTest\0"
    "getAllAppearancesTest\0getLastAndHighestARBsTest\0"
    "getARBsWithAboveAverageRLTest\0"
    "getPredictedLocationTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NetworkTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkTest *_t = static_cast<NetworkTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->initialSizeOfNetworkTest(); break;
        case 2: _t->addNewAppearanceWithLargeDistanceTest(); break;
        case 3: _t->addNewAppearanceWithSmallDistanceTest(); break;
        case 4: _t->getAllAppearancesTest(); break;
        case 5: _t->getLastAndHighestARBsTest(); break;
        case 6: _t->getARBsWithAboveAverageRLTest(); break;
        case 7: _t->getPredictedLocationTest(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NetworkTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NetworkTest.data,
      qt_meta_data_NetworkTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NetworkTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkTest.stringdata))
        return static_cast<void*>(const_cast< NetworkTest*>(this));
    return QObject::qt_metacast(_clname);
}

int NetworkTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
