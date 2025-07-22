/****************************************************************************
** Meta object code from reading C++ file 'chartdatamodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/chartdatamodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartdatamodel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSChartDataModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSChartDataModelENDCLASS = QtMocHelpers::stringData(
    "ChartDataModel",
    "dataChanged",
    "",
    "currentRpmChanged",
    "currentFuelFlowChanged",
    "ecoModeChanged",
    "generateSampleData",
    "getDataPoints",
    "QVariantList",
    "getCurrentFuelFlowAtRpm",
    "rpm",
    "minRpm",
    "maxRpm",
    "minFuelFlow",
    "maxFuelFlow",
    "currentRpm",
    "currentFuelFlow",
    "isEcoMode"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChartDataModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   65, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    8 /* Public */,
       3,    0,   57,    2, 0x06,    9 /* Public */,
       4,    0,   58,    2, 0x06,   10 /* Public */,
       5,    0,   59,    2, 0x06,   11 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   60,    2, 0x02,   12 /* Public */,
       7,    0,   61,    2, 0x102,   13 /* Public | MethodIsConst  */,
       9,    1,   62,    2, 0x102,   14 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    0x80000000 | 8,
    QMetaType::Double, QMetaType::Double,   10,

 // properties: name, type, flags, notifyId, revision
      11, QMetaType::Double, 0x00015001, uint(0), 0,
      12, QMetaType::Double, 0x00015001, uint(0), 0,
      13, QMetaType::Double, 0x00015001, uint(0), 0,
      14, QMetaType::Double, 0x00015001, uint(0), 0,
      15, QMetaType::Double, 0x00015103, uint(1), 0,
      16, QMetaType::Double, 0x00015001, uint(2), 0,
      17, QMetaType::Bool, 0x00015001, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChartDataModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSChartDataModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChartDataModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChartDataModelENDCLASS_t,
        // property 'minRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'maxRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'minFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'maxFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'currentRpm'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'currentFuelFlow'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'isEcoMode'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChartDataModel, std::true_type>,
        // method 'dataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentRpmChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'currentFuelFlowChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ecoModeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'generateSampleData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getDataPoints'
        QtPrivate::TypeAndForceComplete<QVariantList, std::false_type>,
        // method 'getCurrentFuelFlowAtRpm'
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>
    >,
    nullptr
} };

void ChartDataModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChartDataModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->currentRpmChanged(); break;
        case 2: _t->currentFuelFlowChanged(); break;
        case 3: _t->ecoModeChanged(); break;
        case 4: _t->generateSampleData(); break;
        case 5: { QVariantList _r = _t->getDataPoints();
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = std::move(_r); }  break;
        case 6: { double _r = _t->getCurrentFuelFlowAtRpm((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChartDataModel::*)();
            if (_t _q_method = &ChartDataModel::dataChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChartDataModel::*)();
            if (_t _q_method = &ChartDataModel::currentRpmChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChartDataModel::*)();
            if (_t _q_method = &ChartDataModel::currentFuelFlowChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChartDataModel::*)();
            if (_t _q_method = &ChartDataModel::ecoModeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ChartDataModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->minRpm(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->maxRpm(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->minFuelFlow(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->maxFuelFlow(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->currentRpm(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->currentFuelFlow(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->isEcoMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ChartDataModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setCurrentRpm(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *ChartDataModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartDataModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChartDataModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int ChartDataModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ChartDataModel::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChartDataModel::currentRpmChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ChartDataModel::currentFuelFlowChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ChartDataModel::ecoModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
