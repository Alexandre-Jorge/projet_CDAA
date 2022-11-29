/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../appliContact/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
<<<<<<< HEAD
    QByteArrayData data[14];
    char stringdata0[133];
=======
    QByteArrayData data[11];
    char stringdata0[78];
>>>>>>> d8656cc733c777f4b3202f8d9e8dc61c81894664
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
<<<<<<< HEAD
QT_MOC_LITERAL(1, 11, 20), // "toAffichagePrincipal"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 18), // "affichagePrincipal"
QT_MOC_LITERAL(4, 52, 20), // "affichageCreeContact"
QT_MOC_LITERAL(5, 73, 16), // "affichageContact"
QT_MOC_LITERAL(6, 90, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 107, 11), // "creeContact"
QT_MOC_LITERAL(8, 119, 1), // "n"
QT_MOC_LITERAL(9, 121, 2), // "pr"
QT_MOC_LITERAL(10, 124, 1), // "e"
QT_MOC_LITERAL(11, 126, 1), // "m"
QT_MOC_LITERAL(12, 128, 1), // "t"
QT_MOC_LITERAL(13, 130, 2) // "ph"

    },
    "MainWindow\0toAffichagePrincipal\0\0"
    "affichagePrincipal\0affichageCreeContact\0"
    "affichageContact\0QListWidgetItem*\0"
    "creeContact\0n\0pr\0e\0m\0t\0ph"
=======
QT_MOC_LITERAL(1, 11, 18), // "affichagePrincipal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "affichageCreeContact"
QT_MOC_LITERAL(4, 52, 11), // "creeContact"
QT_MOC_LITERAL(5, 64, 1), // "n"
QT_MOC_LITERAL(6, 66, 2), // "pr"
QT_MOC_LITERAL(7, 69, 1), // "e"
QT_MOC_LITERAL(8, 71, 1), // "m"
QT_MOC_LITERAL(9, 73, 1), // "t"
QT_MOC_LITERAL(10, 75, 2) // "ph"

    },
    "MainWindow\0affichagePrincipal\0\0"
    "affichageCreeContact\0creeContact\0n\0"
    "pr\0e\0m\0t\0ph"
>>>>>>> d8656cc733c777f4b3202f8d9e8dc61c81894664
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       7,    6,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,   11,   12,   13,
=======
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,    8,    9,   10,
>>>>>>> d8656cc733c777f4b3202f8d9e8dc61c81894664

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
<<<<<<< HEAD
        case 0: _t->toAffichagePrincipal(); break;
        case 1: _t->affichagePrincipal(); break;
        case 2: _t->affichageCreeContact(); break;
        case 3: _t->affichageContact((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->creeContact((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
=======
        case 0: _t->affichagePrincipal(); break;
        case 1: _t->affichageCreeContact(); break;
        case 2: _t->creeContact((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
>>>>>>> d8656cc733c777f4b3202f8d9e8dc61c81894664
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::toAffichagePrincipal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void MainWindow::toAffichagePrincipal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
