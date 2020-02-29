/****************************************************************************
** Meta object code from reading C++ file 'room21.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../myfirst/room21.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'room21.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Room21_t {
    QByteArrayData data[11];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Room21_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Room21_t qt_meta_stringdata_Room21 = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Room21"
QT_MOC_LITERAL(1, 7, 7), // "move_up"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 9), // "move_down"
QT_MOC_LITERAL(4, 26, 18), // "on_pb_deal_clicked"
QT_MOC_LITERAL(5, 45, 16), // "on_pb_25_clicked"
QT_MOC_LITERAL(6, 62, 16), // "on_pb_50_clicked"
QT_MOC_LITERAL(7, 79, 17), // "on_pb_100_clicked"
QT_MOC_LITERAL(8, 97, 17), // "on_pb_hit_clicked"
QT_MOC_LITERAL(9, 115, 20), // "on_pb_double_clicked"
QT_MOC_LITERAL(10, 136, 19) // "on_pb_stand_clicked"

    },
    "Room21\0move_up\0\0move_down\0on_pb_deal_clicked\0"
    "on_pb_25_clicked\0on_pb_50_clicked\0"
    "on_pb_100_clicked\0on_pb_hit_clicked\0"
    "on_pb_double_clicked\0on_pb_stand_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Room21[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
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

void Room21::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Room21 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->move_up(); break;
        case 1: _t->move_down(); break;
        case 2: _t->on_pb_deal_clicked(); break;
        case 3: _t->on_pb_25_clicked(); break;
        case 4: _t->on_pb_50_clicked(); break;
        case 5: _t->on_pb_100_clicked(); break;
        case 6: _t->on_pb_hit_clicked(); break;
        case 7: _t->on_pb_double_clicked(); break;
        case 8: _t->on_pb_stand_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Room21::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Room21.data,
    qt_meta_data_Room21,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Room21::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Room21::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Room21.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Room21::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
