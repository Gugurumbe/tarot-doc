/****************************************************************************
** Meta object code from reading C++ file 'client_debogage.hpp'
**
** Created: Sun Oct 19 11:36:08 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "client_debogage.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client_debogage.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientDebogage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      36,   15,   15,   15, 0x0a,
      58,   15,   15,   15, 0x0a,
      83,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ClientDebogage[] = {
    "ClientDebogage\0\0traiter_connexion()\0"
    "traiter_deconnexion()\0traiter_message(Message)\0"
    "demander_ordres()\0"
};

void ClientDebogage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClientDebogage *_t = static_cast<ClientDebogage *>(_o);
        switch (_id) {
        case 0: _t->traiter_connexion(); break;
        case 1: _t->traiter_deconnexion(); break;
        case 2: _t->traiter_message((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 3: _t->demander_ordres(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ClientDebogage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClientDebogage::staticMetaObject = {
    { &Client::staticMetaObject, qt_meta_stringdata_ClientDebogage,
      qt_meta_data_ClientDebogage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientDebogage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientDebogage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientDebogage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientDebogage))
        return static_cast<void*>(const_cast< ClientDebogage*>(this));
    return Client::qt_metacast(_clname);
}

int ClientDebogage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Client::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
