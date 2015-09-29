/****************************************************************************
** Meta object code from reading C++ file 'trackingAndDetection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../trackingAndDetection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackingAndDetection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TrackingAndDetection_t {
    QByteArrayData data[47];
    char stringdata[662];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrackingAndDetection_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrackingAndDetection_t qt_meta_stringdata_TrackingAndDetection = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TrackingAndDetection"
QT_MOC_LITERAL(1, 21, 11), // "updateImage"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "uchar*"
QT_MOC_LITERAL(4, 41, 4), // "data"
QT_MOC_LITERAL(5, 46, 4), // "cols"
QT_MOC_LITERAL(6, 51, 4), // "rows"
QT_MOC_LITERAL(7, 56, 21), // "updateObjectsPosition"
QT_MOC_LITERAL(8, 78, 1), // "x"
QT_MOC_LITERAL(9, 80, 1), // "y"
QT_MOC_LITERAL(10, 82, 8), // "rotation"
QT_MOC_LITERAL(11, 91, 5), // "width"
QT_MOC_LITERAL(12, 97, 6), // "height"
QT_MOC_LITERAL(13, 104, 13), // "updateNumARBs"
QT_MOC_LITERAL(14, 118, 7), // "numARBs"
QT_MOC_LITERAL(15, 126, 19), // "grabVideoFileConfig"
QT_MOC_LITERAL(16, 146, 10), // "setNetwork"
QT_MOC_LITERAL(17, 157, 8), // "Network*"
QT_MOC_LITERAL(18, 166, 7), // "network"
QT_MOC_LITERAL(19, 174, 22), // "distanceMeasureChanged"
QT_MOC_LITERAL(20, 197, 19), // "DistanceMeasureType"
QT_MOC_LITERAL(21, 217, 19), // "distanceMeasureType"
QT_MOC_LITERAL(22, 237, 18), // "useRotationChanged"
QT_MOC_LITERAL(23, 256, 11), // "useRotation"
QT_MOC_LITERAL(24, 268, 15), // "useScaleChanged"
QT_MOC_LITERAL(25, 284, 8), // "useScale"
QT_MOC_LITERAL(26, 293, 28), // "whichARBsToSearchWithChanged"
QT_MOC_LITERAL(27, 322, 16), // "ARBsToSearchWith"
QT_MOC_LITERAL(28, 339, 21), // "whichARBsToSearchWith"
QT_MOC_LITERAL(29, 361, 27), // "usePredictedLocationChanged"
QT_MOC_LITERAL(30, 389, 20), // "usePredictedLocation"
QT_MOC_LITERAL(31, 410, 12), // "stateChanged"
QT_MOC_LITERAL(32, 423, 12), // "ProgramState"
QT_MOC_LITERAL(33, 436, 5), // "state"
QT_MOC_LITERAL(34, 442, 10), // "getNetwork"
QT_MOC_LITERAL(35, 453, 25), // "changeVideoConfigFilePath"
QT_MOC_LITERAL(36, 479, 6), // "string"
QT_MOC_LITERAL(37, 486, 12), // "filePathName"
QT_MOC_LITERAL(38, 499, 5), // "reset"
QT_MOC_LITERAL(39, 505, 14), // "VideoInputType"
QT_MOC_LITERAL(40, 520, 9), // "inputType"
QT_MOC_LITERAL(41, 530, 12), // "runVideoFeed"
QT_MOC_LITERAL(42, 543, 30), // "initialiseTrackingFromPosition"
QT_MOC_LITERAL(43, 574, 27), // "stimulationThresholdChanged"
QT_MOC_LITERAL(44, 602, 20), // "stimulationThreshold"
QT_MOC_LITERAL(45, 623, 22), // "objectThresholdChanged"
QT_MOC_LITERAL(46, 646, 15) // "objectThreshold"

    },
    "TrackingAndDetection\0updateImage\0\0"
    "uchar*\0data\0cols\0rows\0updateObjectsPosition\0"
    "x\0y\0rotation\0width\0height\0updateNumARBs\0"
    "numARBs\0grabVideoFileConfig\0setNetwork\0"
    "Network*\0network\0distanceMeasureChanged\0"
    "DistanceMeasureType\0distanceMeasureType\0"
    "useRotationChanged\0useRotation\0"
    "useScaleChanged\0useScale\0"
    "whichARBsToSearchWithChanged\0"
    "ARBsToSearchWith\0whichARBsToSearchWith\0"
    "usePredictedLocationChanged\0"
    "usePredictedLocation\0stateChanged\0"
    "ProgramState\0state\0getNetwork\0"
    "changeVideoConfigFilePath\0string\0"
    "filePathName\0reset\0VideoInputType\0"
    "inputType\0runVideoFeed\0"
    "initialiseTrackingFromPosition\0"
    "stimulationThresholdChanged\0"
    "stimulationThreshold\0objectThresholdChanged\0"
    "objectThreshold"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrackingAndDetection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  104,    2, 0x06 /* Public */,
       7,    5,  111,    2, 0x06 /* Public */,
      13,    1,  122,    2, 0x06 /* Public */,
      15,    0,  125,    2, 0x06 /* Public */,
      16,    1,  126,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  129,    2, 0x0a /* Public */,
      22,    1,  132,    2, 0x0a /* Public */,
      24,    1,  135,    2, 0x0a /* Public */,
      26,    1,  138,    2, 0x0a /* Public */,
      29,    1,  141,    2, 0x0a /* Public */,
      31,    1,  144,    2, 0x0a /* Public */,
      34,    0,  147,    2, 0x0a /* Public */,
      35,    1,  148,    2, 0x0a /* Public */,
      38,    1,  151,    2, 0x0a /* Public */,
      41,    0,  154,    2, 0x0a /* Public */,
      42,    4,  155,    2, 0x0a /* Public */,
      43,    1,  164,    2, 0x0a /* Public */,
      45,    1,  167,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, QMetaType::Bool,   30,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   11,   12,
    QMetaType::Void, QMetaType::Double,   44,
    QMetaType::Void, QMetaType::Double,   46,

       0        // eod
};

