/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionVBE1200;
    QAction *actionVBE1000;
    QAction *action_Bypass;
    QAction *action_Mirror;
    QWidget *centralwidget;
    QGridLayout *gridLayout_18;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxSerialReceive;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *rBtnReceiveASCII;
    QRadioButton *rBtnReceiveHEX;
    QSpacerItem *horizontalSpacer;
    QPushButton *BtnClearReceiveData;
    QTextEdit *textEditReceiveData;
    QGroupBox *groupBoxSerialSend;
    QGridLayout *gridLayout_8;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *textEditSendData;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *rBtnSendDataASCII;
    QRadioButton *rBtnSendDataHex;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *BtnSendData;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxMdioInterface;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *lineEditPhyAddr;
    QLineEdit *lineEditDevAddr;
    QLineEdit *lineEditRegAddr;
    QLineEdit *lineEditMdioValue;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *BtnMdioRead;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *BtnMdioWrite;
    QGroupBox *groupBoxFpgaInterface;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEditFpgaAddr;
    QLabel *label_8;
    QLineEdit *lineEditFpgaValue;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *BtnFpgaRead;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *BtnFpgaWrite;
    QGroupBox *groupBoxFirmwareWrite;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_8;
    QLabel *labelCurFirmwareVersion;
    QLabel *labelCurFpgaVersion;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *BtnGetVersion;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QLineEdit *lineEditPath;
    QToolButton *tBtnSelectPath;
    QHBoxLayout *horizontalLayout_12;
    QRadioButton *rBtnMcu;
    QRadioButton *rBtnFpga;
    QPushButton *BtnBurn;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_RJ45_1;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_14;
    QRadioButton *rBtnGeSpeedRJ45_1;
    QRadioButton *rBtnFullDuplexRJ45_1;
    QRadioButton *rBtnAnegDisableRJ45_1;
    QRadioButton *rBtnFeSpeedRJ45_1;
    QSpacerItem *horizontalSpacer_8;
    QRadioButton *rBtnHalfDuplexRJ45_1;
    QRadioButton *rBtnAnegEnableRJ45_1;
    QPushButton *BtnSetRJ45_1;
    QGroupBox *groupBox_RJ45_2;
    QGridLayout *gridLayout_17;
    QGridLayout *gridLayout_16;
    QRadioButton *rBtnGeSpeedRJ45_2;
    QRadioButton *rBtnAnegEnableRJ45_2;
    QRadioButton *rBtnHalfDuplexRJ45_2;
    QRadioButton *rBtnFullDuplexRJ45_2;
    QRadioButton *rBtnFeSpeedRJ45_2;
    QRadioButton *rBtnAnegDisableRJ45_2;
    QPushButton *BtnSetRJ45_2;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_T1_2;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_11;
    QRadioButton *rBtnMasterModeT1_2;
    QRadioButton *rBtnAnegEnableT1_2;
    QRadioButton *rBtnAnegDisableT1_2;
    QRadioButton *rBtnSlaverModeT1_2;
    QRadioButton *rBtnFeSpeedT1_2;
    QRadioButton *rBtnGeSpeedT1_2;
    QPushButton *BtnSetT1_2;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_T1_1;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QRadioButton *rBtnAnegEnableT1_1;
    QRadioButton *rBtnMasterModeT1_1;
    QRadioButton *rBtnGeSpeedT1_1;
    QRadioButton *rBtnFeSpeedT1_1;
    QRadioButton *rBtnAnegDisableT1_1;
    QRadioButton *rBtnSlaverModeT1_1;
    QPushButton *BtnSetT1_1;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox_Status;
    QGridLayout *gridLayout_19;
    QGridLayout *gridLayout_13;
    QLabel *T1ALinkSpeedLabel;
    QLabel *RJ45AAutoNegoLabel;
    QLabel *RJ45ALinkStatusLabel;
    QLabel *T1BAutoNegoLabel;
    QPushButton *BtnStatusFresh;
    QLabel *T1AAutoNegoLabel;
    QLabel *RJ45AForceModeLabel;
    QLabel *label_RJ45_A;
    QLabel *label_9;
    QLabel *T1AForceModeLabel;
    QLabel *RJ45ALinkSpeedLabel;
    QLabel *label_12;
    QLabel *label_T1_A;
    QLabel *T1BLinkSpeedLabel;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *T1ADuplexLabel;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *RJ45ADuplexTypeLabel;
    QLabel *T1BLinkStatusLabel;
    QLabel *RJ45AModeLabel;
    QLabel *label_RJ45_B;
    QLabel *T1ALinkStatusLabel;
    QLabel *T1AModeLabel;
    QLabel *label_T1_B;
    QLabel *T1BForceModeLabel;
    QLabel *T1BDuplexLabel;
    QLabel *T1BModeLabel;
    QLabel *RJ45BAutoNegoLabel;
    QLabel *RJ45BLinkStatusLabel;
    QLabel *RJ45BLinkSpeedLabel;
    QLabel *RJ45BForceModeLabel;
    QLabel *RJ45BDuplexTypeLabel;
    QLabel *RJ45BModeLabel;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QMenuBar *menubar;
    QMenu *SerialSelect;
    QMenu *OpenSerialMenu;
    QMenu *CloseSerialMenu;
    QMenu *BoardCardSelect;
    QMenu *ModeSwitch;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1237, 608);
        actionVBE1200 = new QAction(MainWindow);
        actionVBE1200->setObjectName(QString::fromUtf8("actionVBE1200"));
        actionVBE1200->setCheckable(true);
        actionVBE1200->setChecked(true);
        actionVBE1000 = new QAction(MainWindow);
        actionVBE1000->setObjectName(QString::fromUtf8("actionVBE1000"));
        actionVBE1000->setCheckable(true);
        action_Bypass = new QAction(MainWindow);
        action_Bypass->setObjectName(QString::fromUtf8("action_Bypass"));
        action_Bypass->setCheckable(true);
        action_Bypass->setChecked(true);
        action_Mirror = new QAction(MainWindow);
        action_Mirror->setObjectName(QString::fromUtf8("action_Mirror"));
        action_Mirror->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_18 = new QGridLayout(centralwidget);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxSerialReceive = new QGroupBox(centralwidget);
        groupBoxSerialReceive->setObjectName(QString::fromUtf8("groupBoxSerialReceive"));
        gridLayout_7 = new QGridLayout(groupBoxSerialReceive);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        rBtnReceiveASCII = new QRadioButton(groupBoxSerialReceive);
        rBtnReceiveASCII->setObjectName(QString::fromUtf8("rBtnReceiveASCII"));
        rBtnReceiveASCII->setChecked(false);

        horizontalLayout_4->addWidget(rBtnReceiveASCII);

        rBtnReceiveHEX = new QRadioButton(groupBoxSerialReceive);
        rBtnReceiveHEX->setObjectName(QString::fromUtf8("rBtnReceiveHEX"));
        rBtnReceiveHEX->setChecked(true);

        horizontalLayout_4->addWidget(rBtnReceiveHEX);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        BtnClearReceiveData = new QPushButton(groupBoxSerialReceive);
        BtnClearReceiveData->setObjectName(QString::fromUtf8("BtnClearReceiveData"));

        horizontalLayout_5->addWidget(BtnClearReceiveData);


        verticalLayout_4->addLayout(horizontalLayout_5);

        textEditReceiveData = new QTextEdit(groupBoxSerialReceive);
        textEditReceiveData->setObjectName(QString::fromUtf8("textEditReceiveData"));
        textEditReceiveData->setEnabled(true);

        verticalLayout_4->addWidget(textEditReceiveData);


        gridLayout_7->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxSerialReceive);

        groupBoxSerialSend = new QGroupBox(centralwidget);
        groupBoxSerialSend->setObjectName(QString::fromUtf8("groupBoxSerialSend"));
        gridLayout_8 = new QGridLayout(groupBoxSerialSend);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        textEditSendData = new QTextEdit(groupBoxSerialSend);
        textEditSendData->setObjectName(QString::fromUtf8("textEditSendData"));

        verticalLayout_5->addWidget(textEditSendData);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        rBtnSendDataASCII = new QRadioButton(groupBoxSerialSend);
        rBtnSendDataASCII->setObjectName(QString::fromUtf8("rBtnSendDataASCII"));
        rBtnSendDataASCII->setChecked(false);

        horizontalLayout_7->addWidget(rBtnSendDataASCII);

        rBtnSendDataHex = new QRadioButton(groupBoxSerialSend);
        rBtnSendDataHex->setObjectName(QString::fromUtf8("rBtnSendDataHex"));
        rBtnSendDataHex->setChecked(true);

        horizontalLayout_7->addWidget(rBtnSendDataHex);


        horizontalLayout_6->addLayout(horizontalLayout_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        BtnSendData = new QPushButton(groupBoxSerialSend);
        BtnSendData->setObjectName(QString::fromUtf8("BtnSendData"));

        horizontalLayout_6->addWidget(BtnSendData);


        verticalLayout_5->addLayout(horizontalLayout_6);


        gridLayout_8->addLayout(verticalLayout_5, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxSerialSend);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBoxMdioInterface = new QGroupBox(centralwidget);
        groupBoxMdioInterface->setObjectName(QString::fromUtf8("groupBoxMdioInterface"));
        gridLayout_6 = new QGridLayout(groupBoxMdioInterface);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBoxMdioInterface);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(groupBoxMdioInterface);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(groupBoxMdioInterface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        label_4 = new QLabel(groupBoxMdioInterface);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        lineEditPhyAddr = new QLineEdit(groupBoxMdioInterface);
        lineEditPhyAddr->setObjectName(QString::fromUtf8("lineEditPhyAddr"));

        gridLayout_2->addWidget(lineEditPhyAddr, 0, 1, 1, 1);

        lineEditDevAddr = new QLineEdit(groupBoxMdioInterface);
        lineEditDevAddr->setObjectName(QString::fromUtf8("lineEditDevAddr"));

        gridLayout_2->addWidget(lineEditDevAddr, 1, 1, 1, 1);

        lineEditRegAddr = new QLineEdit(groupBoxMdioInterface);
        lineEditRegAddr->setObjectName(QString::fromUtf8("lineEditRegAddr"));

        gridLayout_2->addWidget(lineEditRegAddr, 2, 1, 1, 1);

        lineEditMdioValue = new QLineEdit(groupBoxMdioInterface);
        lineEditMdioValue->setObjectName(QString::fromUtf8("lineEditMdioValue"));

        gridLayout_2->addWidget(lineEditMdioValue, 3, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        BtnMdioRead = new QPushButton(groupBoxMdioInterface);
        BtnMdioRead->setObjectName(QString::fromUtf8("BtnMdioRead"));

        horizontalLayout_8->addWidget(BtnMdioRead);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        BtnMdioWrite = new QPushButton(groupBoxMdioInterface);
        BtnMdioWrite->setObjectName(QString::fromUtf8("BtnMdioWrite"));

        horizontalLayout_8->addWidget(BtnMdioWrite);


        verticalLayout_6->addLayout(horizontalLayout_8);

        verticalLayout_6->setStretch(0, 1);

        gridLayout_6->addLayout(verticalLayout_6, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBoxMdioInterface);

        groupBoxFpgaInterface = new QGroupBox(centralwidget);
        groupBoxFpgaInterface->setObjectName(QString::fromUtf8("groupBoxFpgaInterface"));
        gridLayout_5 = new QGridLayout(groupBoxFpgaInterface);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lineEditFpgaAddr = new QLineEdit(groupBoxFpgaInterface);
        lineEditFpgaAddr->setObjectName(QString::fromUtf8("lineEditFpgaAddr"));

        gridLayout_3->addWidget(lineEditFpgaAddr, 0, 1, 1, 1);

        label_8 = new QLabel(groupBoxFpgaInterface);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        lineEditFpgaValue = new QLineEdit(groupBoxFpgaInterface);
        lineEditFpgaValue->setObjectName(QString::fromUtf8("lineEditFpgaValue"));

        gridLayout_3->addWidget(lineEditFpgaValue, 1, 1, 1, 1);

        label_5 = new QLabel(groupBoxFpgaInterface);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);


        verticalLayout_7->addLayout(gridLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        BtnFpgaRead = new QPushButton(groupBoxFpgaInterface);
        BtnFpgaRead->setObjectName(QString::fromUtf8("BtnFpgaRead"));

        horizontalLayout_9->addWidget(BtnFpgaRead);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);

        BtnFpgaWrite = new QPushButton(groupBoxFpgaInterface);
        BtnFpgaWrite->setObjectName(QString::fromUtf8("BtnFpgaWrite"));

        horizontalLayout_9->addWidget(BtnFpgaWrite);


        verticalLayout_7->addLayout(horizontalLayout_9);

        verticalLayout_7->setStretch(0, 1);

        gridLayout_5->addLayout(verticalLayout_7, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBoxFpgaInterface);

        groupBoxFirmwareWrite = new QGroupBox(centralwidget);
        groupBoxFirmwareWrite->setObjectName(QString::fromUtf8("groupBoxFirmwareWrite"));
        gridLayout_4 = new QGridLayout(groupBoxFirmwareWrite);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        labelCurFirmwareVersion = new QLabel(groupBoxFirmwareWrite);
        labelCurFirmwareVersion->setObjectName(QString::fromUtf8("labelCurFirmwareVersion"));

        verticalLayout_8->addWidget(labelCurFirmwareVersion);

        labelCurFpgaVersion = new QLabel(groupBoxFirmwareWrite);
        labelCurFpgaVersion->setObjectName(QString::fromUtf8("labelCurFpgaVersion"));

        verticalLayout_8->addWidget(labelCurFpgaVersion);


        horizontalLayout_10->addLayout(verticalLayout_8);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        BtnGetVersion = new QPushButton(groupBoxFirmwareWrite);
        BtnGetVersion->setObjectName(QString::fromUtf8("BtnGetVersion"));

        horizontalLayout_10->addWidget(BtnGetVersion);


        verticalLayout_9->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(groupBoxFirmwareWrite);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_11->addWidget(label_6);

        lineEditPath = new QLineEdit(groupBoxFirmwareWrite);
        lineEditPath->setObjectName(QString::fromUtf8("lineEditPath"));

        horizontalLayout_11->addWidget(lineEditPath);

        tBtnSelectPath = new QToolButton(groupBoxFirmwareWrite);
        tBtnSelectPath->setObjectName(QString::fromUtf8("tBtnSelectPath"));

        horizontalLayout_11->addWidget(tBtnSelectPath);


        verticalLayout_9->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        rBtnMcu = new QRadioButton(groupBoxFirmwareWrite);
        rBtnMcu->setObjectName(QString::fromUtf8("rBtnMcu"));
        rBtnMcu->setChecked(true);

        horizontalLayout_12->addWidget(rBtnMcu);

        rBtnFpga = new QRadioButton(groupBoxFirmwareWrite);
        rBtnFpga->setObjectName(QString::fromUtf8("rBtnFpga"));

        horizontalLayout_12->addWidget(rBtnFpga);

        BtnBurn = new QPushButton(groupBoxFirmwareWrite);
        BtnBurn->setObjectName(QString::fromUtf8("BtnBurn"));

        horizontalLayout_12->addWidget(BtnBurn);


        verticalLayout_9->addLayout(horizontalLayout_12);


        gridLayout_4->addLayout(verticalLayout_9, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBoxFirmwareWrite);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout_3->setStretch(3, 1);

        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_RJ45_1 = new QGroupBox(centralwidget);
        groupBox_RJ45_1->setObjectName(QString::fromUtf8("groupBox_RJ45_1"));
        gridLayout_15 = new QGridLayout(groupBox_RJ45_1);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        rBtnGeSpeedRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnGeSpeedRJ45_1->setObjectName(QString::fromUtf8("rBtnGeSpeedRJ45_1"));

        gridLayout_14->addWidget(rBtnGeSpeedRJ45_1, 1, 1, 1, 1);

        rBtnFullDuplexRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnFullDuplexRJ45_1->setObjectName(QString::fromUtf8("rBtnFullDuplexRJ45_1"));
        rBtnFullDuplexRJ45_1->setChecked(false);

        gridLayout_14->addWidget(rBtnFullDuplexRJ45_1, 2, 0, 1, 1);

        rBtnAnegDisableRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnAnegDisableRJ45_1->setObjectName(QString::fromUtf8("rBtnAnegDisableRJ45_1"));

        gridLayout_14->addWidget(rBtnAnegDisableRJ45_1, 0, 1, 1, 1);

        rBtnFeSpeedRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnFeSpeedRJ45_1->setObjectName(QString::fromUtf8("rBtnFeSpeedRJ45_1"));
        rBtnFeSpeedRJ45_1->setChecked(true);

        gridLayout_14->addWidget(rBtnFeSpeedRJ45_1, 1, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_8, 3, 1, 1, 1);

        rBtnHalfDuplexRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnHalfDuplexRJ45_1->setObjectName(QString::fromUtf8("rBtnHalfDuplexRJ45_1"));

        gridLayout_14->addWidget(rBtnHalfDuplexRJ45_1, 2, 1, 1, 1);

        rBtnAnegEnableRJ45_1 = new QRadioButton(groupBox_RJ45_1);
        rBtnAnegEnableRJ45_1->setObjectName(QString::fromUtf8("rBtnAnegEnableRJ45_1"));
        rBtnAnegEnableRJ45_1->setChecked(false);

        gridLayout_14->addWidget(rBtnAnegEnableRJ45_1, 0, 0, 1, 1);

        BtnSetRJ45_1 = new QPushButton(groupBox_RJ45_1);
        BtnSetRJ45_1->setObjectName(QString::fromUtf8("BtnSetRJ45_1"));

        gridLayout_14->addWidget(BtnSetRJ45_1, 3, 0, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_RJ45_1, 1, 0, 1, 1);

        groupBox_RJ45_2 = new QGroupBox(centralwidget);
        groupBox_RJ45_2->setObjectName(QString::fromUtf8("groupBox_RJ45_2"));
        gridLayout_17 = new QGridLayout(groupBox_RJ45_2);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        rBtnGeSpeedRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnGeSpeedRJ45_2->setObjectName(QString::fromUtf8("rBtnGeSpeedRJ45_2"));

        gridLayout_16->addWidget(rBtnGeSpeedRJ45_2, 1, 1, 1, 1);

        rBtnAnegEnableRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnAnegEnableRJ45_2->setObjectName(QString::fromUtf8("rBtnAnegEnableRJ45_2"));
        rBtnAnegEnableRJ45_2->setChecked(false);

        gridLayout_16->addWidget(rBtnAnegEnableRJ45_2, 0, 0, 1, 1);

        rBtnHalfDuplexRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnHalfDuplexRJ45_2->setObjectName(QString::fromUtf8("rBtnHalfDuplexRJ45_2"));

        gridLayout_16->addWidget(rBtnHalfDuplexRJ45_2, 2, 1, 1, 1);

        rBtnFullDuplexRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnFullDuplexRJ45_2->setObjectName(QString::fromUtf8("rBtnFullDuplexRJ45_2"));
        rBtnFullDuplexRJ45_2->setChecked(false);

        gridLayout_16->addWidget(rBtnFullDuplexRJ45_2, 2, 0, 1, 1);

        rBtnFeSpeedRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnFeSpeedRJ45_2->setObjectName(QString::fromUtf8("rBtnFeSpeedRJ45_2"));
        rBtnFeSpeedRJ45_2->setChecked(true);

        gridLayout_16->addWidget(rBtnFeSpeedRJ45_2, 1, 0, 1, 1);

        rBtnAnegDisableRJ45_2 = new QRadioButton(groupBox_RJ45_2);
        rBtnAnegDisableRJ45_2->setObjectName(QString::fromUtf8("rBtnAnegDisableRJ45_2"));

        gridLayout_16->addWidget(rBtnAnegDisableRJ45_2, 0, 1, 1, 1);

        BtnSetRJ45_2 = new QPushButton(groupBox_RJ45_2);
        BtnSetRJ45_2->setObjectName(QString::fromUtf8("BtnSetRJ45_2"));

        gridLayout_16->addWidget(BtnSetRJ45_2, 3, 0, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_9, 3, 1, 1, 1);


        gridLayout_17->addLayout(gridLayout_16, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_RJ45_2, 1, 1, 1, 1);

        groupBox_T1_2 = new QGroupBox(centralwidget);
        groupBox_T1_2->setObjectName(QString::fromUtf8("groupBox_T1_2"));
        gridLayout_12 = new QGridLayout(groupBox_T1_2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        rBtnMasterModeT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnMasterModeT1_2->setObjectName(QString::fromUtf8("rBtnMasterModeT1_2"));
        rBtnMasterModeT1_2->setChecked(false);

        gridLayout_11->addWidget(rBtnMasterModeT1_2, 2, 0, 1, 1);

        rBtnAnegEnableT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnAnegEnableT1_2->setObjectName(QString::fromUtf8("rBtnAnegEnableT1_2"));
        rBtnAnegEnableT1_2->setChecked(false);

        gridLayout_11->addWidget(rBtnAnegEnableT1_2, 0, 0, 1, 1);

        rBtnAnegDisableT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnAnegDisableT1_2->setObjectName(QString::fromUtf8("rBtnAnegDisableT1_2"));

        gridLayout_11->addWidget(rBtnAnegDisableT1_2, 0, 1, 1, 1);

        rBtnSlaverModeT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnSlaverModeT1_2->setObjectName(QString::fromUtf8("rBtnSlaverModeT1_2"));

        gridLayout_11->addWidget(rBtnSlaverModeT1_2, 2, 1, 1, 1);

        rBtnFeSpeedT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnFeSpeedT1_2->setObjectName(QString::fromUtf8("rBtnFeSpeedT1_2"));
        rBtnFeSpeedT1_2->setChecked(true);

        gridLayout_11->addWidget(rBtnFeSpeedT1_2, 1, 0, 1, 1);

        rBtnGeSpeedT1_2 = new QRadioButton(groupBox_T1_2);
        rBtnGeSpeedT1_2->setObjectName(QString::fromUtf8("rBtnGeSpeedT1_2"));

        gridLayout_11->addWidget(rBtnGeSpeedT1_2, 1, 1, 1, 1);

        BtnSetT1_2 = new QPushButton(groupBox_T1_2);
        BtnSetT1_2->setObjectName(QString::fromUtf8("BtnSetT1_2"));

        gridLayout_11->addWidget(BtnSetT1_2, 3, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_7, 3, 1, 1, 1);


        gridLayout_12->addLayout(gridLayout_11, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_T1_2, 0, 1, 1, 1);

        groupBox_T1_1 = new QGroupBox(centralwidget);
        groupBox_T1_1->setObjectName(QString::fromUtf8("groupBox_T1_1"));
        gridLayout_10 = new QGridLayout(groupBox_T1_1);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        rBtnAnegEnableT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnAnegEnableT1_1->setObjectName(QString::fromUtf8("rBtnAnegEnableT1_1"));
        rBtnAnegEnableT1_1->setChecked(false);

        gridLayout_9->addWidget(rBtnAnegEnableT1_1, 0, 0, 1, 1);

        rBtnMasterModeT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnMasterModeT1_1->setObjectName(QString::fromUtf8("rBtnMasterModeT1_1"));
        rBtnMasterModeT1_1->setChecked(false);

        gridLayout_9->addWidget(rBtnMasterModeT1_1, 2, 0, 1, 1);

        rBtnGeSpeedT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnGeSpeedT1_1->setObjectName(QString::fromUtf8("rBtnGeSpeedT1_1"));

        gridLayout_9->addWidget(rBtnGeSpeedT1_1, 1, 1, 1, 1);

        rBtnFeSpeedT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnFeSpeedT1_1->setObjectName(QString::fromUtf8("rBtnFeSpeedT1_1"));
        rBtnFeSpeedT1_1->setChecked(true);

        gridLayout_9->addWidget(rBtnFeSpeedT1_1, 1, 0, 1, 1);

        rBtnAnegDisableT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnAnegDisableT1_1->setObjectName(QString::fromUtf8("rBtnAnegDisableT1_1"));

        gridLayout_9->addWidget(rBtnAnegDisableT1_1, 0, 1, 1, 1);

        rBtnSlaverModeT1_1 = new QRadioButton(groupBox_T1_1);
        rBtnSlaverModeT1_1->setObjectName(QString::fromUtf8("rBtnSlaverModeT1_1"));

        gridLayout_9->addWidget(rBtnSlaverModeT1_1, 2, 1, 1, 1);

        BtnSetT1_1 = new QPushButton(groupBox_T1_1);
        BtnSetT1_1->setObjectName(QString::fromUtf8("BtnSetT1_1"));

        gridLayout_9->addWidget(BtnSetT1_1, 3, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_6, 3, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_T1_1, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        groupBox_Status = new QGroupBox(centralwidget);
        groupBox_Status->setObjectName(QString::fromUtf8("groupBox_Status"));
        gridLayout_19 = new QGridLayout(groupBox_Status);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        T1ALinkSpeedLabel = new QLabel(groupBox_Status);
        T1ALinkSpeedLabel->setObjectName(QString::fromUtf8("T1ALinkSpeedLabel"));
        T1ALinkSpeedLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1ALinkSpeedLabel, 3, 1, 1, 1);

        RJ45AAutoNegoLabel = new QLabel(groupBox_Status);
        RJ45AAutoNegoLabel->setObjectName(QString::fromUtf8("RJ45AAutoNegoLabel"));
        RJ45AAutoNegoLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45AAutoNegoLabel, 1, 2, 1, 1);

        RJ45ALinkStatusLabel = new QLabel(groupBox_Status);
        RJ45ALinkStatusLabel->setObjectName(QString::fromUtf8("RJ45ALinkStatusLabel"));
        RJ45ALinkStatusLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45ALinkStatusLabel, 2, 2, 1, 1);

        T1BAutoNegoLabel = new QLabel(groupBox_Status);
        T1BAutoNegoLabel->setObjectName(QString::fromUtf8("T1BAutoNegoLabel"));
        T1BAutoNegoLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BAutoNegoLabel, 1, 3, 1, 1);

        BtnStatusFresh = new QPushButton(groupBox_Status);
        BtnStatusFresh->setObjectName(QString::fromUtf8("BtnStatusFresh"));

        gridLayout_13->addWidget(BtnStatusFresh, 0, 0, 1, 1);

        T1AAutoNegoLabel = new QLabel(groupBox_Status);
        T1AAutoNegoLabel->setObjectName(QString::fromUtf8("T1AAutoNegoLabel"));
        T1AAutoNegoLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1AAutoNegoLabel, 1, 1, 1, 1);

        RJ45AForceModeLabel = new QLabel(groupBox_Status);
        RJ45AForceModeLabel->setObjectName(QString::fromUtf8("RJ45AForceModeLabel"));
        RJ45AForceModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45AForceModeLabel, 4, 2, 1, 1);

        label_RJ45_A = new QLabel(groupBox_Status);
        label_RJ45_A->setObjectName(QString::fromUtf8("label_RJ45_A"));
        label_RJ45_A->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_RJ45_A, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox_Status);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_9, 2, 0, 1, 1);

        T1AForceModeLabel = new QLabel(groupBox_Status);
        T1AForceModeLabel->setObjectName(QString::fromUtf8("T1AForceModeLabel"));
        T1AForceModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1AForceModeLabel, 4, 1, 1, 1);

        RJ45ALinkSpeedLabel = new QLabel(groupBox_Status);
        RJ45ALinkSpeedLabel->setObjectName(QString::fromUtf8("RJ45ALinkSpeedLabel"));
        RJ45ALinkSpeedLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45ALinkSpeedLabel, 3, 2, 1, 1);

        label_12 = new QLabel(groupBox_Status);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_12, 5, 0, 1, 1);

        label_T1_A = new QLabel(groupBox_Status);
        label_T1_A->setObjectName(QString::fromUtf8("label_T1_A"));
        label_T1_A->setStyleSheet(QString::fromUtf8(""));
        label_T1_A->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_T1_A, 0, 1, 1, 1);

        T1BLinkSpeedLabel = new QLabel(groupBox_Status);
        T1BLinkSpeedLabel->setObjectName(QString::fromUtf8("T1BLinkSpeedLabel"));
        T1BLinkSpeedLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BLinkSpeedLabel, 3, 3, 1, 1);

        label_11 = new QLabel(groupBox_Status);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_11, 4, 0, 1, 1);

        label_13 = new QLabel(groupBox_Status);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_13, 6, 0, 1, 1);

        T1ADuplexLabel = new QLabel(groupBox_Status);
        T1ADuplexLabel->setObjectName(QString::fromUtf8("T1ADuplexLabel"));
        T1ADuplexLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1ADuplexLabel, 5, 1, 1, 1);

        label_7 = new QLabel(groupBox_Status);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_7, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_Status);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_10, 3, 0, 1, 1);

        RJ45ADuplexTypeLabel = new QLabel(groupBox_Status);
        RJ45ADuplexTypeLabel->setObjectName(QString::fromUtf8("RJ45ADuplexTypeLabel"));
        RJ45ADuplexTypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45ADuplexTypeLabel, 5, 2, 1, 1);

        T1BLinkStatusLabel = new QLabel(groupBox_Status);
        T1BLinkStatusLabel->setObjectName(QString::fromUtf8("T1BLinkStatusLabel"));
        T1BLinkStatusLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BLinkStatusLabel, 2, 3, 1, 1);

        RJ45AModeLabel = new QLabel(groupBox_Status);
        RJ45AModeLabel->setObjectName(QString::fromUtf8("RJ45AModeLabel"));
        RJ45AModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45AModeLabel, 6, 2, 1, 1);

        label_RJ45_B = new QLabel(groupBox_Status);
        label_RJ45_B->setObjectName(QString::fromUtf8("label_RJ45_B"));
        label_RJ45_B->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_RJ45_B, 0, 4, 1, 1);

        T1ALinkStatusLabel = new QLabel(groupBox_Status);
        T1ALinkStatusLabel->setObjectName(QString::fromUtf8("T1ALinkStatusLabel"));
        T1ALinkStatusLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1ALinkStatusLabel, 2, 1, 1, 1);

        T1AModeLabel = new QLabel(groupBox_Status);
        T1AModeLabel->setObjectName(QString::fromUtf8("T1AModeLabel"));
        T1AModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1AModeLabel, 6, 1, 1, 1);

        label_T1_B = new QLabel(groupBox_Status);
        label_T1_B->setObjectName(QString::fromUtf8("label_T1_B"));
        label_T1_B->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(label_T1_B, 0, 3, 1, 1);

        T1BForceModeLabel = new QLabel(groupBox_Status);
        T1BForceModeLabel->setObjectName(QString::fromUtf8("T1BForceModeLabel"));
        T1BForceModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BForceModeLabel, 4, 3, 1, 1);

        T1BDuplexLabel = new QLabel(groupBox_Status);
        T1BDuplexLabel->setObjectName(QString::fromUtf8("T1BDuplexLabel"));
        T1BDuplexLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BDuplexLabel, 5, 3, 1, 1);

        T1BModeLabel = new QLabel(groupBox_Status);
        T1BModeLabel->setObjectName(QString::fromUtf8("T1BModeLabel"));
        T1BModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(T1BModeLabel, 6, 3, 1, 1);

        RJ45BAutoNegoLabel = new QLabel(groupBox_Status);
        RJ45BAutoNegoLabel->setObjectName(QString::fromUtf8("RJ45BAutoNegoLabel"));
        RJ45BAutoNegoLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BAutoNegoLabel, 1, 4, 1, 1);

        RJ45BLinkStatusLabel = new QLabel(groupBox_Status);
        RJ45BLinkStatusLabel->setObjectName(QString::fromUtf8("RJ45BLinkStatusLabel"));
        RJ45BLinkStatusLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BLinkStatusLabel, 2, 4, 1, 1);

        RJ45BLinkSpeedLabel = new QLabel(groupBox_Status);
        RJ45BLinkSpeedLabel->setObjectName(QString::fromUtf8("RJ45BLinkSpeedLabel"));
        RJ45BLinkSpeedLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BLinkSpeedLabel, 3, 4, 1, 1);

        RJ45BForceModeLabel = new QLabel(groupBox_Status);
        RJ45BForceModeLabel->setObjectName(QString::fromUtf8("RJ45BForceModeLabel"));
        RJ45BForceModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BForceModeLabel, 4, 4, 1, 1);

        RJ45BDuplexTypeLabel = new QLabel(groupBox_Status);
        RJ45BDuplexTypeLabel->setObjectName(QString::fromUtf8("RJ45BDuplexTypeLabel"));
        RJ45BDuplexTypeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BDuplexTypeLabel, 5, 4, 1, 1);

        RJ45BModeLabel = new QLabel(groupBox_Status);
        RJ45BModeLabel->setObjectName(QString::fromUtf8("RJ45BModeLabel"));
        RJ45BModeLabel->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(RJ45BModeLabel, 6, 4, 1, 1);


        gridLayout_19->addLayout(gridLayout_13, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_Status);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(2, 1);

        gridLayout_18->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1237, 22));
        SerialSelect = new QMenu(menubar);
        SerialSelect->setObjectName(QString::fromUtf8("SerialSelect"));
        OpenSerialMenu = new QMenu(SerialSelect);
        OpenSerialMenu->setObjectName(QString::fromUtf8("OpenSerialMenu"));
        CloseSerialMenu = new QMenu(SerialSelect);
        CloseSerialMenu->setObjectName(QString::fromUtf8("CloseSerialMenu"));
        BoardCardSelect = new QMenu(menubar);
        BoardCardSelect->setObjectName(QString::fromUtf8("BoardCardSelect"));
        ModeSwitch = new QMenu(menubar);
        ModeSwitch->setObjectName(QString::fromUtf8("ModeSwitch"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(SerialSelect->menuAction());
        menubar->addAction(BoardCardSelect->menuAction());
        menubar->addAction(ModeSwitch->menuAction());
        SerialSelect->addAction(OpenSerialMenu->menuAction());
        SerialSelect->addAction(CloseSerialMenu->menuAction());
        BoardCardSelect->addAction(actionVBE1200);
        BoardCardSelect->addAction(actionVBE1000);
        ModeSwitch->addAction(action_Bypass);
        ModeSwitch->addAction(action_Mirror);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\275\246\350\275\275\344\273\245\345\244\252\347\275\221\350\275\254\346\215\242\346\216\247\345\210\266", nullptr));
        actionVBE1200->setText(QCoreApplication::translate("MainWindow", "VBE1200", nullptr));
        actionVBE1000->setText(QCoreApplication::translate("MainWindow", "VBE1000", nullptr));
        action_Bypass->setText(QCoreApplication::translate("MainWindow", "\347\233\264\351\200\232\357\274\210Bypass\357\274\211", nullptr));
        action_Mirror->setText(QCoreApplication::translate("MainWindow", "\351\225\234\345\203\217\357\274\210Mirror\357\274\211", nullptr));
        groupBoxSerialReceive->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\346\216\245\346\224\266", nullptr));
        rBtnReceiveASCII->setText(QCoreApplication::translate("MainWindow", "ASCII", nullptr));
        rBtnReceiveHEX->setText(QCoreApplication::translate("MainWindow", "HEX", nullptr));
        BtnClearReceiveData->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        textEditReceiveData->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        groupBoxSerialSend->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\221\351\200\201", nullptr));
        rBtnSendDataASCII->setText(QCoreApplication::translate("MainWindow", "ASCII", nullptr));
        rBtnSendDataHex->setText(QCoreApplication::translate("MainWindow", "HEX", nullptr));
        BtnSendData->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        groupBoxMdioInterface->setTitle(QCoreApplication::translate("MainWindow", "MDIO\346\216\245\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PHY ADDR", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "REG ADDR", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "DEV ADDR", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "VALUE", nullptr));
        lineEditPhyAddr->setText(QString());
        BtnMdioRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        BtnMdioWrite->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
        groupBoxFpgaInterface->setTitle(QCoreApplication::translate("MainWindow", "FPGA\346\216\245\345\217\243", nullptr));
        lineEditFpgaAddr->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "VALUE", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "FPGA ADDR", nullptr));
        BtnFpgaRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
        BtnFpgaWrite->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
        groupBoxFirmwareWrite->setTitle(QCoreApplication::translate("MainWindow", "\345\233\272\344\273\266\347\203\247\345\206\231", nullptr));
        labelCurFirmwareVersion->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\233\272\344\273\266\347\211\210\346\234\254\357\274\232", nullptr));
        labelCurFpgaVersion->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215FPGA\347\211\210\346\234\254\357\274\232", nullptr));
        BtnGetVersion->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\347\211\210\346\234\254", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "path", nullptr));
        tBtnSelectPath->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        rBtnMcu->setText(QCoreApplication::translate("MainWindow", "Mcu", nullptr));
        rBtnFpga->setText(QCoreApplication::translate("MainWindow", "FPGA", nullptr));
        BtnBurn->setText(QCoreApplication::translate("MainWindow", "\347\203\247\345\206\231", nullptr));
        groupBox_RJ45_1->setTitle(QCoreApplication::translate("MainWindow", "RJ45-1", nullptr));
        rBtnGeSpeedRJ45_1->setText(QCoreApplication::translate("MainWindow", "1000 Mbps", nullptr));
        rBtnFullDuplexRJ45_1->setText(QCoreApplication::translate("MainWindow", "Full Duplex", nullptr));
        rBtnAnegDisableRJ45_1->setText(QCoreApplication::translate("MainWindow", "Aneg Disable", nullptr));
        rBtnFeSpeedRJ45_1->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        rBtnHalfDuplexRJ45_1->setText(QCoreApplication::translate("MainWindow", "Half Duplex", nullptr));
        rBtnAnegEnableRJ45_1->setText(QCoreApplication::translate("MainWindow", "Aneg Enable", nullptr));
        BtnSetRJ45_1->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        groupBox_RJ45_2->setTitle(QCoreApplication::translate("MainWindow", "RJ45-2", nullptr));
        rBtnGeSpeedRJ45_2->setText(QCoreApplication::translate("MainWindow", "1000 Mbps", nullptr));
        rBtnAnegEnableRJ45_2->setText(QCoreApplication::translate("MainWindow", "Aneg Enable", nullptr));
        rBtnHalfDuplexRJ45_2->setText(QCoreApplication::translate("MainWindow", "Half Duplex", nullptr));
        rBtnFullDuplexRJ45_2->setText(QCoreApplication::translate("MainWindow", "Full Duplex", nullptr));
        rBtnFeSpeedRJ45_2->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        rBtnAnegDisableRJ45_2->setText(QCoreApplication::translate("MainWindow", "Aneg Disable", nullptr));
        BtnSetRJ45_2->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        groupBox_T1_2->setTitle(QCoreApplication::translate("MainWindow", "T1-2", nullptr));
        rBtnMasterModeT1_2->setText(QCoreApplication::translate("MainWindow", "Force Master", nullptr));
        rBtnAnegEnableT1_2->setText(QCoreApplication::translate("MainWindow", "Aneg Enable", nullptr));
        rBtnAnegDisableT1_2->setText(QCoreApplication::translate("MainWindow", "Aneg Disable", nullptr));
        rBtnSlaverModeT1_2->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        rBtnFeSpeedT1_2->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        rBtnGeSpeedT1_2->setText(QCoreApplication::translate("MainWindow", "1000 Mbps", nullptr));
        BtnSetT1_2->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        groupBox_T1_1->setTitle(QCoreApplication::translate("MainWindow", "T1-1", nullptr));
        rBtnAnegEnableT1_1->setText(QCoreApplication::translate("MainWindow", "Aneg Enable", nullptr));
        rBtnMasterModeT1_1->setText(QCoreApplication::translate("MainWindow", "Force Master", nullptr));
        rBtnGeSpeedT1_1->setText(QCoreApplication::translate("MainWindow", "1000 Mbps", nullptr));
        rBtnFeSpeedT1_1->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        rBtnAnegDisableT1_1->setText(QCoreApplication::translate("MainWindow", "Aneg Disable", nullptr));
        rBtnSlaverModeT1_1->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        BtnSetT1_1->setText(QCoreApplication::translate("MainWindow", "set", nullptr));
        groupBox_Status->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        T1ALinkSpeedLabel->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        RJ45AAutoNegoLabel->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        RJ45ALinkStatusLabel->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        T1BAutoNegoLabel->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        BtnStatusFresh->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\345\210\267\346\226\260", nullptr));
        T1AAutoNegoLabel->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        RJ45AForceModeLabel->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        label_RJ45_A->setText(QCoreApplication::translate("MainWindow", "\346\231\256\351\200\232RJ45-1", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Link Status", nullptr));
        T1AForceModeLabel->setText(QCoreApplication::translate("MainWindow", "Slaver", nullptr));
        RJ45ALinkSpeedLabel->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Duplex", nullptr));
        label_T1_A->setText(QCoreApplication::translate("MainWindow", "\350\275\246\350\275\275T1-1", nullptr));
        T1BLinkSpeedLabel->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Master/Slaver", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Bypass/Mirror", nullptr));
        T1ADuplexLabel->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Auto Nego", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Link Speed", nullptr));
        RJ45ADuplexTypeLabel->setText(QCoreApplication::translate("MainWindow", "Full", nullptr));
        T1BLinkStatusLabel->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        RJ45AModeLabel->setText(QCoreApplication::translate("MainWindow", "Bypass", nullptr));
        label_RJ45_B->setText(QCoreApplication::translate("MainWindow", "\346\231\256\351\200\232RJ45-2", nullptr));
        T1ALinkStatusLabel->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        T1AModeLabel->setText(QCoreApplication::translate("MainWindow", "Bypass", nullptr));
        label_T1_B->setText(QCoreApplication::translate("MainWindow", "\350\275\246\350\275\275T2-2", nullptr));
        T1BForceModeLabel->setText(QCoreApplication::translate("MainWindow", "Slaver", nullptr));
        T1BDuplexLabel->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        T1BModeLabel->setText(QCoreApplication::translate("MainWindow", "Bypass", nullptr));
        RJ45BAutoNegoLabel->setText(QCoreApplication::translate("MainWindow", "Enable", nullptr));
        RJ45BLinkStatusLabel->setText(QCoreApplication::translate("MainWindow", "Down", nullptr));
        RJ45BLinkSpeedLabel->setText(QCoreApplication::translate("MainWindow", "100 Mbps", nullptr));
        RJ45BForceModeLabel->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        RJ45BDuplexTypeLabel->setText(QCoreApplication::translate("MainWindow", "Full", nullptr));
        RJ45BModeLabel->setText(QCoreApplication::translate("MainWindow", "Bypass", nullptr));
#if QT_CONFIG(statustip)
        statusBar->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        SerialSelect->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\351\200\211\346\213\251", nullptr));
        OpenSerialMenu->setTitle(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        CloseSerialMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        BoardCardSelect->setTitle(QCoreApplication::translate("MainWindow", "\346\235\277\345\215\241\351\200\211\346\213\251", nullptr));
        ModeSwitch->setTitle(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\345\210\207\346\215\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
