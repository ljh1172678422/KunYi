QT       += core gui charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 设置应用程序信息
#RC_ICONS = ./icons/favicon.ico
#QMAKE_TARGET_COMPANY = "昆易（上海）电子科技有限公司" #公司名称
#QMAKE_TARGET_PRODUCT = "VET2544测试套件" #产品名称
#QMAKE_TARGET_DESCRIPTION = "Copyright 2023 The KUNYI. All rights reserved." #产品解释
#QMAKE_TARGET_COPYRIGHT = "" #版权
#RC_LANG = 0x0004 #语言，默认中文

RC_FILE = res/AppResource.rc

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}# 设置应用程序生成路径

INCLUDEPATH += widget/ utils/

SOURCES += \
    FormTestResult.cpp \
    main.cpp \
    MainWindow.cpp \
    utils/PDFHelper.cpp \
    utils/SerialPortThread.cpp \
    utils/TimerThread.cpp \
    widget/MenuItem.cpp \
    widget/MultiComboBox.cpp \
    widget/MyTableWidget.cpp

HEADERS += \
    FormTestResult.h \
    MainWindow.h \
    utils/DataTypeDef.h \
    utils/PDFHelper.h \
    utils/SerialPortThread.h \
    utils/ServiceException.h \
    utils/TimerThread.h \
    widget/MenuItem.h \
    widget/MultiComboBox.h \
    widget/MyTableWidget.h

FORMS += \
    FormTestResult.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
