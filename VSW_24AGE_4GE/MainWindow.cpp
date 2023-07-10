#include "MainWindow.h"
#include "FormNetConfig.h"
#include "ServiceException.h"
#include "ui_MainWindow.h"

#include "FormSerialPortConfig.h"
#include "SerialPortThread.h"
#include "TcpServerThread.h"
#include "TcpClientThread.h"
#include "UdpThread.h"

#include <QFile>
#include <QGridLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "VSW_24AGE_4GE.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置应用程序窗口图标
    this->setWindowIcon(QIcon(":/icons/favicon.ico"));

    ui->tabWidget->setEnabled(false);

    initStatusBar();
    initWidget();
    initTabWidget();

    ui->gridLayout_11->setAlignment(Qt::AlignRight);

    VSW_24AGE_4GE* test = new VSW_24AGE_4GE();
    test->show();

    //隐藏线缆检测功能页
    //ui->tabWidget->removeTab(4);
//    ui->tabWidget->tabBar()->setTabVisible(0, false);
    ui->tabWidget->tabBar()->setTabVisible(4, false);
//    ui->tabWidget->tabBar()->setTabVisible(6, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    //网络配置窗口初始化
    {
        formNetConfig = new FormNetConfig();
        //设置父窗口
        formNetConfig->setParent(this);
        //设置为独立窗口
        formNetConfig->setWindowFlags(Qt::Window);
        //设置为应用程序的模态窗口，阻止本应用所有窗口的输入
        formNetConfig->setWindowModality(Qt::ApplicationModal);
    }

    //窗口配置界面初始化
    {
        formSerialPortConfig = new FormSerialPortConfig();
        //设置父窗口
        formSerialPortConfig->setParent(this);
        //设置为独立窗口
        formSerialPortConfig->setWindowFlags(Qt::Window);
        //设置为应用程序的模态窗口，阻止本应用所有窗口的输入
        formSerialPortConfig->setWindowModality(Qt::ApplicationModal);
    }

    ui->actionCloseSerial->setEnabled(false);
    ui->actionDisConnect->setEnabled(false);
    ui->portNameVLAN->setEnabled(false);
    ui->lineEditPortName->setEnabled(false);

    QList<QAction*> actions = ui->menuStyleSheet->actions();
    slotMenuStyleSheetTriggered(actions[7]);

    //设置窗口样式菜单栏选项不可视
    ui->menuStyleSheet->menuAction()->setVisible(false);

    //菜单栏信号槽连接
    connect(ui->menuSerial, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuSerialTriggered(QAction*)));
    connect(ui->menuNet, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuNetTriggered(QAction*)));
    connect(ui->menuStyleSheet, SIGNAL(triggered(QAction*)), this, SLOT(slotMenuStyleSheetTriggered(QAction*)));

    //网络配置界面信号槽连接
    connect(formNetConfig, SIGNAL(signalCurrentStatusTips(QString)), this, SLOT(slotCurrentNetStatusTips(QString)));

    //串口配置界面信号槽连接
    connect(this, SIGNAL(signalStopSerialPortThread()), SerialPortThread::instance(), SLOT(slotCloseThread()));
    connect(SerialPortThread::instance(), SIGNAL(signalSerialPortThreadSuccess()), this, SLOT(slotSerialPortThreadSuccess()));

    //关闭网络连接线程信号槽连接
    connect(this, SIGNAL(signalCloseNetThread()), TcpServerThread::instance(), SLOT(slotCloseThread()));
    connect(this, SIGNAL(signalCloseNetThread()), TcpClientThread::instance(), SLOT(slotCloseThread()));
    connect(this, SIGNAL(signalCloseNetThread()), UdpThread::instance(), SLOT(slotCloseThread()));
}

void MainWindow::initStatusBar()
{
    //初始化状态栏提示
    statusBarTipLabel = new QLabel();
    ui->statusbar->addWidget(statusBarTipLabel);

    m_progressBar = new QProgressBar();
    m_progressBar->setMaximum(100);
    m_progressBar->setMinimum(0);
    m_progressBar->setValue(0);
    instructionExecTipLabel = new QLabel();
    ui->statusbar->addPermanentWidget(m_progressBar);
    ui->statusbar->addPermanentWidget(instructionExecTipLabel);

    TcpClientThread::instance()->setProgressBar(m_progressBar);
    TcpClientThread::instance()->setTipslabel(instructionExecTipLabel);
}

void MainWindow::initTabWidget()
{
    //设置当前选中为选择测试项
    ui->tabWidget->setCurrentIndex(0);

    auto size = ui->tabWidget->count();
    ui->tabWidget->setTabPosition(QTabWidget::West);
    for(int i = 0; i < size; i ++)
    {
        auto label = new QLabel(ui->tabWidget->tabText(i), this);
        ui->tabWidget->setTabText(i, "");

        ui->tabWidget->tabBar()->setTabButton(i, QTabBar::ButtonPosition::RightSide, label);

        //让字体居中
        ui->tabWidget->tabBar()->tabButton(i, QTabBar::ButtonPosition::RightSide)->setFixedHeight(16);
    }

    initStatusTableWidget();
    initPortManagetWidget();
    initPortMirrorWidget();
    initLoopbackTestWidget();
    initCableTestWidget();
    initVLANConfigWidget();
    initMACConfigWidget();

    //TabWidget控件当前页更改信号槽连接
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(slotTabWidgetCurrentChanged(int)));
    connect(TcpClientThread::instance(), SIGNAL(signalServerDisconnect()), this, SLOT(slotTcpClientDisConnect()));
}

void MainWindow::initStatusTableWidget()
{
    ui->tabWidgetChipInfo->setCurrentIndex(0);
    ui->groupBoxChipInfo->setVisible(false);

    //状态显示界面状态显示表格样式初始化
    ui->tableWidgetStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                  //先自适应宽度
    ui->tableWidgetStatus->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);      //然后设置要根据内容使用宽度的列
    //ui->tableWidgetStatus->setSelectionBehavior(QAbstractItemView::SelectRows);                             //整行选中的方式
    ui->tableWidgetStatus->setEditTriggers(QAbstractItemView::NoEditTriggers);                              //禁止修改
    ui->tableWidgetStatus->setSelectionMode(QAbstractItemView::NoSelection);                                //禁止选中
    ui->tableWidgetStatus->verticalHeader()->hide();                                                        //行号隐藏

    ui->tableWidgetNormalRJ45->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);              //先自适应宽度
    ui->tableWidgetNormalRJ45->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);  //然后设置要根据内容使用宽度的列
    //ui->tableWidgetNormalRJ45->setSelectionBehavior(QAbstractItemView::SelectRows);                         //整行选中的方式
    ui->tableWidgetNormalRJ45->setEditTriggers(QAbstractItemView::NoEditTriggers);                          //禁止修改
    ui->tableWidgetNormalRJ45->setSelectionMode(QAbstractItemView::NoSelection);                            //禁止选中
    ui->tableWidgetNormalRJ45->verticalHeader()->hide();                                                    //行号隐藏

    //表格添加数据测试, 后续需要从板卡获取数据并显示更新
    {
        for(int i = 0; i < 28; i ++) {
            CHIP_DATA data;
            data.autoNego = 0;
            data.linkStatus = 0;
            data.linkSpeed = 0;
            data.masterSlave = 0;
            data.duplex = 0;

            data.chipName = QString("P%1").arg(QString::number(i + 1));

            int portId = TcpClientThread::instance()->portMapping(data.chipName);
            if(portId < 4) {
                data.chipType = 0;
            }
            else if(portId >= 4 && portId < 28) {
                data.chipType = 1;
            }

            chipDataList.append(data);
        }
    }
    statusTableWidgetAddItems(chipDataList);

    connect(ui->tableWidgetStatus, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slotTableWidgetItemDoubleClicked(QTableWidgetItem*)));
    connect(ui->tableWidgetNormalRJ45, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slotTableWidgetItemDoubleClicked(QTableWidgetItem*)));

    connect(ui->BtnChipModify, SIGNAL(clicked()), this, SLOT(slotBtnChipModifyClicked()));

    connect(ui->rBtnAnegEnable, SIGNAL(clicked()), this, SLOT(slotRadioButtonAnegClicked()));
    connect(ui->rBtnAnegDisable, SIGNAL(clicked()), this, SLOT(slotRadioButtonAnegClicked()));

    connect(ui->rBtnSpeed100M, SIGNAL(clicked()), this, SLOT(slotRadioButtonSpeedClicked()));
    connect(ui->rBtnSpeed1000M, SIGNAL(clicked()), this, SLOT(slotRadioButtonSpeedClicked()));

    connect(ui->rBtnMaster, SIGNAL(clicked()), this, SLOT(slotRadioButtonMasterClicked()));
    connect(ui->rBtnSlave, SIGNAL(clicked()), this, SLOT(slotRadioButtonMasterClicked()));

    connect(ui->rBtnFullDuplex, SIGNAL(clicked()), this, SLOT(slotRadioButtonDuplexClicked()));
    connect(ui->rBtnHalfDuplex, SIGNAL(clicked()), this, SLOT(slotRadioButtonDuplexClicked()));
}

void MainWindow::initPortManagetWidget()
{
    ui->groupBoxPortInfo->setVisible(false);
    ui->BtnPackUp->setVisible(false);

    ui->cBoxPortStatus->setEnabled(false);
    ui->cBoxDuplex->setEnabled(false);

    //端口管理界面端口信息显示表格样式初始化
    ui->tableWidgetPortInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    ui->tableWidgetPortInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetPortInfo->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetPortInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    //ui->tableWidgetPortInfo->setSelectionMode(QAbstractItemView::NoSelection);                                 //禁止选中
    ui->tableWidgetPortInfo->verticalHeader()->hide();                                                         //行号隐藏
    slotCheckBoxPVIDClicked();

    //端口信息表格测试
    {
        for(int i = 0; i < 28; i ++) {
            PORT_DATA data;
            data.portName = QString("P%1").arg(QString::number(i + 1));
            data.chipID = TcpClientThread::instance()->portMapping(data.portName);
            data.portStatus = "Disable";
            data.portDuplex = "Auto";
            data.portSpeed = QString("1000M");
            data.portType = QString("Access");
            data.PVID = 1;

            data.portVlanGroup = 1;

            data.netLineType = "Across";
            data.flowControl = "Disable";
            data.energyMode = "Disable";
            data.maxMacCount = 100;

            data.broadcast = "pps:100M";
            data.multicast = "kbps:100M";
            data.unknownUnicast = "pps:10GE";
            data.loopback = i % 2;
            data.loopbackEnable = i % 2;

            data.mirrorPortType = 2;
            data.mirrorPortMonitorDir = 2;

            portInfoList.append(data);
        }
    }

    portTableWidgetAddItems(portInfoList);

    //设置PVID输入框的输入范围
    QRegularExpression regExpPVID("^(?:[0-9]|"
                                  "\\d{0,2}|"
                                  "\\d{0,3}|"
                                  "[0-3]\\d{0,3}|"
                                  "40[0-9][0-4])$");
    ui->lineEditPVID->setValidator(new QRegularExpressionValidator(regExpPVID, this));

    //设置最大MAC地址数输入框的输入范围
    QRegularExpression regExpMaxCount("^(?:[0-9]|"
                                      "\\d{0,2}|"
                                      "\\d{0,3}|"
                                      "[0-7]\\d{0,3}|"
                                      "8[0-1][0-9][0-2])$");

    //端口配置界面--端口信息表格信号槽连接
    connect(ui->tableWidgetPortInfo, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slotTableWidgetPortInfoDoubleClicked(QTableWidgetItem*)));
    connect(ui->tableWidgetPortInfo, SIGNAL(currentTextChanged(int)), this, SLOT(slotPortInfoCurrentTextChanged(int)));

    //端口配置界面--收起按钮信号槽连接
    connect(ui->BtnPackUp, SIGNAL(clicked()), this, SLOT(slotBtnPackUpClicked()));

    //端口配置界面--修改按钮信号槽连接
    connect(ui->BtnModifyPortInfo, SIGNAL(clicked()), this, SLOT(slotBtnModifyPortInfoClicked()));

    //端口配置界面--PVID复选框信号槽连接
    connect(ui->cBoxPVID, SIGNAL(clicked()), this, SLOT(slotCheckBoxPVIDClicked()));
}

void MainWindow::initPortMirrorWidget()
{
    ui->cBoxAllPort->clear();
    for(int i = 0; i < portInfoList.size(); i ++){
        ui->cBoxAllPort->addItem(portInfoList[i].portName);
    }
    ui->cBoxAllPort->setCurrentIndex(0);

    for(int i = 0; i < portInfoList.size(); i ++){
        if(portInfoList[i].mirrorPortType == 1){
            ui->cBoxAllPort->setCurrentIndex(i);
        }
    }
    portMirrorGroupTableWidgetAddItems(portInfoList);

    //端口镜像组界面镜像组信息显示表格样式初始化
    ui->tableWidgetMirrorPort->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    //ui->tableWidgetPortMirrorGroup->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetMirrorPort->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetMirrorPort->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    ui->tableWidgetMirrorPort->verticalHeader()->hide();                                                         //行号隐藏

    //端口镜像界面--创建按钮信号槽连接
    connect(ui->BtnSetMonitorPort, SIGNAL(clicked()), this, SLOT(slotBtnSetMonitorPortClicked()));
    connect(ui->tableWidgetMirrorPort, SIGNAL(currentTextChanged(int)), this, SLOT(slotTableWidgetMirrorPortChanged(int)));
}

void MainWindow::initLoopbackTestWidget()
{
    loopbackTestPortTreeWidgetAddItems(portInfoList);

    //环回测试界面--列表item单击事件信号槽连接
    connect(ui->listWidgetInner, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotListWidgetLoopbackClicked(QListWidgetItem*)));
    connect(ui->listWidgetOuter, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slotListWidgetLoopbackClicked(QListWidgetItem*)));

    //环回测试界面--列表item双击事件信号槽连接
    connect(ui->listWidgetInner, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotListWidgetLoopbackDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetOuter, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotListWidgetLoopbackDoubleClicked(QListWidgetItem*)));

    //环回测试界面--测试按钮信号槽连接
    connect(ui->BtnSetPortLoopback, SIGNAL(clicked()), this, SLOT(slotBtnSetPortLoopbackClicked()));
}

void MainWindow::initCableTestWidget()
{
    //设置线缆检测结果显示框只读属性
    ui->cableTestResults->setReadOnly(true);

    //线缆检测界面端口信息显示表格样式初始化
    ui->treeWidgetCableTestPort->header()->setSectionResizeMode(QHeaderView::Stretch);                          //自适应宽度
    ui->treeWidgetCableTestPort->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);              //然后设置要根据内容使用宽度的列
    ui->treeWidgetCableTestPort->setSelectionBehavior(QAbstractItemView::SelectRows);                           //整行选中的方式
    ui->treeWidgetCableTestPort->setEditTriggers(QAbstractItemView::NoEditTriggers);                            //禁止修改

    //线缆检测端口添加数据测试
    {
        cableTestPortTreeWidgetAddItems(portInfoList);
    }

    //线缆检测界面--测试按钮信号槽连接
    connect(ui->tBtnCableTestStart, SIGNAL(clicked()), this, SLOT(slotCableTestStartClicked()));
}

void MainWindow::initVLANConfigWidget()
{
    slotCboxVlanPortTypeCurIndexChanged(ui->cBoxVlanPortType->currentIndex());

    //VLAN配置信息显示表格样式初始化
    ui->tableWidgetVlanInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    ui->tableWidgetVlanInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetVlanInfo->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetVlanInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    ui->tableWidgetVlanInfo->verticalHeader()->hide();                                                         //行号隐藏

    //VLAN Port 配置信息显示表格样式初始化
    ui->tableWidgetVlanPortInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //先自适应宽度
    ui->tableWidgetVlanPortInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //然后设置要根据内容使用宽度的列
    ui->tableWidgetVlanPortInfo->setSelectionBehavior(QAbstractItemView::SelectRows);                          //整行选中的方式
    ui->tableWidgetVlanPortInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                           //禁止修改

    //vlan表格添加数据测试
    {
        for(int i = 1; i < 2; i ++) {
            VLAN_DATA data;
            data.ID = i;
            data.describe = QString("VLAN %1").arg(QString::number(i));
            vlanList.append(data);
        }

        vlanTableWidgetAddItems(vlanList);
    }

    //设置输入框只能输入整数
    QRegularExpression regExp("0|[1-9]\\d{0,4}");
    ui->showMinVlanId->setValidator(new QRegularExpressionValidator(regExp, this));
    ui->showMaxVlanId->setValidator(new QRegularExpressionValidator(regExp, this));

    ui->BtnDeleteVlanPort->setVisible(false);
    ui->lineEditVlanTaggedID->setEnabled(false);

    //VLAN配置界面--筛选VLAN按钮信号槽连接
    connect(ui->BtnScreen, SIGNAL(clicked()), this, SLOT(slotBtnScreenClicked()));

    //VLAN配置界面--修改PORT信息按钮信号槽连接
    connect(ui->BtnModifyPortInfoVLAN, SIGNAL(clicked()), this, SLOT(slotBtnModifyPortInfoVLANClicked()));

    connect(ui->cBoxVlanPortType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCboxVlanPortTypeCurIndexChanged(int)));

    //VLAN配置界面--VLAN界面VLAN信息表格双击信号槽连接
    connect(ui->tableWidgetVlanInfo, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotVlanInfoTableDoubleClicked(QModelIndex)));

    //VLAN配置界面--VLAN界面端口信息表格双击信号槽连接
    connect(ui->tableWidgetVlanPortInfo, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotVlanPortInfoTableDoubleClicked(QModelIndex)));

    //VLAN配置界面--VLAN界面端口信息类型单选按钮信号槽连接
    connect(ui->rBtnVlanPortNonMember, SIGNAL(clicked()), this, SLOT(slotVlanPortTypeChanged()));
    connect(ui->rBtnVlanPortUntagged, SIGNAL(clicked()), this, SLOT(slotVlanPortTypeChanged()));
    connect(ui->rBtnVlanPortTagged, SIGNAL(clicked()), this, SLOT(slotVlanPortTypeChanged()));

    //VLAN配置界面--范围创建复选框信号槽连接
    connect(ui->checkBoxScopeCreate, SIGNAL(clicked()), this, SLOT(slotCheckBoxScopeCreateClicked()));

    //VLAN配置界面--创建按钮信号槽连接
    connect(ui->BtnCreate, SIGNAL(clicked()), this, SLOT(slotBtnCreateClicked()));

    //VLAN配置界面--删除按钮信号槽连接
    connect(ui->BtnDeleteVlanPort, SIGNAL(clicked()), this, SLOT(slotBtnDeleteVlanPort()));

    //VLAN配置界面--删除VLAN按钮信号槽连接
    connect(ui->BtnDeleteVlanID, SIGNAL(clicked()), this, SLOT(slotBtnDelectVlanId()));
}

