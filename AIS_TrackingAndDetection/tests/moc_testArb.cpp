/****************************************************************************
** Meta object code from reading C++ file 'testArb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testArb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testArb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ArbTest_t {
    QByteArrayData data[10];
    char stringdata[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArbTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArbTest_t qt_meta_stringdata_ArbTest = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ArbTest"
QT_MOC_LITERAL(1, 8, 12), // "initTestCase"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 23), // "initalResourceLevelTest"
QT_MOC_LITERAL(4, 46, 12), // "addALinkTest"
QT_MOC_LITERAL(5, 59, 25), // "decreaseResourceLevelTest"
QT_MOC_LITERAL(6, 85, 25), // "increaseResourceLevelTest"
QT_MOC_LITERAL(7, 111, 34), // "increaseResourceLevelWithLink..."
QT_MOC_LITERAL(8, 146, 15), // "removeALinkTest"
QT_MOC_LITERAL(9, 162, 20) // "addSameLinkTwiceTest"

    },
    "ArbTest\0initTestCase\0\0initalResourceLevelTest\0"
    "addALinkTest\0decreaseResourceLevelTest\0"
    "increaseResourceLevelTest\0"
    "increaseResourceLevelWithLinksTest\0"
    "removeALinkTest\0addSameLinkTwiceTest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArbTest[] = {

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

void ArbTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArbTest *_t = static_cast<ArbTest *>(_o);
        switch (_id) {
        case 0: _t->initTestCase(); break;
        case 1: _t->initalResourceLevelTest(); break;
        case 2: _t->addALinkTest(); break;
        case 3: _t->decreaseResourceLevelTest(); break;
        case 4: _t->increaseResourceLevelTest(); break;
        case 5: _t->increaseResourceLevelWithLinksTest(); break;
        case 6: _t->removeALinkTest(); break;
        case 7: _t->addSameLinkTwiceTest(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ArbTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ArbTest.data,
      qt_meta_data_ArbTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ArbTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArbTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ArbTest.stringdata))
        return static_cast<void*>(const_cast< ArbTest*>(this));
    return QObject::qt_metacast(_clname);
}

int ArbTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
