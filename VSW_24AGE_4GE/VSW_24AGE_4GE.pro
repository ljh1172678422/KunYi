QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE = res/AppResource.rc

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}

TARGET = KYGUI

INCLUDEPATH += Form/ utils/ Widget/

SOURCES += \
    Form/FormNetConfig.cpp \
    Form/FormSerialPortConfig.cpp \
    VSW_24AGE_4GE.cpp \
    Widget/CustomToolButton.cpp \
    Widget/MirrorPortTableWidget.cpp \
    Widget/MyTableWidget.cpp \
    main.cpp \
    MainWindow.cpp \
    utils/AutoGetChipDataThread.cpp \
    utils/OnlineTool.cpp \
    utils/SerialPortThread.cpp \
    utils/TcpClientThread.cpp \
    utils/TcpServerThread.cpp \
    utils/UdpThread.cpp

HEADERS += \
    Form/FormNetConfig.h \
    Form/FormSerialPortConfig.h \
    MainWindow.h \
    VSW_24AGE_4GE.h \
    Widget/CustomToolButton.h \
    Widget/MirrorPortTableWidget.h \
    Widget/MyTableWidget.h \
    utils/AutoGetChipDataThread.h \
    utils/DataTypeDef.h \
    utils/OnlineTool.h \
    utils/SerialPortThread.h \
    utils/ServiceException.h \
    utils/TcpClientThread.h \
    utils/TcpServerThread.h \
    utils/UdpThread.h

FORMS += \
    Form/FormNetConfig.ui \
    Form/FormSerialPortConfig.ui \
    MainWindow.ui \
    VSW_24AGE_4GE.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