void MainWindow::initMACConfigWidget()
{
    //MAC配置界面已有MAC地址显示表格样式初始化
    ui->tableWidgetMacInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    ui->tableWidgetMacInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetMacInfo->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetMacInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    ui->tableWidgetMacInfo->verticalHeader()->hide();                                                         //行号隐藏

    //MAC表格添加数据测试
    {
        for(int i = 0; i < 100; i ++) {
            MAC_DATA data;
            data.ID = i + 1;

            //字符串补位
            auto mac1 = QString("%1").arg(i, 2, 10, QLatin1Char('0'));
            auto mac2 = QString("%1").arg(99 - i, 2, 10, QLatin1Char('0'));

            data.macAddress = QString("00-00-11-11-%1-%2").arg(mac1, mac2);
            data.vlanID = (i % 24) + 1;
            data.portName = QString("GE 1/0/%1").arg(data.vlanID);

            switch (i % 5) {
            case 0:
                data.macType = "Config static";
                break;
            case 1:
                data.macType = "Config dynamic";
                break;
            case 2:
                data.macType = "Blackhole";
                break;
            case 3:
                data.macType = "Learned";
                break;
            case 4:
                data.macType = "Other";
                break;
            default:
                break;
            }
            macInfoList.append(data);
        }

        macInfoTableWidgetAddItems(macInfoList);
    }

    for(int i = 0; i < vlanList.size(); i ++) {
        ui->cBoxMacVlanID->addItem(QString::number(vlanList[i].ID));
    }
    ui->cBoxMacVlanID->setCurrentIndex(0);

    auto curID = ui->cBoxMacVlanID->currentText().toInt();
    for(int i = 0; i < portInfoList.size(); i ++) {
        if(portInfoList[i].portVlanGroup == curID) {
            ui->cBoxMacPort->addItem(portInfoList[i].portName);
        }
    }

    slotCheckBoxOldClicked();

    //MAC配置界面--MAC地址信息显示表格双击事件信号槽连接
    connect(ui->tableWidgetMacInfo, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(slotMacInfoTableWidgetItemDoubleClicked(QTableWidgetItem*)));

    //MAC配置界面--VLAN ID下拉框更改当前选中信号槽连接
    connect(ui->cBoxMacVlanID, SIGNAL(currentTextChanged(QString)), this, SLOT(slotMacVlanIDCurrentChanged(QString)));

    //MAC配置界面--老化复选框按钮信号槽连接
    connect(ui->cBoxOld, SIGNAL(clicked()), this, SLOT(slotCheckBoxOldClicked()));

    //MAC配置界面--MAC类型单选按钮组信号槽连接
    connect(ui->rBtnAllMac, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
    connect(ui->rBtnStaticMacAddress, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
    connect(ui->rBtnDynamicMacAddress, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
    connect(ui->rBtnBlackhole, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
    connect(ui->rBtnLearned, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
    connect(ui->rBtnOther, SIGNAL(clicked()), this, SLOT(slotMacInfoTableWidgetShow()));
}

void MainWindow::statusTableWidgetAddItems(const QList<CHIP_DATA> &chipDataList)
{
    ui->tableWidgetStatus->clearContents();
    ui->tableWidgetStatus->setRowCount(0);

    ui->tableWidgetNormalRJ45->clearContents();
    ui->tableWidgetNormalRJ45->setRowCount(0);

    auto rowCount = chipDataList.count();
    for(int i = 0; i < rowCount; i ++) {
        if(chipDataList[i].chipType == 1) {
            statusTableWidgetAddItem(ui->tableWidgetStatus, chipDataList[i]);
        }
        else if(chipDataList[i].chipType == 0) {
            statusTableWidgetAddItem(ui->tableWidgetNormalRJ45, chipDataList[i]);
        }
    }
}

void MainWindow::statusTableWidgetAddItem(QTableWidget *tableWidget, const CHIP_DATA &chipData)
{
    auto row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    tableWidget->setItem(row, 0, new QTableWidgetItem(chipData.chipName));
    tableWidget->item(row, 0)->setTextAlignment(Qt::AlignCenter);

    tableWidget->setItem(row, 1, new QTableWidgetItem(TcpClientThread::instance()->getChipStatus(chipData.autoNego)));
    tableWidget->item(row, 1)->setTextAlignment(Qt::AlignCenter);

    tableWidget->setItem(row, 2, new QTableWidgetItem(TcpClientThread::instance()->getChipLinkType(chipData.linkStatus)));
    tableWidget->item(row, 2)->setTextAlignment(Qt::AlignCenter);

    tableWidget->setItem(row, 3, new QTableWidgetItem(TcpClientThread::instance()->getChipSpeed(chipData.linkSpeed)));
    tableWidget->item(row, 3)->setTextAlignment(Qt::AlignCenter);

    if(chipData.chipType == 0) {
        tableWidget->setItem(row, 4, new QTableWidgetItem(TcpClientThread::instance()->getChipDuplex(chipData.duplex)));
        tableWidget->item(row, 4)->setTextAlignment(Qt::AlignCenter);
    }
    else if(chipData.chipType == 1) {
        tableWidget->setItem(row, 4, new QTableWidgetItem(TcpClientThread::instance()->getChipMaster(chipData.masterSlave)));
        tableWidget->item(row, 4)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::portTableWidgetAddItems(const QList<PORT_DATA> &portDataList)
{
    ui->tableWidgetPortInfo->clearContents();
    ui->tableWidgetPortInfo->setRowCount(0);

    auto rowCount = portDataList.size();
    for(int row = 0; row < rowCount; row ++) {
        ui->tableWidgetPortInfo->appendRow(portDataList[row]);
    }

    //初始化表格中的下拉框信号槽连接---必备--添加数据后使用
    ui->tableWidgetPortInfo->initConnect();
}

void MainWindow::portMirrorGroupTableWidgetAddItems(const QList<PORT_DATA> &portInfoList)
{
    ui->tableWidgetMirrorPort->clearContents();
    ui->tableWidgetMirrorPort->setRowCount(0);

    auto rowCount = portInfoList.size();
    for(int i = 0; i < rowCount; i ++) {
        PORT_DATA data = portInfoList[i];
        if(data.mirrorPortType == 1){
            continue;
        }

        ui->tableWidgetMirrorPort->appendRow(data);
    }

    ui->tableWidgetMirrorPort->initConnect();
}

void MainWindow::vlanTableWidgetAddItems(const QList<VLAN_DATA> &vlanInfoList, int minID, int maxID)
{
    ui->tableWidgetVlanInfo->clearContents();
    ui->tableWidgetVlanInfo->setRowCount(0);

    for(int i = 0; i < vlanInfoList.size(); i ++) {
        if(vlanInfoList[i].ID >= minID &&
                vlanInfoList[i].ID <= maxID) {
            auto row = ui->tableWidgetVlanInfo->rowCount();
            ui->tableWidgetVlanInfo->insertRow(row);

            ui->tableWidgetVlanInfo->setItem(row, 0, new QTableWidgetItem(QString::number(vlanInfoList[i].ID)));
            ui->tableWidgetVlanInfo->item(row, 0)->setTextAlignment(Qt::AlignCenter);

            ui->tableWidgetVlanInfo->setItem(row, 1, new QTableWidgetItem(vlanInfoList[i].describe));
            ui->tableWidgetVlanInfo->item(row, 1)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::vlanPortInfoTableWidgetAddItems(const QList<PORT_DATA> &portList, int vlanID, QString vlanPortType)
{
    ui->tableWidgetVlanPortInfo->clearContents();
    ui->tableWidgetVlanPortInfo->setRowCount(0);

    for(int i = 0; i < portList.size(); i ++) {
        if(vlanPortType == "NonMember") {
            if(((portList[i].vlanPortType == vlanPortType) || (portList[i].portVlanGroup != vlanID))
                    && (!portList[i].taggedVlanID.contains(vlanID))) {
                vlanPortInfoTableWidgetAddItem(ui->tableWidgetVlanPortInfo, portInfoList[i]);
            }
        }
        else if((vlanPortType == "Untagged")) {
            if((portList[i].vlanPortType == vlanPortType) && (portList[i].portVlanGroup == vlanID)) {
                vlanPortInfoTableWidgetAddItem(ui->tableWidgetVlanPortInfo, portInfoList[i]);
            }
        }
        else if(vlanPortType == "Tagged") {
            if((portList[i].vlanPortType == vlanPortType) && (portList[i].taggedVlanID.contains(vlanID))) {
                vlanPortInfoTableWidgetAddItem(ui->tableWidgetVlanPortInfo, portInfoList[i]);
            }
        }
    }
}

void MainWindow::vlanPortInfoTableWidgetAddItem(QTableWidget *tableWidget, const PORT_DATA &data)
{
    auto row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    auto nameItem = new QTableWidgetItem();
    nameItem->setText(data.portName);
    nameItem->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetVlanPortInfo->setItem(row, 0, nameItem);

    auto typeItem = new QTableWidgetItem();
    typeItem->setText(data.portType);
    typeItem->setTextAlignment(Qt::AlignCenter);
    ui->tableWidgetVlanPortInfo->setItem(row, 1, typeItem);
}

void MainWindow::loopbackTestPortTreeWidgetAddItems(const QList<PORT_DATA> &portList)
{
    ui->listWidgetInner->clear();
    ui->listWidgetOuter->clear();

    int size = portList.size();
    for(int i = 0; i < size; i ++){
        PORT_DATA data = portList[i];
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(data.portName);
        item->setCheckState(data.loopbackEnable == 0 ? Qt::CheckState::Unchecked : Qt::CheckState::Checked);
        if(data.loopback == 0){//内环
            ui->listWidgetInner->addItem(item);
        }
        else if(data.loopback == 1){//外环
            ui->listWidgetOuter->addItem(item);
        }
    }
}

void MainWindow::cableTestPortTreeWidgetAddItems(const QList<PORT_DATA> &portList)
{
    ui->treeWidgetCableTestPort->clear();

    auto rowCount = portList.count();
    for(int row = 0; row < rowCount; row ++) {
        auto topItem = new QTreeWidgetItem();

        topItem->setText(0, portList[row].portName);
        topItem->setCheckState(0, Qt::Unchecked);

        ui->treeWidgetCableTestPort->addTopLevelItem(topItem);
    }
}

void MainWindow::macInfoTableWidgetAddItems(const QList<MAC_DATA> &macInfoList, const QString &macType)
{
    ui->tableWidgetMacInfo->clearContents();
    ui->tableWidgetMacInfo->setRowCount(0);

    for(int i = 0; i < macInfoList.size(); i ++) {
        if(macType == macInfoList[i].macType || macType.isEmpty()) {
            auto row = ui->tableWidgetMacInfo->rowCount();
            ui->tableWidgetMacInfo->insertRow(row);
            ui->tableWidgetMacInfo->setItem(row, 0, new QTableWidgetItem(macInfoList[i].macAddress));
            ui->tableWidgetMacInfo->item(row, 0)->setTextAlignment(Qt::AlignCenter);

            ui->tableWidgetMacInfo->setItem(row, 1, new QTableWidgetItem(QString::number(macInfoList[i].vlanID)));
            ui->tableWidgetMacInfo->item(row, 1)->setTextAlignment(Qt::AlignCenter);

            ui->tableWidgetMacInfo->setItem(row, 2, new QTableWidgetItem(macInfoList[i].macType));
            ui->tableWidgetMacInfo->item(row, 2)->setTextAlignment(Qt::AlignCenter);

            ui->tableWidgetMacInfo->setItem(row, 3, new QTableWidgetItem(macInfoList[i].portName));
            ui->tableWidgetMacInfo->item(row, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::setTableWidgetItemBackGround(QTableWidgetItem *item, QColor &color)
{
    item->setBackground(QBrush(color));
}

bool MainWindow::vlanIDIsExist(int id)
{
    for(int i = 0; i < vlanList.size(); i ++) {
        if(vlanList[i].ID == id) {
            return true;
        }
    }

    return false;
}

void MainWindow::setChipPreproty(const CHIP_DATA &data)
{
    if(data.chipName == curChipData.chipName){
        if(ui->groupBoxChipInfo->isVisible()){
            ui->groupBoxChipInfo->setVisible(false);
        }
        else{
            ui->groupBoxChipInfo->setVisible(true);
        }
    }
    else{
        ui->groupBoxChipInfo->setVisible(true);
    }

    int chipType = data.chipType;
    int aneg = data.autoNego;
    int linkStatus = data.linkStatus;
    int linkSpeed = data.linkSpeed;
    int master = data.masterSlave;
    int duplex = data.duplex;

    if(aneg){
        ui->rBtnAnegEnable->setChecked(true);
        setSpeedEnable(false);
        ui->rBtnAnegDisable->setChecked(false);
    }else{
        ui->rBtnAnegEnable->setChecked(false);
        setSpeedEnable(true);
        ui->rBtnAnegDisable->setChecked(true);
    }

    if(!linkStatus && !chipType){
        ui->rBtnSpeed1000M->setEnabled(false);
        ui->rBtnSpeed100M->setEnabled(false);
    }
    else{
        ui->rBtnSpeed1000M->setEnabled(true);
        ui->rBtnSpeed100M->setEnabled(true);
    }

    if(linkSpeed){
        ui->rBtnSpeed1000M->setChecked(false);
        ui->rBtnSpeed100M->setChecked(true);
    }else{
        ui->rBtnSpeed1000M->setChecked(true);
        ui->rBtnSpeed100M->setChecked(false);
    }

    if(master){
        ui->rBtnMaster->setChecked(true);
        ui->rBtnSlave->setChecked(false);
    }else{
        ui->rBtnMaster->setChecked(false);
        ui->rBtnSlave->setChecked(true);
    }

    if(duplex){
        ui->rBtnFullDuplex->setChecked(false);
        ui->rBtnHalfDuplex->setChecked(true);
    }else{
        ui->rBtnFullDuplex->setChecked(true);
        ui->rBtnHalfDuplex->setChecked(false);
    }
}

void MainWindow::setSpeedEnable(bool status)
{
    if(curChipData.chipType == 1){
        ui->rBtnSpeed1000M->setEnabled(status);
        ui->rBtnSpeed100M->setEnabled(status);
    }
}

void MainWindow::slotMenuSerialTriggered(QAction *action)
{
    if(action->text() == "打开串口") {
        formSerialPortConfig->show();
    }
    else {
        action->setEnabled(false);
        ui->actionOpenSerial->setEnabled(true);
        ui->menuNet->setEnabled(true);

        emit signalStopSerialPortThread();
        statusBarTipLabel->setText("");
    }
}

void MainWindow::slotMenuNetTriggered(QAction *action)
{
    if(action->text() == "网络配置") {
        formNetConfig->show();
    }
    else {
        ui->menuSerial->setEnabled(true);
        action->setEnabled(false);

        ui->actionNetConfig->setEnabled(true);
        statusBarTipLabel->setText("");

        ui->tabWidget->setEnabled(false);

        emit signalCloseNetThread();
    }
}

void MainWindow::slotMenuStyleSheetTriggered(QAction *action)
{
    auto count = ui->menuStyleSheet->actions().count();
    auto actions = ui->menuStyleSheet->actions();
    for(int i = 0; i < count; i ++) {
        auto tempAction = actions[i];
        if(tempAction->isChecked() && tempAction->text() != action->text()) {
            tempAction->setChecked(false);
        }

        if(tempAction->text() == action->text()) {
            tempAction->setChecked(true);
        }
    }

    auto styleName = action->text();

    auto qssFileName = QString(":/QSS/%1.css").arg(styleName);

    //加载CSS文件设置窗口样式
    QFile file(qssFileName);
    file.open(QFile::ReadOnly);
    auto css = QLatin1String(file.readAll());
    this->setStyleSheet(css);
}

void MainWindow::slotTabWidgetCurrentChanged(int index)
{
    //后续添加切换当前页后指令获取端口、VLAN、镜像组、MAC等信息列表
    switch (index) {
    case 0://状态显示界面
    {
        chipDataList = TcpClientThread::instance()->getChipInfoList();

        statusTableWidgetAddItems(chipDataList);
        break;
    }
    case 1://端口配置界面
    {
        portInfoList = TcpClientThread::instance()->getPortInfoList();

        portTableWidgetAddItems(portInfoList);
        break;
    }
    case 2://端口镜像界面
    {
        ui->cBoxAllPort->clear();
        for(int i = 0; i < portInfoList.size(); i ++){
            ui->cBoxAllPort->addItem(portInfoList[i].portName);
        }

        for(int i = 0; i < portInfoList.size(); i ++){
            if(portInfoList[i].mirrorPortType == 1){
                ui->cBoxAllPort->setCurrentIndex(i);
            }
        }

        TcpClientThread::instance()->getMirrorGroupPortMointorDir(portInfoList);

        portMirrorGroupTableWidgetAddItems(portInfoList);

        break;
    }
    case 3://环回测试界面
    {
        TcpClientThread::instance()->getPortLoopback(portInfoList);

        loopbackTestPortTreeWidgetAddItems(portInfoList);
        break;
    }
    case 4://线缆检测界面

        break;
    case 5://VLAN配置界面
    {
//        vlanList = TcpClientThread::instance()->getAllVlan();

        vlanTableWidgetAddItems(vlanList);
        break;
    }
    case 6://MAC配置界面

        break;

    default:
        break;
    }
}

void MainWindow::slotTcpClientDisConnect()
{
    TcpClientThread::instance()->slotCloseThread();
}

void MainWindow::slotTableWidgetItemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    QString chipName = item->tableWidget()->item(row, 0)->text();

    for(int i = 0; i < chipDataList.size(); i ++) {
        if(chipName == chipDataList[i].chipName) {
            setChipPreproty(chipDataList[i]);
            curChipData = chipDataList[i];

            if(curChipData.chipType == 0){
                ui->rBtnMaster->hide();
                ui->rBtnSlave->hide();
                ui->rBtnFullDuplex->show();
                ui->rBtnHalfDuplex->show();
            }
            else if(curChipData.chipType == 1){
                ui->rBtnMaster->show();
                ui->rBtnSlave->show();
                ui->rBtnFullDuplex->hide();
                ui->rBtnHalfDuplex->hide();
            }
        }
    }
}

void MainWindow::slotRadioButtonAnegClicked()
{
    int aneg = 0;
    if(ui->rBtnAnegDisable->isChecked()){
        aneg = 0;

        setSpeedEnable(true);
    }
    else if (ui->rBtnAnegEnable->isChecked()){
        aneg = 1;

        setSpeedEnable(false);
    }


    if(aneg != curChipData.autoNego){
        curChipData.modify = curChipData.modify | (1 << 3);
    }
    else{
        curChipData.modify = curChipData.modify & ~(1 << 3);
    }
}

void MainWindow::slotRadioButtonSpeedClicked()
{
    int speed = 0;
    if(ui->rBtnSpeed1000M->isChecked()){
        speed = 0;
    }
    else if (ui->rBtnSpeed100M->isChecked()){
        speed = 1;
    }

    if(speed != curChipData.linkSpeed){
        curChipData.modify = curChipData.modify | (1 << 1);
    }
    else{
        curChipData.modify = curChipData.modify & ~(1 << 1);
    }
}

void MainWindow::slotRadioButtonMasterClicked()
{
    int master = 0;
    if(ui->rBtnMaster->isChecked()){
        master = 1;
    }
    else if (ui->rBtnSlave->isChecked()){
        master = 0;
    }

    if(master != curChipData.masterSlave){
        curChipData.modify = curChipData.modify | (1);
    }
    else{
        curChipData.modify = curChipData.modify & ~(1);
    }
}

void MainWindow::slotRadioButtonDuplexClicked()
{
    int duplex = 0;
    if(ui->rBtnFullDuplex->isChecked()){
        duplex = 0;
    }
    else if (ui->rBtnHalfDuplex->isChecked()){
        duplex = 1;
    }

    if(duplex != curChipData.duplex){
        curChipData.modify = curChipData.modify | 1;
    }
    else{
        curChipData.modify = curChipData.modify & ~(1);
    }
}

void MainWindow::slotBtnChipModifyClicked()
{
    //后续添加修改芯片信息指令
    try {
        curChipData.autoNego = ui->rBtnAnegEnable->isChecked() == true ? 1 : 0;
        curChipData.linkSpeed = ui->rBtnSpeed1000M->isChecked() == true ? 1 : 0;
        curChipData.masterSlave = ui->rBtnMaster->isChecked() == true ? 1 : 0;
        curChipData.duplex = ui->rBtnHalfDuplex->isChecked() == true ? 1 : 0;

        TcpClientThread::instance()->setChipInfo(curChipData);

        for(int i = 0; i < chipDataList.size(); i ++){
            if(curChipData.chipName == chipDataList[i].chipName){
                chipDataList[i].autoNego = ui->rBtnAnegEnable->isChecked() == true ? 1 : 0;
                chipDataList[i].linkSpeed = ui->rBtnSpeed1000M->isChecked() == true ? 1 : 0;
                if(chipDataList[i].chipType == 0){
                    chipDataList[i].masterSlave = ui->rBtnMaster->isChecked() == true ? 1 : 0;
                }
                else{
                    chipDataList[i].duplex = ui->rBtnHalfDuplex->isChecked() == true ? 1 : 0;
                }
            }
        }
        ui->groupBoxChipInfo->setVisible(false);

        CHIP_DATA chipdata = TcpClientThread::instance()->getChipInfo(curChipData.chipName);

        for(int i = 0; i < chipDataList.size(); i ++){
            if(chipdata.chipName == chipDataList[i].chipName){
                chipDataList[i].autoNego = chipdata.autoNego;
                chipDataList[i].linkSpeed = chipdata.linkSpeed;
                chipDataList[i].linkStatus = chipdata.linkStatus;
                if(chipDataList[i].chipType == 0){
                    chipDataList[i].masterSlave = chipdata.masterSlave;
                }
                else{
                    chipDataList[i].duplex = chipdata.duplex;
                }
            }
        }

        statusTableWidgetAddItems(chipDataList);
        curChipData = CHIP_DATA();
    }
    catch (ServiceException& e) {
        return;
    }
}

void MainWindow::slotSerialPortThreadSuccess()
{
    ui->menuNet->setEnabled(false);
    ui->actionOpenSerial->setEnabled(false);
    ui->actionCloseSerial->setEnabled(true);

    statusBarTipLabel->setText(QString("串口[%1]打开中...").arg(SerialPortThread::instance()->getSerialName()));
}

void MainWindow::slotCurrentNetStatusTips(QString status)
{
    ui->tabWidget->setEnabled(true);
    statusBarTipLabel->setText(status);

    statusBarTipLabel->setText("");

    ui->menuSerial->setEnabled(false);
    ui->actionNetConfig->setEnabled(false);
    ui->actionDisConnect->setEnabled(true);
}

void MainWindow::slotTableWidgetPortInfoDoubleClicked(QTableWidgetItem *item)
{
    auto row = item->row();
    if(ui->lineEditPortName->text() == portInfoList[row].portName){
        if(ui->groupBoxPortInfo->isVisible()){
            ui->groupBoxPortInfo->setVisible(false);
            ui->BtnPackUp->setVisible(false);
        }
        else{
            ui->groupBoxPortInfo->setVisible(true);
            ui->BtnPackUp->setVisible(true);
        }
    }
    else{
        ui->groupBoxPortInfo->setVisible(true);
        ui->BtnPackUp->setVisible(true);
    }

    ui->lineEditPortName->setText(portInfoList[row].portName);
    ui->cBoxPortStatus->setCurrentText(portInfoList[row].portStatus);
    ui->cBoxConnectType->setCurrentText(portInfoList[row].portType);
    ui->cBoxPortSpeed->setCurrentText(portInfoList[row].portSpeed);
    ui->lineEditVlanId->setText(QString::number(portInfoList[row].portVlanGroup));
    ui->cBoxDuplex->setCurrentText(portInfoList[row].portDuplex);

    ui->cBoxLoopback->setEnabled(portInfoList[row].loopbackEnable);
    ui->cBoxLoopback->setCurrentIndex(portInfoList[row].loopback);

    //窗口PVID添加数据
    if(portInfoList[row].PVID == 0) {
        ui->cBoxPVID->setChecked(false);
        ui->lineEditPVID->setEnabled(false);
    }
    else {
        ui->cBoxPVID->setChecked(true);
        ui->lineEditPVID->setEnabled(true);
        ui->lineEditPVID->setText(QString::number(portInfoList[row].PVID));
    }
}

void MainWindow::slotPortInfoCurrentTextChanged(int row)
{
    auto data = ui->tableWidgetPortInfo->getRowData(row);
    for(int i = 0; i < portInfoList.size(); i ++) {
        if(portInfoList[i].portName == data.portName) {
            try {
                TcpClientThread::instance()->setPortInfo(portInfoList[i]);

                portInfoList[i].portStatus = data.portStatus;
                portInfoList[i].portType = data.portType;
                portInfoList[i].portSpeed = data.portSpeed;
                portInfoList[i].portDuplex = data.portDuplex;
            }
            catch (ServiceException& e) {
                QMessageBox::information(this, "提示", e.getMessage());
                portTableWidgetAddItems(portInfoList);
                return;
            }
        }
    }
}

void MainWindow::slotBtnPackUpClicked()
{
    ui->groupBoxPortInfo->setVisible(false);
    ui->BtnPackUp->setVisible(false);
}

void MainWindow::slotBtnModifyPortInfoClicked()
{
    ui->groupBoxPortInfo->setVisible(false);

    auto curName = ui->lineEditPortName->text();
    for(int i = 0; i < portInfoList.size(); i ++) {
        if(curName == portInfoList[i].portName) {
            portInfoList[i].portStatus = ui->cBoxPortStatus->currentText();
            portInfoList[i].portType = ui->cBoxConnectType->currentText();
            portInfoList[i].portSpeed = ui->cBoxPortSpeed->currentText();
            portInfoList[i].portVlanGroup = ui->lineEditVlanId->text().toInt();
            portInfoList[i].portDuplex = ui->cBoxDuplex->currentText();

            if(!ui->cBoxPVID->isChecked()) {//判断PVID复选框是否勾选，不勾选设置PVID为0
                portInfoList[i].PVID = 0;
            }
            else {
                if(ui->lineEditPVID->text().isEmpty()) {//判断PVID输入框内容是否为空，为空则设置PVID为0
                    portInfoList[i].PVID = 0;
                }
                else {
                    portInfoList[i].PVID = ui->lineEditPVID->text().toInt();
                }
            }

            try {
                TcpClientThread::instance()->setPortInfo(portInfoList[i]);
            } catch (ServiceException& e) {
                QMessageBox::information(this, "提示", e.getMessage());
            }
        }
    }

    portTableWidgetAddItems(portInfoList);
    ui->lineEditPortName->clear();
}

void MainWindow::slotCheckBoxPVIDClicked()
{
    ui->lineEditPVID->setEnabled(ui->cBoxPVID->isChecked());
}

void MainWindow::slotCreatePortMirrorGroupClicked()
{
    try {
        TcpClientThread::instance()->createMirrorGroupID(0);

        MGROUP_DATA data;
        data.ID = 0;
        data.type = "";
        mGroupInfoList.append(data);

        portMirrorGroupTableWidgetAddItems(portInfoList);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
    }
}

void MainWindow::slotBtnSetMonitorPortClicked()
{
    for(int i = 0; i < portInfoList.size(); i ++){
        if(portInfoList[i].mirrorPortType == 1){
            int ret = QMessageBox::information(this, "提示", "已有监控端口，是否确认修改！", QMessageBox::Yes | QMessageBox::No);
            if(ret == QMessageBox::Yes){
                QString curPortName = ui->cBoxAllPort->currentText();
                try {
                    TcpClientThread::instance()->setMirrorGroupPortPreproty(portInfoList[i].portName, 2);
                    portInfoList[i].mirrorPortType = 2;
                    portInfoList[i].mirrorPortEnable = 0;
                    portInfoList[i].mirrorPortMonitorDir = 0;

                    TcpClientThread::instance()->setMirrorGroupPortPreproty(curPortName, 1, 1);
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    return;
                }
            }
        }
        else{
            try {
                QString curPortName = ui->cBoxAllPort->currentText();
                TcpClientThread::instance()->setMirrorGroupPortPreproty(curPortName, 1, 1);
                portInfoList[i].mirrorPortType = 1;
                portInfoList[i].mirrorPortEnable = 0;
                portInfoList[i].mirrorPortMonitorDir = 0;
                break;
            }
            catch (ServiceException& e) {
                QMessageBox::information(this, "提示", e.getMessage());
                return;
            }
        }
    }

    portMirrorGroupTableWidgetAddItems(portInfoList);
}

void MainWindow::slotTableWidgetMirrorPortChanged(int row)
{
    PORT_DATA data = ui->tableWidgetMirrorPort->getRowData(row);

    for(int i = 0; i < portInfoList.size(); i ++){
        if(data.portName == portInfoList[i].portName){
            try {
                TcpClientThread::instance()->setMirrorGroupPortPreproty(data.portName, data.mirrorPortType, data.mirrorPortEnable, data.mirrorPortMonitorDir);

                portInfoList[i].mirrorPortType = data.mirrorPortType;
                portInfoList[i].mirrorPortEnable = data.mirrorPortEnable;
                portInfoList[i].mirrorPortMonitorDir = data.mirrorPortMonitorDir;
            }
            catch (ServiceException& e) {
                QMessageBox::information(this, "提示", e.getMessage());

                portMirrorGroupTableWidgetAddItems(portInfoList);
                return;
            }
        }
    }
}

void MainWindow::slotListWidgetLoopbackClicked(QListWidgetItem *item)
{
    QString portName = item->text();
    for(int i = 0; i < portInfoList.size(); i ++){
        if(portName == portInfoList[i].portName){
            int loopbackEnable = item->checkState() == Qt::Checked ? 1 : 0;
            if(loopbackEnable != portInfoList[i].loopbackEnable){
                try {
                    TcpClientThread::instance()->setLoopBackTest(portName, portInfoList[i].loopback, loopbackEnable);

                    portInfoList[i].loopbackEnable = loopbackEnable;
                }
                catch (ServiceException& e) {
                    return;
                }
            }
        }
    }
}

void MainWindow::slotListWidgetLoopbackDoubleClicked(QListWidgetItem *item)
{
    QString portName = item->text();
    for(int i = 0; i < portInfoList.size(); i ++){
        if(portName == portInfoList[i].portName){
            ui->lineEditPortNameLoopback->setText(portName);
            ui->cBoxTestMode->setCurrentIndex(portInfoList[i].loopback);
            ui->cBoxTestEnable->setCurrentIndex(portInfoList[i].loopbackEnable);
        }
    }
}

void MainWindow::slotBtnSetPortLoopbackClicked()
{
    QString portName = ui->lineEditPortNameLoopback->text();
    for(int i = 0; i < portInfoList.size(); i ++){
        if(portName == portInfoList[i].portName){
            try {
                TcpClientThread::instance()->setLoopBackTest(portName, ui->cBoxTestMode->currentIndex(), ui->cBoxTestEnable->currentIndex());

                portInfoList[i].loopback = ui->cBoxTestMode->currentIndex();
                portInfoList[i].loopbackEnable = ui->cBoxTestEnable->currentIndex();
            }
            catch (ServiceException& e) {
                return;
            }
        }
    }

    loopbackTestPortTreeWidgetAddItems(portInfoList);
}

void MainWindow::slotCableTestStartClicked()
{
    QList<PORT_DATA> testList;
    testList.clear();
    auto count = ui->treeWidgetCableTestPort->topLevelItemCount();

    for(int i = 0; i < count; i ++) {
        auto item = ui->treeWidgetCableTestPort->topLevelItem(i);

        if(item->checkState(0) == Qt::Checked) {
            auto data = portInfoList[i];
            testList.append(data);
        }
    }

    if(testList.size() == 0) {
        QMessageBox::information(this, "提示", "未选择端口，请先选择端口，再点击测试按钮！");
        return;
    }

    //后续添加线缆检测流程
}

void MainWindow::slotBtnScreenClicked()
{
    auto minID = 0;
    auto maxID = 0;

    //判断最小值和最大值输入框内是否为空，不为空转换数字，为空则置零
    if(!ui->showMinVlanId->text().isEmpty()) {
        minID = ui->showMinVlanId->text().toInt();
    }
    if(!ui->showMaxVlanId->text().isEmpty()) {
        maxID = ui->showMaxVlanId->text().toInt();

        vlanTableWidgetAddItems(vlanList, minID, maxID);
    }
    else {
        vlanTableWidgetAddItems(vlanList, minID);
    }
}

void MainWindow::slotVlanInfoTableDoubleClicked(QModelIndex index)
{
    auto row = index.row();
    ui->tableWidgetVlanInfo->item(row, 0)->text().toInt();

    slotVlanPortTypeChanged();
}

void MainWindow::slotVlanPortInfoTableDoubleClicked(QModelIndex index)
{
    auto row = index.row();
    auto vlanPortName = ui->tableWidgetVlanPortInfo->item(row, 0)->text();

    auto size = portInfoList.size();
    for(int i = 0; i < size; i ++) {
        if(portInfoList[i].portName == vlanPortName) {
            ui->portNameVLAN->setText(vlanPortName);
            ui->cBoxConnectTypeVLAN->setCurrentText(portInfoList[i].portType);
            ui->portVlanIDVLAN->setText(QString::number(portInfoList[i].portVlanGroup));
            ui->cBoxVlanPortType->setCurrentText(portInfoList[i].vlanPortType);

            QStringList taggedID;
            for(int j = 0; j < portInfoList[i].taggedVlanID.size(); j++) {
                taggedID << QString::number(portInfoList[i].taggedVlanID[j]);
            }
            ui->lineEditVlanTaggedID->setText(taggedID.join(","));
        }
    }
}

void MainWindow::slotVlanPortTypeChanged()
{
    auto row = ui->tableWidgetVlanInfo->currentRow();
    if(row >= 0) {//判断是否有选中行，无选中行不进行操作，有选中行则显示对应端口数据
        auto curID = ui->tableWidgetVlanInfo->item(row, 0)->text().toInt();
        if(ui->rBtnVlanPortUntagged->isChecked()) {
            ui->BtnDeleteVlanPort->setVisible(false);
            vlanPortInfoTableWidgetAddItems(portInfoList, curID, "Untagged");
        }
        else if(ui->rBtnVlanPortTagged->isChecked()) {
            ui->BtnDeleteVlanPort->setVisible(true);
            vlanPortInfoTableWidgetAddItems(portInfoList, curID, "Tagged");
        }
        else if(ui->rBtnVlanPortNonMember->isChecked()) {
            ui->BtnDeleteVlanPort->setVisible(false);
            vlanPortInfoTableWidgetAddItems(portInfoList, curID, "NonMember");
        }
    }
}

void MainWindow::slotBtnModifyPortInfoVLANClicked()
{
    auto size = portInfoList.size();
    auto vlanPortName = ui->portNameVLAN->text();
    for(int i = 0; i < size; i ++) {
        if(vlanPortName == portInfoList[i].portName) {
            if(portInfoList[i].portType != ui->cBoxConnectTypeVLAN->currentText()){
                try {
                    TcpClientThread::instance()->setPortInfo(portInfoList[i]);

                    portInfoList[i].portType = ui->cBoxConnectTypeVLAN->currentText();
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    return;
                }
            }
            if(portInfoList[i].portType == "Access" &&
                    ui->cBoxVlanPortType->currentText() == "Tagged") {
                QMessageBox::information(this, "提示", "该端口类型为Access，不可配置Tag");
                return;
            }

            portInfoList[i].vlanPortType = ui->cBoxVlanPortType->currentText();

            if(portInfoList[i].vlanPortType == "Tagged") {
                if(!portInfoList[i].taggedVlanID.contains(ui->portVlanIDVLAN->text().toInt())) {
                    portInfoList[i].taggedVlanID.append(ui->portVlanIDVLAN->text().toInt());
                }
            }
            else {
                portInfoList[i].portVlanGroup = ui->portVlanIDVLAN->text().toInt();
            }

            try {
                auto curVlanRow = ui->tableWidgetVlanInfo->currentRow();
                auto curVlanID = ui->tableWidgetVlanInfo->item(curVlanRow, 0)->text().toInt();

                TcpClientThread::instance()->vlanAddPort(curVlanID, portInfoList[i].portName);
            }
            catch (ServiceException& e) {
                QMessageBox::information(this, "提示", e.getMessage());
                return;
            }
        }
    }

    slotVlanPortTypeChanged();

    ui->portNameVLAN->clear();
    ui->portVlanIDVLAN->clear();
    ui->lineEditVlanTaggedID->clear();

    portTableWidgetAddItems(portInfoList);
}

void MainWindow::slotCboxVlanPortTypeCurIndexChanged(int index)
{
    ui->label_VlanTaggedId->setVisible(index);
    ui->lineEditVlanTaggedID->setVisible(index);
}

void MainWindow::slotMacInfoTableWidgetItemDoubleClicked(QTableWidgetItem *item)
{
    auto row = item->row();
    auto curMac = ui->tableWidgetMacInfo->item(row, 0)->text();

    MAC_DATA data;
    for(int i = 0; i < macInfoList.size(); i ++) {
        if(macInfoList[i].macAddress == curMac) {
            data = macInfoList[i];
        }
    }

    ui->lineEditMACAddress->setText(data.macAddress);
}

void MainWindow::slotMacVlanIDCurrentChanged(QString currentText)
{
    auto curID = currentText.toInt();

    ui->cBoxMacPort->clear();
    for(int i = 0; i < portInfoList.size(); i ++) {
        if(curID == portInfoList[i].portVlanGroup || portInfoList[i].taggedVlanID.contains(curID)) {
            ui->cBoxMacPort->addItem(portInfoList[i].portName);
        }
    }
}

void MainWindow::slotCheckBoxOldClicked()
{
    ui->sBoxOldTime->setEnabled(ui->cBoxOld->isChecked());
}

void MainWindow::slotMacInfoTableWidgetShow()
{
    if(ui->rBtnAllMac->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList);
    }
    else if(ui->rBtnStaticMacAddress->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList, "Config static");
    }
    else if(ui->rBtnDynamicMacAddress->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList, "Config dynamic");
    }
    else if(ui->rBtnBlackhole->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList, "Blackhole");
    }
    else if(ui->rBtnLearned->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList, "Learned");
    }
    else if(ui->rBtnOther->isChecked()) {
        macInfoTableWidgetAddItems(macInfoList, "Other");
    }
}

void MainWindow::slotCheckBoxScopeCreateClicked()
{
    if(ui->checkBoxScopeCreate->isChecked()) {
        ui->labelCreatePrompt->setText("（例如：1-10）");
    }
    else {
        ui->labelCreatePrompt->setText("（例如：1，3，5，7，9等）");
    }
}

void MainWindow::slotBtnCreateClicked()
{
    QStringList idList;
    idList.clear();

    if(ui->checkBoxScopeCreate->isChecked()) {
        if(ui->lineEditCreate->text().contains("-")) {//判断输入的分隔符--英文分隔符
            idList = ui->lineEditCreate->text().split("-");
        }
        else if(ui->lineEditCreate->text().contains("——")) {//判断输入的分隔符--中文分隔符
            idList = ui->lineEditCreate->text().split("——");
        }
        else {
            QMessageBox::information(this, "提示", "输入的分隔符不符合标准，请修改后重新输入！");
            return;
        }

        auto minID = idList[0].toInt();
        auto maxID = idList[idList.size() - 1].toInt();
        if(minID >= maxID) {
            QMessageBox::information(this, "提示", "输入不符合规则，请重新输入！");
            return;
        }

        qDebug() << "minID : " << minID;
        qDebug() << "maxID : " << maxID;

        for(int i = minID; i <= maxID; i ++) {
            //后续添加插入VLAN ID
            if(!vlanIDIsExist(i)) {
                //后续添加插入VLAN ID

                try {
                    TcpClientThread::instance()->createVlanID(i);

                    VLAN_DATA data;
                    data.ID = i;
                    data.describe = QString("VLAN %1").arg(QString::number(i));
                    vlanList.append(data);
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    break;
                }
            }
        }
    }
    else {
        if(ui->lineEditCreate->text().contains(",")) {//判断输入的分隔符--英文分隔符
            idList = ui->lineEditCreate->text().split(",");
        }
        else if(ui->lineEditCreate->text().contains("，")) {//判断输入的分隔符--中文分隔符
            idList = ui->lineEditCreate->text().split("，");
        }
        else if(ui->lineEditCreate->text().size() <= 3){
            idList = ui->lineEditCreate->text().split("，");
        }
        else {
            QMessageBox::information(this, "提示", "输入的分隔符不符合标准，请修改后重新输入！");
            return;
        }

        qDebug() << idList;

        for(int i = 0; i < idList.size(); i ++) {
            if(!vlanIDIsExist(idList[i].toInt())) {
                //后续添加插入VLAN ID
                try {
                    TcpClientThread::instance()->createVlanID(idList[i].toInt());

                    VLAN_DATA data;
                    data.ID = idList[i].toInt();
                    data.describe = QString("VLAN %1").arg(idList[i]);
                    vlanList.append(data);
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    break;
                }
            }
        }
    }

    ui->lineEditCreate->clear();

    vlanTableWidgetAddItems(vlanList);
}

void MainWindow::slotBtnDeleteVlanPort()
{
    auto row = ui->tableWidgetVlanPortInfo->currentRow();
    if(row < 0) {
        return;
    }

    auto portName = ui->tableWidgetVlanPortInfo->item(row, 0)->text();
    for(int i = 0; i < portInfoList.size(); i ++) {
        if(portInfoList[i].portName == portName) {
            auto curVlanRow = ui->tableWidgetVlanInfo->currentRow();
            auto curVlanID = ui->tableWidgetVlanInfo->item(curVlanRow, 0)->text().toInt();
            for(int j = 0; j < portInfoList[i].taggedVlanID.size(); ) {
                if(curVlanID == portInfoList[i].taggedVlanID[j]) {
                    try {
                        TcpClientThread::instance()->vlanDeletePort(curVlanID, portInfoList[i].portName);
                        portInfoList[i].taggedVlanID.removeAt(j);
                        slotVlanPortTypeChanged();
                    }
                    catch (ServiceException& e) {
                        QMessageBox::information(this, "提示", e.getMessage());
                        return;
                    }

                    return;
                }
                j++;
            }
        }
    }
}

void MainWindow::slotBtnDelectVlanId()
{
    auto curVlanRow = ui->tableWidgetVlanInfo->currentRow();
    auto curVlanID = ui->tableWidgetVlanInfo->item(curVlanRow, 0)->text().toInt();

    try {
        TcpClientThread::instance()->deleteVlanId(curVlanID);

        for(int i = 0; i < vlanList.size(); i ++){
            if(vlanList[i].ID == curVlanID){
                vlanList.removeAt(i);
                break;
            }
        }

        vlanTableWidgetAddItems(vlanList);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
        return;
    }
}
