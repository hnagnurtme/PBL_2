/****************************************************************************
** Meta object code from reading C++ file 'CustomerInterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../View/CustomerInterface.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomerInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
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
struct qt_meta_stringdata_CLASSCustomerInterfaceENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCustomerInterfaceENDCLASS = QtMocHelpers::stringData(
    "CustomerInterface",
    "showOverview",
    "",
    "showProducts",
    "filterProducts",
    "showCart",
    "showOrders",
    "showAccount",
    "change",
    "showInvoice",
    "payment",
    "checkout",
    "cartOrigin",
    "ordersOrigin",
    "clearCart",
    "onDeliveryDateChanged",
    "onPaymentMethodChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCustomerInterfaceENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    0,  107,    2, 0x08,    4 /* Private */,
       6,    0,  108,    2, 0x08,    5 /* Private */,
       7,    1,  109,    2, 0x08,    6 /* Private */,
       7,    0,  112,    2, 0x28,    8 /* Private | MethodCloned */,
       9,    0,  113,    2, 0x08,    9 /* Private */,
      10,    0,  114,    2, 0x08,   10 /* Private */,
      11,    0,  115,    2, 0x08,   11 /* Private */,
      12,    0,  116,    2, 0x08,   12 /* Private */,
      13,    0,  117,    2, 0x08,   13 /* Private */,
      14,    0,  118,    2, 0x08,   14 /* Private */,
      15,    0,  119,    2, 0x08,   15 /* Private */,
      16,    0,  120,    2, 0x08,   16 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
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

Q_CONSTINIT const QMetaObject CustomerInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSCustomerInterfaceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCustomerInterfaceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCustomerInterfaceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CustomerInterface, std::true_type>,
        // method 'showOverview'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showProducts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filterProducts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showCart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showOrders'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'showAccount'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showInvoice'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'payment'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cartOrigin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ordersOrigin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearCart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeliveryDateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPaymentMethodChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void CustomerInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomerInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showOverview(); break;
        case 1: _t->showProducts(); break;
        case 2: _t->filterProducts(); break;
        case 3: _t->showCart(); break;
        case 4: _t->showOrders(); break;
        case 5: _t->showAccount((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->showAccount(); break;
        case 7: _t->showInvoice(); break;
        case 8: _t->payment(); break;
        case 9: _t->checkout(); break;
        case 10: _t->cartOrigin(); break;
        case 11: _t->ordersOrigin(); break;
        case 12: _t->clearCart(); break;
        case 13: _t->onDeliveryDateChanged(); break;
        case 14: _t->onPaymentMethodChanged(); break;
        default: ;
        }
    }
}

const QMetaObject *CustomerInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCustomerInterfaceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CustomerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
