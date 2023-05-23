/****************************************************************************
** Meta object code from reading C++ file 'mapItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/mapItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mapItem_t {
    QByteArrayData data[7];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mapItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mapItem_t qt_meta_stringdata_mapItem = {
    {
QT_MOC_LITERAL(0, 0, 7), // "mapItem"
QT_MOC_LITERAL(1, 8, 9), // "updateMap"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 14), // "updateLocation"
QT_MOC_LITERAL(4, 34, 10), // "Location_t"
QT_MOC_LITERAL(5, 45, 10), // "updatePath"
QT_MOC_LITERAL(6, 56, 16) // "QVector<QPointF>"

    },
    "mapItem\0updateMap\0\0updateLocation\0"
    "Location_t\0updatePath\0QVector<QPointF>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mapItem[] = {

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
       1,    1,   29,    2, 0x0a /* Public */,
       3,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void mapItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mapItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateMap((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->updateLocation((*reinterpret_cast< Location_t(*)>(_a[1]))); break;
        case 2: _t->updatePath((*reinterpret_cast< QVector<QPointF>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mapItem::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_mapItem.data,
    qt_meta_data_mapItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mapItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mapItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mapItem.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int mapItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
