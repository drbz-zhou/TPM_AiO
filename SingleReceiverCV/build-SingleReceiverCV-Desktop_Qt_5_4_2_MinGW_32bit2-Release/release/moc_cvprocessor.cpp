/****************************************************************************
** Meta object code from reading C++ file 'cvprocessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../Work/Projects/iQLab/Chair Receiver/source/include/cvprocessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cvprocessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CVProcessor_t {
    QByteArrayData data[5];
    char stringdata[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVProcessor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVProcessor_t qt_meta_stringdata_CVProcessor = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CVProcessor"
QT_MOC_LITERAL(1, 12, 12), // "processFrame"
QT_MOC_LITERAL(2, 25, 12), // "data_spatial"
QT_MOC_LITERAL(3, 38, 0), // ""
QT_MOC_LITERAL(4, 39, 7) // "inFrame"

    },
    "CVProcessor\0processFrame\0data_spatial\0"
    "\0inFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2, 0x80000000 | 2,    4,

       0        // eod
};

void CVProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVProcessor *_t = static_cast<CVProcessor *>(_o);
        switch (_id) {
        case 0: { data_spatial _r = _t->processFrame((*reinterpret_cast< data_spatial(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< data_spatial*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject CVProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CVProcessor.data,
      qt_meta_data_CVProcessor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CVProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CVProcessor.stringdata))
        return static_cast<void*>(const_cast< CVProcessor*>(this));
    return QObject::qt_metacast(_clname);
}

int CVProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