void TrackingAndDetection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrackingAndDetection *_t = static_cast<TrackingAndDetection *>(_o);
        switch (_id) {
        case 0: _t->updateImage((*reinterpret_cast< uchar*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->updateObjectsPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->updateNumARBs((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->grabVideoFileConfig(); break;
        case 4: _t->setNetwork((*reinterpret_cast< Network*(*)>(_a[1]))); break;
        case 5: _t->distanceMeasureChanged((*reinterpret_cast< DistanceMeasureType(*)>(_a[1]))); break;
        case 6: _t->useRotationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->useScaleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->whichARBsToSearchWithChanged((*reinterpret_cast< ARBsToSearchWith(*)>(_a[1]))); break;
        case 9: _t->usePredictedLocationChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->stateChanged((*reinterpret_cast< ProgramState(*)>(_a[1]))); break;
        case 11: _t->getNetwork(); break;
        case 12: _t->changeVideoConfigFilePath((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 13: _t->reset((*reinterpret_cast< VideoInputType(*)>(_a[1]))); break;
        case 14: _t->runVideoFeed(); break;
        case 15: _t->initialiseTrackingFromPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 16: _t->stimulationThresholdChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->objectThresholdChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TrackingAndDetection::*_t)(uchar * , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrackingAndDetection::updateImage)) {
                *result = 0;
            }
        }
        {
            typedef void (TrackingAndDetection::*_t)(int , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrackingAndDetection::updateObjectsPosition)) {
                *result = 1;
            }
        }
        {
            typedef void (TrackingAndDetection::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrackingAndDetection::updateNumARBs)) {
                *result = 2;
            }
        }
        {
            typedef void (TrackingAndDetection::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrackingAndDetection::grabVideoFileConfig)) {
                *result = 3;
            }
        }
        {
            typedef void (TrackingAndDetection::*_t)(Network * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TrackingAndDetection::setNetwork)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TrackingAndDetection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TrackingAndDetection.data,
      qt_meta_data_TrackingAndDetection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TrackingAndDetection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrackingAndDetection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TrackingAndDetection.stringdata))
        return static_cast<void*>(const_cast< TrackingAndDetection*>(this));
    if (!strcmp(_clname, "Transformations"))
        return static_cast< Transformations*>(const_cast< TrackingAndDetection*>(this));
    return QObject::qt_metacast(_clname);
}

int TrackingAndDetection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void TrackingAndDetection::updateImage(uchar * _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrackingAndDetection::updateObjectsPosition(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrackingAndDetection::updateNumARBs(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrackingAndDetection::grabVideoFileConfig()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void TrackingAndDetection::setNetwork(Network * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
