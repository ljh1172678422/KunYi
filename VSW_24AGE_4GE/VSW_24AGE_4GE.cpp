#include "VSW_24AGE_4GE.h"
#include "ServiceException.h"
#include "ui_VSW_24AGE_4GE.h"

#include "TcpClientThread.h"

#include <QMessageBox>

VSW_24AGE_4GE::VSW_24AGE_4GE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VSW_24AGE_4GE),
    curPortId(0),
    curPortButton(NULL)
{
    ui->setupUi(this);
    chipInfoList.clear();
    portInfoList.clear();
    vlanInfoList.clear();
    initPortButtonMap();
    initVlanPortMap();
    curChipData = CHIP_DATA();

    ui->groupBoxChipInfo->setVisible(false);

    initPortConnect();
    initStatusWidget();
    initMirrorPortManage();
    initVlanManage();
}

VSW_24AGE_4GE::~VSW_24AGE_4GE()
{
    delete ui;
}

void VSW_24AGE_4GE::initPortConnect()
{
    for(int i = 0; i < 28; i ++){
        QString portName = QString("P%1").arg(QString::number(i + 1));
        int portId = TcpClientThread::instance()->portMapping(portName);

        portButtonMap.value(portId)->setToolButtonId(portId);

        connect(portButtonMap.value(portId), SIGNAL(currentPortButton(int)), this, SLOT(slotToolButtonClicked(int)));
    }
    curPortButton = portButtonMap.value(0);
}

void VSW_24AGE_4GE::initStatusWidget()
{
    //表格添加数据测试, 后续需要从板卡获取数据并显示更新
    {
        for(int i = 0; i < 28; i ++) {
            CHIP_DATA data;
            data.autoNego = i % 2;
            data.linkStatus = i % 2;
            data.linkSpeed = i % 2;
            data.masterSlave = i % 2;
            data.duplex = i % 2;

            data.chipName = QString("P%1").arg(QString::number(i + 1));

            int portId = TcpClientThread::instance()->portMapping(data.chipName);
            if(portId < 4) {
                data.chipType = 0;
            }
            else if(portId >= 4 && portId < 28) {
                data.chipType = 1;
            }

            chipInfoList.append(data);
        }
    }
    setPortButtonStatus(chipInfoList);

    connect(ui->BtnChipModify, SIGNAL(clicked()), this, SLOT(slotBtnChipModifyClicked()));

    connect(ui->rBtnAnegEnable, SIGNAL(clicked()), this, SLOT(slotRadioButtonAnegClicked()));
    connect(ui->rBtnAnegDisable, SIGNAL(clicked()), this, SLOT(slotRadioButtonAnegClicked()));

    connect(ui->rBtnSpeed100M, SIGNAL(clicked()), this, SLOT(slotRadioButtonSpeedClicked()));
    connect(ui->rBtnSpeed1000M, SIGNAL(clicked()), this, SLOT(slotRadioButtonSpeedClicked()));

    connect(ui->rBtnMaster, SIGNAL(clicked()), this, SLOT(slotRadioButtonMasterClicked()));
    connect(ui->rBtnSlave, SIGNAL(clicked()), this, SLOT(slotRadioButtonMasterClicked()));

    connect(ui->rBtnFullDuplex, SIGNAL(clicked()), this, SLOT(slotRadioButtonDuplexClicked()));
    connect(ui->rBtnHalfDuplex, SIGNAL(clicked()), this, SLOT(slotRadioButtonDuplexClicked()));

    connect(ui->rBtnAutoRefreshOpen, SIGNAL(clicked()), this, SLOT(slotAutoRefreshClicked()));
    connect(ui->rBtnAutoRefreshClose, SIGNAL(clicked()), this, SLOT(slotAutoRefreshClicked()));
}

void VSW_24AGE_4GE::initVlanManage()
{
    vlanTableWidgetAddItems(vlanInfoList);

    //VLAN配置信息显示表格样式初始化
    ui->tableWidgetVlanInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    ui->tableWidgetVlanInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetVlanInfo->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetVlanInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    ui->tableWidgetVlanInfo->verticalHeader()->hide();

    //VLAN配置界面--范围创建复选框信号槽连接
    connect(ui->checkBoxScopeCreate, SIGNAL(clicked()), this, SLOT(slotCheckBoxScopeCreateClicked()));
    //VLAN配置界面--创建按钮信号槽连接
    connect(ui->BtnCreate, SIGNAL(clicked()), this, SLOT(slotBtnCreateClicked()));

    //VLAN配置界面--删除VLAN按钮信号槽连接
    connect(ui->BtnDeleteVlanID, SIGNAL(clicked()), this, SLOT(slotBtnDelectVlanId()));

    //VLAN配置界面--VLAN界面VLAN信息表格双击信号槽连接
    connect(ui->tableWidgetVlanInfo, SIGNAL(clicked(QModelIndex)), this, SLOT(slotVlanInfoTableDoubleClicked(QModelIndex)));
}

void VSW_24AGE_4GE::initPortButtonMap()
{
    portButtonMap.clear();
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P1"), ui->tBtnPort1);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P2"), ui->tBtnPort2);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P3"), ui->tBtnPort3);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P4"), ui->tBtnPort4);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P5"), ui->tBtnPort5);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P6"), ui->tBtnPort6);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P7"), ui->tBtnPort7);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P8"), ui->tBtnPort8);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P9"), ui->tBtnPort9);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P10"), ui->tBtnPort10);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P11"), ui->tBtnPort11);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P12"), ui->tBtnPort12);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P13"), ui->tBtnPort13);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P14"), ui->tBtnPort14);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P15"), ui->tBtnPort15);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P16"), ui->tBtnPort16);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P17"), ui->tBtnPort17);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P18"), ui->tBtnPort18);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P19"), ui->tBtnPort19);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P20"), ui->tBtnPort20);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P21"), ui->tBtnPort21);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P22"), ui->tBtnPort22);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P23"), ui->tBtnPort23);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P24"), ui->tBtnPort24);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P25"), ui->tBtnPort25);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P26"), ui->tBtnPort26);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P27"), ui->tBtnPort27);
    portButtonMap.insert(TcpClientThread::instance()->portMapping("P28"), ui->tBtnPort28);
}

void VSW_24AGE_4GE::initVlanPortMap()
{
    vlanPortMap.clear();
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P1"), ui->cBoxPort_1);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P2"), ui->cBoxPort_2);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P3"), ui->cBoxPort_3);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P4"), ui->cBoxPort_4);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P5"), ui->cBoxPort_5);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P6"), ui->cBoxPort_6);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P7"), ui->cBoxPort_7);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P8"), ui->cBoxPort_8);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P9"), ui->cBoxPort_9);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P10"), ui->cBoxPort_10);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P11"), ui->cBoxPort_11);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P12"), ui->cBoxPort_12);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P13"), ui->cBoxPort_13);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P14"), ui->cBoxPort_14);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P15"), ui->cBoxPort_15);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P16"), ui->cBoxPort_16);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P17"), ui->cBoxPort_17);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P18"), ui->cBoxPort_18);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P19"), ui->cBoxPort_19);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P20"), ui->cBoxPort_20);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P21"), ui->cBoxPort_21);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P22"), ui->cBoxPort_22);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P23"), ui->cBoxPort_23);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P24"), ui->cBoxPort_24);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P25"), ui->cBoxPort_25);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P26"), ui->cBoxPort_26);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P27"), ui->cBoxPort_27);
    vlanPortMap.insert(TcpClientThread::instance()->portMapping("P28"), ui->cBoxPort_28);
}

void VSW_24AGE_4GE::initMirrorPortManage()
{
    ui->BtnMirrorPortSet->setEnabled(false);
    ui->BtnSetMonitorPort->setEnabled(false);
    ui->BtnLoopbackSet->setEnabled(false);
    ui->Btn_PVIDSet->setEnabled(false);

    for(int i = 0; i < 28; i ++){
        PORT_DATA data;
        data.portName = QString("P%1").arg(QString::number(i + 1));
        data.mirrorPortEnable = 0;
        data.mirrorPortMonitorDir = 2;
        data.mirrorPortType = 2;

        portInfoList.append(data);
    }
    {
        VLAN_DATA vlanData;
        vlanData.ID = 1;
        vlanData.describe = QString("VLAN %1").arg(QString::number(vlanData.ID));
        vlanData.portList.clear();
        vlanData.portList << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10
                          << 11 << 12 << 13 << 14 << 15 << 16 << 17 << 18 << 19 << 20
                          << 21 << 22 << 23 << 24 << 25 << 26 << 27;
        vlanInfoList.append(vlanData);
    }

    connect(ui->BtnMirrorPortSet, SIGNAL(clicked()), this, SLOT(slotBtnMirrorPortSetClicked()));
    connect(ui->BtnSetMonitorPort, SIGNAL(clicked()), this, SLOT(slotSetMonitorPortClicked()));
    connect(ui->BtnLoopbackSet, SIGNAL(clicked()), this, SLOT(slotBtnLoopbackSetClicked()));
    connect(ui->Btn_PVIDSet, SIGNAL(clicked()), this, SLOT(slotBtnSetPvid()));
}

void VSW_24AGE_4GE::setPortButtonStatus(const QList<CHIP_DATA> &portData)
{
    int size = portData.size();
    for(int i = 0; i < size; i ++){
        int portId = TcpClientThread::instance()->portMapping(portData[i].chipName);

        portButtonMap.value(portId)->setLinkStatus(portData[i].linkStatus);
    }
}

void VSW_24AGE_4GE::setToolButtonStatus(bool status)
{
    for(int i = 0 ; i < 28; i ++){
        if(status){
            if(i == curPortId){
                portButtonMap.value(i)->setDown(status);
            }
            else{
                portButtonMap.value(i)->setDown(!status);
            }
        }
        else{
            portButtonMap.value(i)->setDown(status);
        }
    }
}

void VSW_24AGE_4GE::setComboBoxAllPort()
{
    ui->cBoxAllPort->clear();
    for(int i = 0; i < chipInfoList.size(); i ++){
        ui->cBoxAllPort->addItem(chipInfoList[i].chipName);
    }
    ui->cBoxAllPort->setCurrentIndex(0);
    for(int i = 0; i < portInfoList.size(); i ++){
        if(portInfoList[i].mirrorPortType == 1){
            ui->cBoxAllPort->setCurrentIndex(i);
        }
    }
}

void VSW_24AGE_4GE::setChipProperty()
{
    for(int i = 0; i < chipInfoList.size(); i ++){
        if(curPortId == TcpClientThread::instance()->portMapping(chipInfoList[i].chipName)){
            curChipData = chipInfoList[i];
            if(chipInfoList[i].chipType){
                ui->rBtnMaster->setVisible(true);
                ui->rBtnSlave->setVisible(true);
                ui->rBtnFullDuplex->setVisible(false);
                ui->rBtnHalfDuplex->setVisible(false);
            }
            else{
                ui->rBtnMaster->setVisible(false);
                ui->rBtnSlave->setVisible(false);
                ui->rBtnFullDuplex->setVisible(true);
                ui->rBtnHalfDuplex->setVisible(true);
            }

            setChipAneg(chipInfoList[i].autoNego);
            setChipLinkSpeed(chipInfoList[i].linkSpeed);
            setChipMaster(chipInfoList[i].masterSlave);
            setChipDuplex(chipInfoList[i].duplex);
        }
    }
}

void VSW_24AGE_4GE::setChipAneg(int aneg)
{
    if(aneg){
        ui->rBtnAnegEnable->setChecked(true);
        ui->rBtnAnegDisable->setChecked(false);
    }
    else{
        ui->rBtnAnegEnable->setChecked(false);
        ui->rBtnAnegDisable->setChecked(true);
    }
}

void VSW_24AGE_4GE::setChipLinkSpeed(int linkSpeed)
{
    if(linkSpeed){
        ui->rBtnSpeed1000M->setChecked(false);
        ui->rBtnSpeed100M->setChecked(true);
    }
    else{
        ui->rBtnSpeed1000M->setChecked(true);
        ui->rBtnSpeed100M->setChecked(false);
    }
}

void VSW_24AGE_4GE::setChipMaster(int master)
{
    if(master){
        ui->rBtnMaster->setChecked(true);
        ui->rBtnSlave->setChecked(false);
    }
    else{
        ui->rBtnMaster->setChecked(false);
        ui->rBtnSlave->setChecked(true);
    }
}

void VSW_24AGE_4GE::setChipDuplex(int duplex)
{
    if(duplex){
        ui->rBtnFullDuplex->setChecked(false);
        ui->rBtnHalfDuplex->setChecked(true);
    }
    else{
        ui->rBtnFullDuplex->setChecked(true);
        ui->rBtnHalfDuplex->setChecked(false);
    }
}

void VSW_24AGE_4GE::setSpeedEnable(bool status)
{
    if(curChipData.chipType == 1){
        ui->rBtnSpeed1000M->setEnabled(status);
        ui->rBtnSpeed100M->setEnabled(status);
    }
}

void VSW_24AGE_4GE::vlanTableWidgetAddItems(const QList<VLAN_DATA> &vlanInfoList, int minID, int maxID)
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

bool VSW_24AGE_4GE::vlanIDIsExist(int id)
{
    for(int i = 0; i < vlanInfoList.size(); i ++) {
        if(vlanInfoList[i].ID == id) {
            return true;
        }
    }

    return false;
}

void VSW_24AGE_4GE::vlanPortSetStatus(int vlanID)
{
    QList<int> portIdList;
    int size = vlanInfoList.size();
    for(int i = 0; i < size; i ++){
        if(vlanInfoList[i].ID == vlanID){
            portIdList.clear();
            portIdList.append(vlanInfoList[i].portList);
        }
    }
    qDebug() << portIdList;

    for(int i = 0; i < vlanPortMap.size(); i ++){
        if(portIdList.contains(i)){
            vlanPortMap.value(i)->setChecked(true);
        }
        else{
            vlanPortMap.value(i)->setChecked(false);
        }
    }
}

void VSW_24AGE_4GE::slotToolButtonClicked(int curId)
{
    curPortButton = portButtonMap.value(curId);
    if(curPortId == curPortButton->getToolButtonId()){
        if(ui->groupBoxChipInfo->isVisible()){
            ui->groupBoxChipInfo->setVisible(false);
            setToolButtonStatus(false);

            ui->BtnSetMonitorPort->setEnabled(false);
            ui->BtnMirrorPortSet->setEnabled(false);
            ui->BtnLoopbackSet->setEnabled(false);
            ui->Btn_PVIDSet->setEnabled(false);
        }
        else{
            ui->groupBoxChipInfo->setVisible(true);
            setToolButtonStatus(true);
        }
    }
    else{
        curPortId = curPortButton->getToolButtonId();
        if(!ui->groupBoxChipInfo->isVisible()) {
            ui->groupBoxChipInfo->setVisible(true);
        }
        setToolButtonStatus(true);
    }

    //添加属性信息
    setChipProperty();

    setComboBoxAllPort();

    for(int i = 0; i < portInfoList.size(); i++){
        if(curPortId == TcpClientThread::instance()->portMapping(portInfoList[i].portName)){
            try {
                //获取端口环回测试模式和使能
                TcpClientThread::instance()->getPortLoopback(portInfoList[i]);

                ui->lineEditPortNameLoopback->setText(portInfoList[i].portName);
                ui->cBoxLoopbackMode->setCurrentIndex(portInfoList[i].loopback);
                ui->cBoxLoopbackEnable->setCurrentIndex(portInfoList[i].loopbackEnable);

                //获取端口镜像组属性
                TcpClientThread::instance()->getMirrorGroupPortMonitorDir(portInfoList[i]);
                ui->lineEditPortNameMirror->setText(portInfoList[i].portName);
                ui->cBoxMirrorType->setCurrentIndex(portInfoList[i].mirrorPortType);
                ui->cBoxMonitorPortDir->setCurrentIndex(portInfoList[i].mirrorPortMonitorDir);

                //获取端口PVID
                TcpClientThread::instance()->getPortPVID(portInfoList[i]);
                ui->lineEditPortPVID->setText(QString::number(portInfoList[i].PVID));

                ui->BtnMirrorPortSet->setEnabled(true);
                ui->BtnSetMonitorPort->setEnabled(true);
                ui->BtnLoopbackSet->setEnabled(true);
                ui->Btn_PVIDSet->setEnabled(true);
            }
            catch (ServiceException& e) {
                //QMessageBox::information(this, "提示", e.getMessage());
            }
        }
    }
}

void VSW_24AGE_4GE::slotBtnChipModifyClicked()
{
    //后续添加修改芯片信息指令
    try {
        curChipData.autoNego = ui->rBtnAnegEnable->isChecked() == true ? 1 : 0;
        curChipData.linkSpeed = ui->rBtnSpeed1000M->isChecked() == true ? 1 : 0;
        curChipData.masterSlave = ui->rBtnMaster->isChecked() == true ? 1 : 0;
        curChipData.duplex = ui->rBtnHalfDuplex->isChecked() == true ? 1 : 0;

        TcpClientThread::instance()->setChipInfo(curChipData);
        ui->groupBoxChipInfo->setVisible(false);

        CHIP_DATA chipdata = TcpClientThread::instance()->getChipInfo(curChipData.chipName);

        for(int i = 0; i < chipInfoList.size(); i ++){
            if(chipdata.chipName == chipInfoList[i].chipName){
                chipInfoList[i].autoNego = chipdata.autoNego;
                chipInfoList[i].linkSpeed = chipdata.linkSpeed;
                chipInfoList[i].linkStatus = chipdata.linkStatus;
                chipInfoList[i].masterSlave = chipdata.masterSlave;
                chipInfoList[i].duplex = chipdata.duplex;
            }
        }

        setPortButtonStatus(chipInfoList);
        curChipData = CHIP_DATA();
    }
    catch (ServiceException& e) {
        return;
    }
}

void VSW_24AGE_4GE::slotRadioButtonAnegClicked()
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

void VSW_24AGE_4GE::slotRadioButtonSpeedClicked()
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

void VSW_24AGE_4GE::slotRadioButtonMasterClicked()
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

void VSW_24AGE_4GE::slotRadioButtonDuplexClicked()
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

void VSW_24AGE_4GE::slotAutoRefreshClicked()
{
    if(ui->rBtnAutoRefreshOpen->isChecked()){
        chipInfoList = TcpClientThread::instance()->getChipInfoList();

        setPortButtonStatus(chipInfoList);
        vlanInfoList = TcpClientThread::instance()->getAllVlan();

        vlanTableWidgetAddItems(vlanInfoList);
    }
}

void VSW_24AGE_4GE::slotBtnMirrorPortSetClicked()
{
    QString portName = ui->lineEditPortNameMirror->text();
    if(ui->cBoxMirrorType->currentIndex() == 1){
        QMessageBox::information(this, "提示", "不可修改为监控端口，请重新选择！");
        return;
    }

    try {
        TcpClientThread::instance()->setMirrorGroupPortPreproty(portName,
                                                                ui->cBoxMirrorType->currentIndex(),
                                                                ui->cBoxMirrorPortEnable->currentIndex(),
                                                                ui->cBoxMonitorPortDir->currentIndex());

        ui->cBoxMirrorType->setCurrentIndex(0);
        ui->cBoxMirrorPortEnable->setCurrentIndex(0);
        ui->cBoxMonitorPortDir->setCurrentIndex(0);
        ui->lineEditPortNameMirror->setText("");
        ui->BtnMirrorPortSet->setEnabled(false);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
    }
}

void VSW_24AGE_4GE::slotSetMonitorPortClicked()
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

    ui->BtnSetMonitorPort->setEnabled(false);
}

void VSW_24AGE_4GE::slotBtnLoopbackSetClicked()
{
    QString portName = ui->lineEditPortNameLoopback->text();
    try {
        TcpClientThread::instance()->setLoopBackTest(portName,
                                                     ui->cBoxLoopbackMode->currentIndex(),
                                                     ui->cBoxLoopbackEnable->currentIndex());

        ui->lineEditPortNameLoopback->setText("");
        ui->cBoxLoopbackMode->setCurrentIndex(0);
        ui->cBoxLoopbackEnable->setCurrentIndex(0);
        ui->BtnMirrorPortSet->setEnabled(false);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
    }
}

void VSW_24AGE_4GE::slotBtnSetPvid()
{
    QString portName = ui->lineEditPortNameLoopback->text();
    try {
        TcpClientThread::instance()->setPortPVID(portName, ui->lineEditPortPVID->text().toInt());

        ui->Btn_PVIDSet->setEnabled(false);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
        return;
    }
}

void VSW_24AGE_4GE::slotCheckBoxScopeCreateClicked()
{
    if(ui->checkBoxScopeCreate->isChecked()) {
        ui->labelCreatePrompt->setText("（例如：1-10）");
    }
    else {
        ui->labelCreatePrompt->setText("（例如：1，3，5，7，9等）");
    }
}

void VSW_24AGE_4GE::slotBtnCreateClicked()
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

        for(int i = minID; i <= maxID; i ++) {
            //后续添加插入VLAN ID
            if(!vlanIDIsExist(i)) {
                //后续添加插入VLAN ID

                try {
                    TcpClientThread::instance()->createVlanID(i);
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    break;
                }

                VLAN_DATA data;
                data.ID = i;
                data.describe = QString("VLAN %1").arg(QString::number(i));
                vlanInfoList.append(data);
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

        for(int i = 0; i < idList.size(); i ++) {
            if(!vlanIDIsExist(idList[i].toInt())) {
                //后续添加插入VLAN ID
                try {
                    TcpClientThread::instance()->createVlanID(idList[i].toInt());
                }
                catch (ServiceException& e) {
                    QMessageBox::information(this, "提示", e.getMessage());
                    break;
                }

                VLAN_DATA data;
                data.ID = idList[i].toInt();
                data.describe = QString("VLAN %1").arg(idList[i]);
                vlanInfoList.append(data);
            }
        }
    }

    ui->lineEditCreate->clear();

    vlanTableWidgetAddItems(vlanInfoList);
}

void VSW_24AGE_4GE::slotBtnDelectVlanId()
{
    auto curVlanRow = ui->tableWidgetVlanInfo->currentRow();
    auto curVlanID = ui->tableWidgetVlanInfo->item(curVlanRow, 0)->text().toInt();

    try {
        TcpClientThread::instance()->deleteVlanId(curVlanID);

        for(int i = 0; i < vlanInfoList.size(); i ++){
            if(vlanInfoList[i].ID == curVlanID){
                vlanInfoList.removeAt(i);
                break;
            }
        }

        vlanTableWidgetAddItems(vlanInfoList);
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
        return;
    }
}

void VSW_24AGE_4GE::slotVlanInfoTableDoubleClicked(QModelIndex index)
{
    try {
        auto row = index.row();
        int curVlanId = ui->tableWidgetVlanInfo->item(row, 0)->text().toInt();

        QList<int> portList = TcpClientThread::instance()->getVlanPort(curVlanId);

        for(int i = 0; i < vlanInfoList.size(); i++){
            if(curVlanId == vlanInfoList[i].ID){
                vlanInfoList[i].portList.clear();
                vlanInfoList[i].portList.append(portList);
            }
        }

        vlanPortSetStatus(curVlanId);
    }
    catch (ServiceException& e) {
        return;
    }
}
