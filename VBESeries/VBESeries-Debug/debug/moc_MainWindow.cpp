/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[100];
    char stringdata0[1087];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 17), // "SignalStartThread"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 17), // "SignalCloseThread"
QT_MOC_LITERAL(48, 21), // "SignalStartBurnThread"
QT_MOC_LITERAL(70, 21), // "SignalCloseBurnThread"
QT_MOC_LITERAL(92, 28), // "SignalStartAutoRefreshThread"
QT_MOC_LITERAL(121, 28), // "SignalCloseAutoRefreshThread"
QT_MOC_LITERAL(150, 27), // "SignalStartSendXModemThread"
QT_MOC_LITERAL(178, 27), // "SignalCloseSendXModemThread"
QT_MOC_LITERAL(206, 15), // "SlotReceiveData"
QT_MOC_LITERAL(222, 7), // "revData"
QT_MOC_LITERAL(230, 21), // "slotOpenSerialClicked"
QT_MOC_LITERAL(252, 8), // "QAction*"
QT_MOC_LITERAL(261, 6), // "action"
QT_MOC_LITERAL(268, 22), // "slotCloseSerialClicked"
QT_MOC_LITERAL(291, 31), // "slotBorderCardSelectMenuClicked"
QT_MOC_LITERAL(323, 25), // "slotModeSwitchMenuClicked"
QT_MOC_LITERAL(349, 27), // "slotClearReceiveDataClicked"
QT_MOC_LITERAL(377, 19), // "slotSendDataClicked"
QT_MOC_LITERAL(397, 21), // "slotSelectPathClicked"
QT_MOC_LITERAL(419, 21), // "slotGetVersionClicked"
QT_MOC_LITERAL(441, 26), // "slotReceiveDataTypeChanged"
QT_MOC_LITERAL(468, 23), // "slotSendDataTypeChanged"
QT_MOC_LITERAL(492, 26), // "slotTextEditReceiveChanged"
QT_MOC_LITERAL(519, 22), // "slotBtnMdioReadClicked"
QT_MOC_LITERAL(542, 23), // "slotBtnMdioWriteClicked"
QT_MOC_LITERAL(566, 22), // "slotBtnFpgaReadClicked"
QT_MOC_LITERAL(589, 23), // "slotBtnFpgaWriteClicked"
QT_MOC_LITERAL(613, 18), // "slotBtnBurnClicked"
QT_MOC_LITERAL(632, 21), // "slotBurnBtnTextUpdate"
QT_MOC_LITERAL(654, 5), // "value"
QT_MOC_LITERAL(660, 20), // "slotBtnSetT1AClicked"
QT_MOC_LITERAL(681, 20), // "slotBtnSetT1BClicked"
QT_MOC_LITERAL(702, 22), // "slotBtnSetRJ45AClicked"
QT_MOC_LITERAL(725, 22), // "slotBtnSetRJ45BClicked"
QT_MOC_LITERAL(748, 25), // "slotBtnStatusFreshClicked"
QT_MOC_LITERAL(774, 25), // "slotAutoRefreshConfigData"
QT_MOC_LITERAL(800, 15), // "slotDebugWindow"
QT_MOC_LITERAL(816, 19), // "slotDebugDialogShow"
QT_MOC_LITERAL(836, 26), // "slotSynConfigActionClicked"
QT_MOC_LITERAL(863, 26), // "slotDataResetActionClicked"
QT_MOC_LITERAL(890, 27), // "slotSendXmodemActionClicked"
QT_MOC_LITERAL(918, 17), // "slotSendXModemEnd"
QT_MOC_LITERAL(936, 27), // "slotResetBoardActionClicked"
QT_MOC_LITERAL(964, 27), // "slotRBtnT1AAnegGroupChanged"
QT_MOC_LITERAL(992, 6), // "status"
QT_MOC_LITERAL(999, 27), // "slotRBtnT1BAnegGroupChanged"
QT_MOC_LITERAL(1027, 29), // "slotRBtnRJ45AAnegGroupChanged"
QT_MOC_LITERAL(1057, 29) // "slotRBtnRJ45BAnegGroupChanged"

    },
    "MainWindow\0SignalStartThread\0\0"
    "SignalCloseThread\0SignalStartBurnThread\0"
    "SignalCloseBurnThread\0"
    "SignalStartAutoRefreshThread\0"
    "SignalCloseAutoRefreshThread\0"
    "SignalStartSendXModemThread\0"
    "SignalCloseSendXModemThread\0SlotReceiveData\0"
    "revData\0slotOpenSerialClicked\0QAction*\0"
    "action\0slotCloseSerialClicked\0"
    "slotBorderCardSelectMenuClicked\0"
    "slotModeSwitchMenuClicked\0"
    "slotClearReceiveDataClicked\0"
    "slotSendDataClicked\0slotSelectPathClicked\0"
    "slotGetVersionClicked\0slotReceiveDataTypeChanged\0"
    "slotSendDataTypeChanged\0"
    "slotTextEditReceiveChanged\0"
    "slotBtnMdioReadClicked\0slotBtnMdioWriteClicked\0"
    "slotBtnFpgaReadClicked\0slotBtnFpgaWriteClicked\0"
    "slotBtnBurnClicked\0slotBurnBtnTextUpdate\0"
    "value\0slotBtnSetT1AClicked\0"
    "slotBtnSetT1BClicked\0slotBtnSetRJ45AClicked\0"
    "slotBtnSetRJ45BClicked\0slotBtnStatusFreshClicked\0"
    "slotAutoRefreshConfigData\0slotDebugWindow\0"
    "slotDebugDialogShow\0slotSynConfigActionClicked\0"
    "slotDataResetActionClicked\0"
    "slotSendXmodemActionClicked\0"
    "slotSendXModemEnd\0slotResetBoardActionClicked\0"
    "slotRBtnT1AAnegGroupChanged\0status\0"
    "slotRBtnT1BAnegGroupChanged\0"
    "slotRBtnRJ45AAnegGroupChanged\0"
    "slotRBtnRJ45BAnegGroupChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  272,    2, 0x06,    1 /* Public */,
       3,    0,  273,    2, 0x06,    2 /* Public */,
       4,    0,  274,    2, 0x06,    3 /* Public */,
       5,    0,  275,    2, 0x06,    4 /* Public */,
       6,    0,  276,    2, 0x06,    5 /* Public */,
       7,    0,  277,    2, 0x06,    6 /* Public */,
       8,    0,  278,    2, 0x06,    7 /* Public */,
       9,    0,  279,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  280,    2, 0x08,    9 /* Private */,
      12,    1,  283,    2, 0x08,   11 /* Private */,
      15,    1,  286,    2, 0x08,   13 /* Private */,
      16,    1,  289,    2, 0x08,   15 /* Private */,
      17,    1,  292,    2, 0x08,   17 /* Private */,
      18,    0,  295,    2, 0x08,   19 /* Private */,
      19,    0,  296,    2, 0x08,   20 /* Private */,
      20,    0,  297,    2, 0x08,   21 /* Private */,
      21,    0,  298,    2, 0x08,   22 /* Private */,
      22,    0,  299,    2, 0x08,   23 /* Private */,
      23,    0,  300,    2, 0x08,   24 /* Private */,
      24,    0,  301,    2, 0x08,   25 /* Private */,
      25,    0,  302,    2, 0x08,   26 /* Private */,
      26,    0,  303,    2, 0x08,   27 /* Private */,
      27,    0,  304,    2, 0x08,   28 /* Private */,
      28,    0,  305,    2, 0x08,   29 /* Private */,
      29,    0,  306,    2, 0x08,   30 /* Private */,
      30,    1,  307,    2, 0x08,   31 /* Private */,
      32,    0,  310,    2, 0x08,   33 /* Private */,
      33,    0,  311,    2, 0x08,   34 /* Private */,
      34,    0,  312,    2, 0x08,   35 /* Private */,
      35,    0,  313,    2, 0x08,   36 /* Private */,
      36,    0,  314,    2, 0x08,   37 /* Private */,
      37,    0,  315,    2, 0x08,   38 /* Private */,
      38,    0,  316,    2, 0x08,   39 /* Private */,
      39,    0,  317,    2, 0x08,   40 /* Private */,
      40,    0,  318,    2, 0x08,   41 /* Private */,
      41,    0,  319,    2, 0x08,   42 /* Private */,
      42,    0,  320,    2, 0x08,   43 /* Private */,
      43,    0,  321,    2, 0x08,   44 /* Private */,
      44,    0,  322,    2, 0x08,   45 /* Private */,
      45,    1,  323,    2, 0x08,   46 /* Private */,
      47,    1,  326,    2, 0x08,   48 /* Private */,
      48,    1,  329,    2, 0x08,   50 /* Private */,
      49,    1,  332,    2, 0x08,   52 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   46,
    QMetaType::Void, QMetaType::Bool,   46,
    QMetaType::Void, QMetaType::Bool,   46,
    QMetaType::Void, QMetaType::Bool,   46,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SignalStartThread(); break;
        case 1: _t->SignalCloseThread(); break;
        case 2: _t->SignalStartBurnThread(); break;
        case 3: _t->SignalCloseBurnThread(); break;
        case 4: _t->SignalStartAutoRefreshThread(); break;
        case 5: _t->SignalCloseAutoRefreshThread(); break;
        case 6: _t->SignalStartSendXModemThread(); break;
        case 7: _t->SignalCloseSendXModemThread(); break;
        case 8: _t->SlotReceiveData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->slotOpenSerialClicked((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 10: _t->slotCloseSerialClicked((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 11: _t->slotBorderCardSelectMenuClicked((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 12: _t->slotModeSwitchMenuClicked((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 13: _t->slotClearReceiveDataClicked(); break;
        case 14: _t->slotSendDataClicked(); break;
        case 15: _t->slotSelectPathClicked(); break;
        case 16: _t->slotGetVersionClicked(); break;
        case 17: _t->slotReceiveDataTypeChanged(); break;
        case 18: _t->slotSendDataTypeChanged(); break;
        case 19: _t->slotTextEditReceiveChanged(); break;
        case 20: _t->slotBtnMdioReadClicked(); break;
        case 21: _t->slotBtnMdioWriteClicked(); break;
        case 22: _t->slotBtnFpgaReadClicked(); break;
        case 23: _t->slotBtnFpgaWriteClicked(); break;
        case 24: _t->slotBtnBurnClicked(); break;
        case 25: _t->slotBurnBtnTextUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->slotBtnSetT1AClicked(); break;
        case 27: _t->slotBtnSetT1BClicked(); break;
        case 28: _t->slotBtnSetRJ45AClicked(); break;
        case 29: _t->slotBtnSetRJ45BClicked(); break;
        case 30: _t->slotBtnStatusFreshClicked(); break;
        case 31: _t->slotAutoRefreshConfigData(); break;
        case 32: _t->slotDebugWindow(); break;
        case 33: _t->slotDebugDialogShow(); break;
        case 34: _t->slotSynConfigActionClicked(); break;
        case 35: _t->slotDataResetActionClicked(); break;
        case 36: _t->slotSendXmodemActionClicked(); break;
        case 37: _t->slotSendXModemEnd(); break;
        case 38: _t->slotResetBoardActionClicked(); break;
        case 39: _t->slotRBtnT1AAnegGroupChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 40: _t->slotRBtnT1BAnegGroupChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->slotRBtnRJ45AAnegGroupChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 42: _t->slotRBtnRJ45BAnegGroupChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalStartThread)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalCloseThread)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalStartBurnThread)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalCloseBurnThread)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalStartAutoRefreshThread)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalCloseAutoRefreshThread)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalStartSendXModemThread)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SignalCloseSendXModemThread)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
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
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::SignalStartThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::SignalCloseThread()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::SignalStartBurnThread()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::SignalCloseBurnThread()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::SignalStartAutoRefreshThread()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::SignalCloseAutoRefreshThread()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::SignalStartSendXModemThread()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::SignalCloseSendXModemThread()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE