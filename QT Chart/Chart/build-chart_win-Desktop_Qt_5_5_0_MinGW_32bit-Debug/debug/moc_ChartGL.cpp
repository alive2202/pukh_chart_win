/****************************************************************************
** Meta object code from reading C++ file 'ChartGL.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../chart_win/ChartGL.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChartGL.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChartGL_t {
    QByteArrayData data[27];
    char stringdata0[243];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChartGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChartGL_t qt_meta_stringdata_ChartGL = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ChartGL"
QT_MOC_LITERAL(1, 8, 7), // "paintGL"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 12), // "initializeGL"
QT_MOC_LITERAL(4, 30, 8), // "resizeGL"
QT_MOC_LITERAL(5, 39, 6), // "nWidth"
QT_MOC_LITERAL(6, 46, 7), // "nHeight"
QT_MOC_LITERAL(7, 54, 10), // "ChangeNext"
QT_MOC_LITERAL(8, 65, 10), // "ChangePrev"
QT_MOC_LITERAL(9, 76, 11), // "ChangeFirst"
QT_MOC_LITERAL(10, 88, 10), // "ChangeLast"
QT_MOC_LITERAL(11, 99, 3), // "ico"
QT_MOC_LITERAL(12, 103, 5), // "point"
QT_MOC_LITERAL(13, 109, 4), // "line"
QT_MOC_LITERAL(14, 114, 6), // "square"
QT_MOC_LITERAL(15, 121, 9), // "pointSize"
QT_MOC_LITERAL(16, 131, 9), // "lineWidth"
QT_MOC_LITERAL(17, 141, 7), // "marginL"
QT_MOC_LITERAL(18, 149, 7), // "marginR"
QT_MOC_LITERAL(19, 157, 7), // "marginT"
QT_MOC_LITERAL(20, 165, 7), // "marginB"
QT_MOC_LITERAL(21, 173, 9), // "startMinX"
QT_MOC_LITERAL(22, 183, 9), // "startMinY"
QT_MOC_LITERAL(23, 193, 9), // "startMaxX"
QT_MOC_LITERAL(24, 203, 9), // "startMaxY"
QT_MOC_LITERAL(25, 213, 14), // "startNumXTicks"
QT_MOC_LITERAL(26, 228, 14) // "startNumYTicks"

    },
    "ChartGL\0paintGL\0\0initializeGL\0resizeGL\0"
    "nWidth\0nHeight\0ChangeNext\0ChangePrev\0"
    "ChangeFirst\0ChangeLast\0ico\0point\0line\0"
    "square\0pointSize\0lineWidth\0marginL\0"
    "marginR\0marginT\0marginB\0startMinX\0"
    "startMinY\0startMaxX\0startMaxY\0"
    "startNumXTicks\0startNumYTicks"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChartGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
      16,   60, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    2,   51,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      11, QMetaType::Bool, 0x00095003,
      12, QMetaType::Bool, 0x00095003,
      13, QMetaType::Bool, 0x00095003,
      14, QMetaType::Bool, 0x00095003,
      15, QMetaType::Int, 0x00095003,
      16, QMetaType::Int, 0x00095003,
      17, QMetaType::Int, 0x00095003,
      18, QMetaType::Int, 0x00095003,
      19, QMetaType::Int, 0x00095003,
      20, QMetaType::Int, 0x00095003,
      21, QMetaType::Int, 0x00095003,
      22, QMetaType::Int, 0x00095003,
      23, QMetaType::Int, 0x00095003,
      24, QMetaType::Int, 0x00095003,
      25, QMetaType::Int, 0x00095003,
      26, QMetaType::Int, 0x00095003,

       0        // eod
};

void ChartGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChartGL *_t = static_cast<ChartGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->paintGL(); break;
        case 1: _t->initializeGL(); break;
        case 2: _t->resizeGL((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->ChangeNext(); break;
        case 4: _t->ChangePrev(); break;
        case 5: _t->ChangeFirst(); break;
        case 6: _t->ChangeLast(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ChartGL *_t = static_cast<ChartGL *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->GetICO(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->GetPoint(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->GetLine(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->GetSquare(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->GetPointSize(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->GetLineWidth(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->GetMarginL(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->GetMarginR(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->GetMarginT(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->GetMarginB(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->GetStartMinX(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->GetStartMinY(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->GetStartMaxX(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->GetStartMaxY(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->GetStartNumXTicks(); break;
        case 15: *reinterpret_cast< int*>(_v) = _t->GetStartNumYTicks(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ChartGL *_t = static_cast<ChartGL *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->SetICO(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->SetPoint(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->SetLine(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->SetSquare(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->SetPointSize(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->SetLineWidth(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->SetMarginL(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->SetMarginR(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->SetMarginT(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->SetMarginB(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->SetStartMinX(*reinterpret_cast< int*>(_v)); break;
        case 11: _t->SetStartMinY(*reinterpret_cast< int*>(_v)); break;
        case 12: _t->SetStartMaxX(*reinterpret_cast< int*>(_v)); break;
        case 13: _t->SetStartMaxY(*reinterpret_cast< int*>(_v)); break;
        case 14: _t->SetStartNumXTicks(*reinterpret_cast< int*>(_v)); break;
        case 15: _t->SetStartNumYTicks(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ChartGL::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ChartGL.data,
      qt_meta_data_ChartGL,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChartGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartGL::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChartGL.stringdata0))
        return static_cast<void*>(const_cast< ChartGL*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ChartGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 16;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 16;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
