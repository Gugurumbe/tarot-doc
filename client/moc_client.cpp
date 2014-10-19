/****************************************************************************
** Meta object code from reading C++ file 'client.hpp'
**
** Created: Sun Oct 19 11:36:06 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "client.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      19,    7,    7,    7, 0x05,
      32,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    7,    7,    7, 0x0a,
      62,   60,    7,    7, 0x0a,
      91,    7,    7,    7, 0x0a,
     105,    7,    7,    7, 0x0a,
     122,    7,    7,    7, 0x0a,
     142,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0connecte()\0deconnecte()\0"
    "recu(Message)\0reconnecter()\0,\0"
    "connecter(QHostAddress,uint)\0deconnecter()\0"
    "envoyer(Message)\0envoyer(QByteArray)\0"
    "recevoir()\0"
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Client *_t = static_cast<Client *>(_o);
        switch (_id) {
        case 0: _t->connecte(); break;
        case 1: _t->deconnecte(); break;
        case 2: _t->recu((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 3: _t->reconnecter(); break;
        case 4: _t->connecter((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 5: _t->deconnecter(); break;
        case 6: _t->envoyer((*reinterpret_cast< Message(*)>(_a[1]))); break;
        case 7: _t->envoyer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->recevoir(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Client::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Client::connecte()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Client::deconnecte()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Client::recu(Message _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
