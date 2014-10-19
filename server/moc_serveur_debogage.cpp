/****************************************************************************
** Meta object code from reading C++ file 'serveur_debogage.hpp'
**
** Created: Sun Oct 19 12:11:57 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serveur_debogage.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serveur_debogage.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServeurDebogage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      40,   16,   16,   16, 0x0a,
      67,   65,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ServeurDebogage[] = {
    "ServeurDebogage\0\0reagir_connexion(uint)\0"
    "reagir_deconnexion(uint)\0,\0"
    "reagir_message(uint,Message)\0"
};

void ServeurDebogage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ServeurDebogage *_t = static_cast<ServeurDebogage *>(_o);
        switch (_id) {
        case 0: _t->reagir_connexion((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->reagir_deconnexion((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->reagir_message((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< Message(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ServeurDebogage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ServeurDebogage::staticMetaObject = {
    { &Serveur::staticMetaObject, qt_meta_stringdata_ServeurDebogage,
      qt_meta_data_ServeurDebogage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ServeurDebogage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ServeurDebogage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ServeurDebogage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServeurDebogage))
        return static_cast<void*>(const_cast< ServeurDebogage*>(this));
    return Serveur::qt_metacast(_clname);
}

int ServeurDebogage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Serveur::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
