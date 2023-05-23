/****************************************************************************
** Meta object code from reading C++ file 'QBattery.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/QBattery.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBattery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QBattery_t {
    QByteArrayData data[15];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QBattery_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QBattery_t qt_meta_stringdata_QBattery = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QBattery"
QT_MOC_LITERAL(1, 9, 12), // "valueChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "value"
QT_MOC_LITERAL(4, 29, 12), // "setElecValue"
QT_MOC_LITERAL(5, 42, 15), // "setWarningValue"
QT_MOC_LITERAL(6, 58, 12), // "warningValue"
QT_MOC_LITERAL(7, 71, 8), // "minValue"
QT_MOC_LITERAL(8, 80, 8), // "maxValue"
QT_MOC_LITERAL(9, 89, 17), // "warningColorStart"
QT_MOC_LITERAL(10, 107, 15), // "warningColorEnd"
QT_MOC_LITERAL(11, 123, 16), // "normalColorStart"
QT_MOC_LITERAL(12, 140, 14), // "normalColorEnd"
QT_MOC_LITERAL(13, 155, 13), // "animatonMsecs"
QT_MOC_LITERAL(14, 169, 11) // "borderColor"

    },
    "QBattery\0valueChanged\0\0value\0setElecValue\0"
    "setWarningValue\0warningValue\0minValue\0"
    "maxValue\0warningColorStart\0warningColorEnd\0"
    "normalColorStart\0normalColorEnd\0"
    "animatonMsecs\0borderColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QBattery[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      10,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       5,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    6,

 // properties: name, type, flags
       7, QMetaType::Double, 0x00095103,
       8, QMetaType::Double, 0x00095103,
       3, QMetaType::Double, 0x00495103,
       6, QMetaType::Double, 0x00095103,
       9, QMetaType::QColor, 0x00095103,
      10, QMetaType::QColor, 0x00095103,
      11, QMetaType::QColor, 0x00095103,
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::Int, 0x00095003,
      14, QMetaType::QColor, 0x00095103,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,

       0        // eod
};

void QBattery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QBattery *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setElecValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setElecValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setWarningValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setWarningValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QBattery::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QBattery::valueChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QBattery *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->minValue(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->maxValue(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->value(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->warningValue(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->warningColorStart(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->warningColorEnd(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->normalColorStart(); break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->normalColorEnd(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->animationMsecs(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->borderColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QBattery *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinValue(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setMaxValue(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setValue(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setWarningValue(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setWarningColorStart(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setWarningColorEnd(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setNormalColorStart(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setNormalColorEnd(*reinterpret_cast< QColor*>(_v)); break;
        case 8: _t->setAnimationMsecs(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QBattery::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QBattery.data,
    qt_meta_data_QBattery,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QBattery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QBattery::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QBattery.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QBattery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QBattery::valueChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
