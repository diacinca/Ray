/****************************************************************************
** Meta object code from reading C++ file 'chartrenderer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/chartrenderer.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartrenderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSChartRendererENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSChartRendererENDCLASS = QtMocHelpers::stringData(
    "ChartRenderer",
    "dataPointsChanged",
    "",
    "currentRpmChanged",
    "currentFuelFlowChanged",
    "ecoModeChanged",
    "minRpmChanged",
    "maxRpmChanged",
    "minFuelFlowChanged",
    "maxFuelFlowChanged",
    "dataPoints",
    "QVariantList",
    "currentRpm",
    "currentFuelFlow",
    "isEcoMode",
    "minRpm",
    "maxRpm",
    "minFuelFlow",
    "maxFuelFlow"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChartRendererENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       8,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    9 /* Public */,
       3,    0,   63,    2, 0x06,   10 /* Public */,
       4,    0,   64,    2, 0x06,   11 /* Public */,
       5,    0,   65,    2, 0x06,   12 /* Public */,
       6,    0,   66,    2, 0x06,   13 /* Public */,
       7,    0,   67,    2, 0x06,   14 /* Public */,
       8,    0,   68,    2, 0x06,   15 /* Public */,
       9,    0,   69,    2, 0x06,   16 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags, notifyId, revision
      10, 0x80000000 | 11, 0x0001510b, uint(0), 0,
      12, QMetaType::Double, 0x00015103, uint(1), 0,
      13, QMetaType::Double, 0x00015103, uint(2), 0,
      14, QMetaType::Bool, 0x00015103, uint(3), 0,
      15, QMetaType::Double, 0x00015103, uint(4), 0,
      16, QMetaType::Double, 0x00015103, uint(5), 0,
      17, QMetaType::Double, 0x00015103, uint(6), 0,
      18, QMetaType::Double, 0x00015103, uint(7), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartRenderer::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSChartRendererENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChartRendererENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChartRendererENDCLASS_t,
        // property 'dataPoints'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'currentRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'currentFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'isEcoMode'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'minRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'maxRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'minFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'maxFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartRenderer, std::true_type>,
        // method 'dataPointsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentRpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentFuelFlowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ecoModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'minRpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'maxRpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'minFuelFlowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'maxFuelFlowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ChartRenderer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChartRenderer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataPointsChanged(); break;
        case 1: _t->currentRpmChanged(); break;
        case 2: _t->currentFuelFlowChanged(); break;
        case 3: _t->ecoModeChanged(); break;
        case 4: _t->minRpmChanged(); break;
        case 5: _t->maxRpmChanged(); break;
        case 6: _t->minFuelFlowChanged(); break;
        case 7: _t->maxFuelFlowChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::dataPointsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::currentRpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::currentFuelFlowChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::ecoModeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::minRpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::maxRpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::minFuelFlowChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChartRenderer::*)();
            if (_t _q_method = &ChartRenderer::maxFuelFlowChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ChartRenderer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantList*>(_v) = _t->dataPoints(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->currentRpm(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->currentFuelFlow(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isEcoMode(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->minRpm(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->maxRpm(); break;
        case 6: *reinterpret_cast< double*>(_v) = _t->minFuelFlow(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->maxFuelFlow(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ChartRenderer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDataPoints(*reinterpret_cast< QVariantList*>(_v)); break;
        case 1: _t->setCurrentRpm(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setCurrentFuelFlow(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setIsEcoMode(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setMinRpm(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setMaxRpm(*reinterpret_cast< double*>(_v)); break;
        case 6: _t->setMinFuelFlow(*reinterpret_cast< double*>(_v)); break;
        case 7: _t->setMaxFuelFlow(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *ChartRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChartRendererENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int ChartRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ChartRenderer::dataPointsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChartRenderer::currentRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ChartRenderer::currentFuelFlowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ChartRenderer::ecoModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ChartRenderer::minRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ChartRenderer::maxRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ChartRenderer::minFuelFlowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ChartRenderer::maxFuelFlowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
