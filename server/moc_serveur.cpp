/****************************************************************************
** Meta object code from reading C++ file 'serveur.hpp'
**
** Created: Sun Oct 19 12:11:55 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serveur.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serveur.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Serveur[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      27,   25,    8,    8, 0x05,
      57,    8,    8,    8, 0x05,
      75,   25,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      97,    8,    8,    8, 0x0a,
     113,  108,    8,    8, 0x0a,
     131,    8,    8,    8, 0x0a,
     141,    8,    8,    8, 0x0a,
     148,    8,    8,    8, 0x0a,
     166,   25,    8,    8, 0x0a,
     191,   25,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Serveur[] = {
    "Serveur\0\0connexion(uint)\0,\0"
    "message_brut(uint,QByteArray)\0"
    "deconnexion(uint)\0message(uint,Message)\0"
    "accepter()\0sock\0enlever(QObject*)\0"
    "enlever()\0lire()\0deconnecter(uint)\0"
    "envoyer(uint,QByteArray)\0envoyer(uint,Message)\0"
};

void Serveur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Serveur *_t = static_cast<Serveur *>(_o);
        switch (_id) {
        case 0: _t->connexion((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->message_brut((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->deconnexion((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: _t->message((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< Message(*)>(_a[2]))); break;
        case 4: _t->accepter(); break;
        case 5: _t->enlever((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 6: _t->enlever(); break;
        case 7: _t->lire(); break;
        case 8: _t->deconnecter((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 9: _t->envoyer((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 10: _t->envoyer((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< Message(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Serveur::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Serveur::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Serveur,
      qt_meta_data_Serveur, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Serveur::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Serveur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Serveur::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Serveur))
        return static_cast<void*>(const_cast< Serveur*>(this));
    return QObject::qt_metacast(_clname);
}

int Serveur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Serveur::connexion(unsigned int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Serveur::message_brut(unsigned int _t1, QByteArray _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Serveur::deconnexion(unsigned int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Serveur::message(unsigned int _t1, Message _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
