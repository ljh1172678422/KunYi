QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = favicon.ico
QMAKE_TARGET_COMPANY = "昆易（上海）电子科技有限公司" //公司名称
QMAKE_TARGET_PRODUCT = "车载以太网转换控制软" //产品名称
QMAKE_TARGET_DESCRIPTION = "Copyright 2023 The KUNYI. All rights reserved." //产品解释
QMAKE_TARGET_COPYRIGHT = "" //版权
RC_LANG = 0x0004 //语言，默认中文

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../bin/debug
} else {
    DESTDIR = $$PWD/../bin/release
}

SOURCES += \
    AutoRefreshThread.cpp \
    BurnWritThread.cpp \
    DebugPassword.cpp \
    MySerialPort.cpp \
    XModemThread.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AutoRefreshThread.h \
    BurnWritThread.h \
    DebugPassword.h \
    MySerialPort.h \
    MainWindow.h \
    XModemThread.h

FORMS += \
    DebugPassword.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
