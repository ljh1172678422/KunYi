#include "TcpClientThread.h"
#include "ServiceException.h"

#include <QMutex>
#include <QMutexLocker>
#include <QMessageBox>
#include <QCoreApplication>

TcpClientThread* tcpClientThread = nullptr;
TcpClientThread *TcpClientThread::instance()
{
    static QMutex mutex;
    if (!tcpClientThread) {
        QMutexLocker locker(&mutex);
        if (!tcpClientThread) {
            tcpClientThread = new TcpClientThread();
        }
    }

    return tcpClientThread;
}

TcpClientThread::TcpClientThread(QObject *parent)
    : QObject{parent}
    , tcpSocket(NULL)
    , m_label(NULL)
    , m_progressBar(NULL)
{
    thread = new QThread();

    connect(thread, SIGNAL(started()), this, SLOT(slotStartSocketConnect()));
}

TcpClientThread::~TcpClientThread()
{}

void TcpClientThread::setProgressBar(QProgressBar *progressBar)
{
    m_progressBar = progressBar;
}

void TcpClientThread::setTipslabel(QLabel *label)
{
    m_label = label;
}

void TcpClientThread::initNetConnection(const QString &ip, int port)
{
    if(nullptr == ip || port == 0) {
        return;
    }

    serverIp = ip;
    serverPort = port;

    //创建监听套接字
    tcpSocket = new QTcpSocket(this);//指定父对象 回收空间
    tcpSocket->connectToHost(serverIp, serverPort);
    if(!tcpSocket->waitForConnected(2000)) {
        ServiceException(QString("[%1::%2]连接失败，请确认IP和端口是否正确！").arg(ip, QString::number(port)));
    }
}

QByteArray TcpClientThread::sendData(int cmd, QByteArray content)
{
    sendResult.clear();
    if(tcpSocket->isOpen()) {
        QByteArray data;
        data.clear();
        data.append(QString::number(cmd).toLocal8Bit());
        data.append(content);       

        tcpSocket->write(data);
        QPalette labelPalette;

        if(!tcpSocket->waitForReadyRead(2000)) {
            labelPalette.setColor(QPalette::WindowText, Qt::red);
            m_label->setPalette(labelPalette);
            m_label->setText("通讯超时！");
            return NULL;
        }

        //线程阻塞，等待有新数据可读取再进行后续操作
        int timeOut = 0;
        while(timeOut < 2000) {
            if(sendResult.isNull()) {
                thread->sleep(10);
                QCoreApplication::processEvents();
            }
            else {
                break;
            }
            timeOut += 10;
        }
    }

    return sendResult;
}

PORT_DATA TcpClientThread::getPortInfo(int portId)
{
    PORT_DATA data;

    QByteArray content;
    content.clear();
    content.append(QString::number(PORT_INFO).toLocal8Bit());
    content.append(portIdToCmd(portId));

    QByteArray result = sendData(READ_CMD, content);
    if(result.isNull()) {
        throw ServiceException("");
    }
    char* cData = result.data();
    data.portName = portMapping(portId);
    data.chipID = portId;
    data.portStatus = getPortStatus(cData[4] - '0');
    data.portType = getPortLinkType(cData[5] - '0');
    data.portSpeed = getPortSpeed(cData[6] - '0');
    data.portVlanGroup = cData[7];
    data.portDuplex = getPortDuplex(cData[8] - '0');
    data.PVID = cData[9];
    data.loopback = cData[10] - '0';
    data.loopbackEnable = cData[11] - '0';

    return data;
}

QList<PORT_DATA> TcpClientThread::getPortInfoList()
{
    QList<PORT_DATA> result;
    result.clear();
    m_progressBar->setMaximum(28);
    for(int i = 0; i < 28; i ++) {
        try {
            PORT_DATA data = getPortInfo(i);
            result.append(data);
            m_progressBar->setValue(i + 1);
        }
        catch (ServiceException& e) {
            return QList<PORT_DATA>();
        }
    }

    return result;
}

void TcpClientThread::setPortInfo(const PORT_DATA &data)
{
    QByteArray content;
    content.clear();

    int portID = portMapping(data.portName);

    int portAutoNego = getPortStatus(data.portStatus);
    int portLinkType = getPortLinkType(data.portType);
    int portLinkSpeed = getPortSpeed(data.portSpeed);
    int portVlanId = data.portVlanGroup;
    int portDuplex = getPortDuplex(data.portDuplex);
    int portPVID = data.PVID;

    content.append(QString::number(PORT_INFO).toLocal8Bit());
    content.append(portIdToCmd(portID));
    content.append('0');
    content.append('0');
    content.append('0');
    content.append(QString::number(portAutoNego).toLocal8Bit());
    content.append(QString::number(portLinkType).toLocal8Bit());
    content.append(QString::number(portLinkSpeed).toLocal8Bit());
    content.append(QString::number(portVlanId).toLocal8Bit());
    content.append(QString::number(portDuplex).toLocal8Bit());
    content.append(QString::number(portPVID).toLocal8Bit());

    //QMessageBox::information(NULL, "tips", content);

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("设置端口属性：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText("配置端口信息成功！");
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("配置端口[%1]失败！").arg(data.portName);
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::setPortInfoList(const QList<PORT_DATA> &dataList)
{
    int size = dataList.size();
    for(int i = 0; i < size; i ++) {
        try {
            setPortInfo(dataList[i]);
        }
        catch (ServiceException &e) {
            throw e;
        }
    }
}

CHIP_DATA TcpClientThread::getChipInfo(int portID)
{
    CHIP_DATA data;
    QByteArray content;
    content.clear();
    content.append(QString::number(CHIP_INFO).toLocal8Bit());
    content.append(portIdToCmd(portID));

    QByteArray result = sendData(READ_CMD, content);
    if(result.isNull()){
        throw ServiceException("");
    }
    data.chipName = portMapping(portID);

    //uint8_t state = result[3]);
    uint8_t aneg = result[4] - '0';
    uint8_t linkStatus = result[5] - '0';
    uint8_t linkSpeed = result[6] - '0';

    data.autoNego = aneg;
    data.linkStatus = linkStatus;
    data.linkSpeed = getSpeed(linkSpeed);

    if(portID >= 0 && portID <= 3) {
        uint8_t duplex = result[7] - '0';
        data.duplex = duplex;
        data.chipType = 0;
    }
    else if(portID >= 4 && portID <= 27) {
        uint8_t master = result[7] - '0';
        data.masterSlave = master;
        data.chipType = 1;
    }

    return data;
}

int TcpClientThread::getSpeed(int speed)
{
    if(speed == 0){
        return 1;
    }
    else if(speed == 1){
        return 0;
    }

    return speed;
}

QList<CHIP_DATA> TcpClientThread::getChipInfoList()
{
    QList<CHIP_DATA> result;
    result.clear();
    m_progressBar->setMaximum(28);
    for(int i = 0; i < 28; i ++) {
        try {
            CHIP_DATA data = getChipInfo(i);
            result.append(data);
            m_progressBar->setValue(i + 1);
        }
        catch (ServiceException& e) {
            return QList<CHIP_DATA>();
        }
    }

    return result;
}

void TcpClientThread::setChipInfo(const CHIP_DATA &data)
{
    QByteArray content;
    content.clear();

    int portID = portMapping(data.chipName);

    uint8_t aneg = data.autoNego;
    uint8_t linkStatus = data.linkStatus;
    uint8_t linkSpeed = data.linkSpeed;
    uint8_t duplex = data.duplex;
    uint8_t master = data.masterSlave;

    uint8_t state = uint8_t(data.modify) << 4;

    state = state + (aneg << 3);
    state = state + (linkStatus << 2);
    state = state + (linkSpeed << 1);

    if(data.chipType == 0) {
        state = state + duplex;
    }
    else if(data.chipType == 1) {
        state = state + master;

    }

    content.append(QString::number(CHIP_INFO).toLocal8Bit());
    content.append(portIdToCmd(portID));
    content.append('0');
    content.append('0');
    content.append('0');
    content.append(state);

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("设置芯片属性：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText("配置芯片信息成功！");
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("配置芯片[%1]失败！").arg(data.chipName);
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::setChipInfoList(const QList<CHIP_DATA> &dataList)
{
    int size = dataList.size();
    for(int i = 0; i < size; i ++) {
        try {
            setChipInfo(dataList[i]);
        }
        catch (ServiceException& e) {
            throw e;
        }
    }
}

void TcpClientThread::getPortLoopback(PORT_DATA &data)
{
    int portId = portMapping(data.portName);
    QByteArray content;
    content.clear();
    content.append(QString::number(LOOPBACK_INFO).toLocal8Bit());
    content.append(portIdToCmd(portId));

    QByteArray result = sendData(READ_CMD, content);
    if(result.isNull()){
        throw ServiceException("");
    }

    data.loopback = result[4] - '0';
    data.loopbackEnable = result[5] - '0';

}

void TcpClientThread::getPortLoopback(QList<PORT_DATA> &portList)
{
    int size = portList.size();
    for(int i = 0; i < size; i ++){
        getPortLoopback(portList[i]);
    }
}

void TcpClientThread::setLoopBackTest(QString& portName, int loopback, int enable)
{
    int portID = portName.split("P")[1].toInt();

    QByteArray content;
    content.append(QString::number(LOOPBACK_INFO).toLocal8Bit());
    content.append(portIdToCmd(portID));
    content.append('0');
    content.append('0');
    content.append('0');
    content.append(QString::number(loopback).toLocal8Bit());
    content.append(QString::number(enable).toLocal8Bit());

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("设置端口环回测试属性：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText("配置端口环回测试成功！");
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("配置端口[%1]环回测试失败！").arg(portMapping(portName));
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

QList<VLAN_DATA> TcpClientThread::getAllVlan()
{
    QList<VLAN_DATA> vlanData;

    QByteArray content;
    content.clear();

    content.append(QString::number(VLAN_INFO).toLocal8Bit());
    content.append('0');
    content.append(QString::number(ALL_VLAN).toLocal8Bit());
    content.append('0');
    content.append('0');

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        return vlanData;
    }
    QPalette labelPalette;
    if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("获取全部VLAN失败！");
        m_label->setText(msg);
        return vlanData;
    }
    else{
        int size = result.size();
        for(int i = 4; i < size; i ++){
            VLAN_DATA data;
            data.ID = result[i];
            data.describe = QString("VLAN %1").arg(result[i]);

            vlanData.append(data);
        }
    }

    return vlanData;
}

void TcpClientThread::createVlanID(int vlanId)
{
    QByteArray content;
    content.append(QString::number(VLAN_INFO).toLocal8Bit());
    content.append('0');
    content.append(QString::number(CREATE_VLAN).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append(vlanId);

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("创建VLAN：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("创建VLAN[%1]成功！").arg(QString::number(vlanId)));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("创建VLAN[%1]失败！").arg(QString::number(vlanId));
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::createVlanId(QList<int> vlanIdList)
{
    for(int i = 0; i < vlanIdList.size(); i ++) {
        try {
            createVlanID(vlanIdList[i]);
        }
        catch (ServiceException& e) {
            throw e;
        }
    }
}

void TcpClientThread::deleteVlanId(int vlanId)
{
    QByteArray content;
    content.append(QString::number(VLAN_INFO).toLocal8Bit());
    content.append('0');
    content.append(QString::number(DELETE_VLAN).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append(vlanId);

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("删除VLAN：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("删除VLAN[%1]成功！").arg(QString::number(vlanId)));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("删除VLAN[%1]失败！").arg(QString::number(vlanId));
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::deleteVlanId(QList<int> vlanIdList)
{
    for(int i = 0; i < vlanIdList.size(); i ++) {
        try {
            deleteVlanId(vlanIdList[i]);
        }
        catch (ServiceException& e) {
            break;
        }
    }
}

void TcpClientThread::vlanAddPort(int vlanId, const QString &portName)
{
    int portId = portName.split('P')[1].toInt();

    QByteArray content;
    content.append(QString::number(VLAN_INFO).toLocal8Bit());
    content.append('0');
    content.append(QString::number(VLAN_ADD_PORT).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append(vlanId);
    content.append(portIdToCmd(portId));

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("VLAN 添加端口：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("VLAN[%1]添加端口[%2]成功！").arg(QString::number(vlanId), portName));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("VLAN[%1]添加端口[%2]失败！").arg(QString::number(vlanId), portName);
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::vlanDeletePort(int vlanId, const QString &portName)
{
    int portId = portName.split('P')[1].toInt();

    QByteArray content;
    content.append(QString::number(VLAN_INFO).toLocal8Bit());
    content.append('0');
    content.append(QString::number(VLAN_DELETE_PORT).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append(vlanId);
    content.append(portIdToCmd(portId));

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("VLAN 删除端口：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("VLAN[%1]删除端口[%2]成功！").arg(QString::number(vlanId), portName));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        QString msg = QString("VLAN[%1]删除端口[%2]失败！").arg(QString::number(vlanId), portName);
        m_label->setText(msg);
        throw ServiceException(msg);
    }
}

void TcpClientThread::createMacID(int portId)
{
    QByteArray content;
    content.append(QString::number(MAC_INFO).toLocal8Bit());
    content.append(portIdToCmd(portId));
    content.append('0');
    content.append('0');
    content.append('0');

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        return;
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("端口[%1]配置MAC成功！").arg(QString::number(portId)));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("端口[%1]配置MAC失败！").arg(QString::number(portId)));
    }
}

void TcpClientThread::getMirrorGroupPortMonitorDir(PORT_DATA &data)
{
    int portId = portMapping(data.portName);

    QByteArray content;
    content.append(QString::number(MIRROR_INFO).toLocal8Bit());
    content.append(QString::number(portId).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append('0');

    auto result = sendData(READ_CMD, content);
    if(result.isNull()){
        return;
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("获取端口[%1]配置成功！").arg(QString::number(portId)));
        return;
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("获取端口[%1]配置失败！").arg(QString::number(portId)));
        return;
    }

    data.mirrorPortType = 2;
    data.mirrorPortEnable = result[4] - '0';
    data.mirrorPortMonitorDir = 2;
}

void TcpClientThread::getMirrorGroupPortMointorDir(QList<PORT_DATA>& portList)
{
    m_progressBar->setMaximum(portList.size());
    int size = portList.size();
    for(int i = 0; i < size; i ++){
        getMirrorGroupPortMonitorDir(portList[i]);
        m_progressBar->setValue(i + 1);
    }
}

void TcpClientThread::createMirrorGroupID(int mirrorGroupId)
{
    QByteArray content;
    content.append(QString::number(MIRROR_INFO).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append('0');
    content.append('0');
    content.append(QString::number(mirrorGroupId).toLocal8Bit());

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("创建镜像组：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText("创建端口镜像组成功！");
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        m_label->setText("创建端口镜像组失败！");
        throw ServiceException("创建端口镜像组失败！");
    }
}

void TcpClientThread::setMirrorGroupPortPreproty(QString portName, int portType, int enable, int monitorDir)
{
    int portId = portMapping(portName);

    QByteArray content;
    content.append(QString::number(MIRROR_INFO).toLocal8Bit());
    content.append(QString::number(portId).toLocal8Bit());
    content.append('0');
    content.append('0');
    content.append('0');
    content.append(QString::number(portType).toLocal8Bit());
    content.append(QString::number(enable).toLocal8Bit());
    content.append(QString::number(monitorDir).toLocal8Bit());

    auto result = sendData(WRITE_CMD, content);
    if(result.isNull()){
        throw ServiceException("镜像组端口配置：通讯超时！");
    }
    QPalette labelPalette;
    if(result == "success") {
        labelPalette.setColor(QPalette::WindowText, Qt::green);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("端口[%1]设置镜像组属性成功！").arg(QString::number(portId)));
    }
    else if(result == "error") {
        labelPalette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(labelPalette);
        m_label->setText(QString("端口[%1]设置镜像组属性失败！").arg(QString::number(portId)));
        throw ServiceException(QString("端口[%1]设置镜像组属性失败！").arg(QString::number(portId)));
    }
}

int TcpClientThread::getPortStatus(QString status)
{
    if(status == "Disable") {
        return 0;
    }
    else if(status == "Enable") {
        return 1;
    }

    return -1;
}

QString TcpClientThread::getPortStatus(int status)
{
    QString result;
    switch (status) {
        case 0:
        {
            result = "Disable";
            break;
        }
        case 1:
        {
            result = "Enable";
            break;
        }
        default:
        {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getChipStatus(QString status)
{
    return getPortStatus(status);
}

QString TcpClientThread::getChipStatus(int status)
{
    return getPortStatus(status);
}

int TcpClientThread::getPortLinkType(QString type)
{
    if(type == "Access") {
        return 0;
    }
    else if(type == "Trunk") {
        return 1;
    }
    else if(type == "Hybrid") {
        return 2;
    }

    return -1;
}

QString TcpClientThread::getPortLinkType(int type)
{
    QString result;
    switch (type) {
        case 0: {
            result = "Access";
            break;
        }
        case 1: {
            result = "Trunk";
            break;
        }
        case 2: {
            result = "Hybrid";
            break;
        }
        default: {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getChipLinkType(QString type)
{
    if(type == "Down") {
        return 0;
    }
    else if(type == "Up") {
        return 1;
    }

    return -1;
}

QString TcpClientThread::getChipLinkType(int type)
{
    QString result;
    switch (type) {
        case 0: {
            result = "Down";
            break;
        }
        case 1: {
            result = "Up";
            break;
        }
        default: {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getPortSpeed(QString speed)
{
    if(speed == "1000M") {
        return 0;
    }
    else if(speed == "100M") {
        return 1;
    }
    else if(speed == "10M") {
        return 2;
    }

    return -1;
}

QString TcpClientThread::getPortSpeed(int speed)
{
    QString result;
    switch (speed) {
        case 0: {
            result = "1000M";
            break;
        }
        case 1: {
            result = "100M";
            break;
        }
        case 2: {
            result = "10M";
            break;
        }
        default: {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getChipSpeed(QString speed)
{
    return getPortSpeed(speed);
}

QString TcpClientThread::getChipSpeed(int speed)
{
    return getPortSpeed(speed);
}

int TcpClientThread::getPortDuplex(QString duplex)
{
    if(duplex == "Full") {
        return 0;
    }
    else if(duplex == "Half") {
        return 1;
    }

    return -1;
}

QString TcpClientThread::getPortDuplex(int duplex)
{
    QString result;
    switch (duplex) {
        case 0: {
            result = "Full";
            break;
        }
        case 1: {
            result = "Half";
            break;
        }
        default: {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getChipMaster(QString status)
{
    if(status == "Slave") {
        return 0;
    }
    else if(status == "Master") {
        return 1;
    }

    return -1;
}

QString TcpClientThread::getChipMaster(int status)
{
    QString result;
    switch (status) {
        case 0: {
            result = "Slave";
            break;
        }
        case 1: {
            result = "Master";
            break;
        }
        default: {
            result = "";
            break;
        }
    }

    return result;
}

int TcpClientThread::getChipDuplex(QString duplex)
{
    return getPortDuplex(duplex);
}

QString TcpClientThread::getChipDuplex(int duplex)
{
    return getPortDuplex(duplex);
}

void TcpClientThread::slotStartThread()
{
    if(!thread->isRunning()) {
        thread->start();
        //qDebug() << "线程开始了，线程号：" << QThread::currentThreadId();
    }
    else {
        //qDebug() << "线程正在运行：" << QThread::currentThreadId();
    }
}

void TcpClientThread::slotStartSocketConnect()
{
    connect(tcpSocket,
            &QTcpSocket::connected,
            [=]() {
                m_label->setText("");
            });

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(parseDataInfo()));
}

void TcpClientThread::slotCloseThread()
{
    //关闭套接字
    if(tcpSocket) {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }

    //杀死线程
    if(thread->isRunning()) {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}

void TcpClientThread::parseDataInfo()
{
    sendResult.clear();
    //获取通信套接字的内容
    sendResult = tcpSocket->readAll();

    if(sendResult == "error") {
        m_label->setText("获取指令执行失败！");
    }
    else if(sendResult == "success") {
        m_label->setText("指令配置成功！");
    }
}

QString TcpClientThread::portMapping(int portId)
{
    QString result;
    switch (portId) {
    case 0:
    case 1:
    case 2:
    case 3: {
        result = QString("P%1").arg(QString::number(portId + 1));
        break;
    }
    case 4:
    case 5:
    case 6:
    case 7: {
        result = QString("P%1").arg(QString::number(portId + 5));
        break;
    }
    case 8:
    case 9:
    case 10:
    case 11: {
        result = QString("P%1").arg(QString::number(portId + 17));
        break;
    }
    case 12:
    case 13:
    case 14:
    case 15: {
        result = QString("P%1").arg(QString::number(portId + 9));
        break;
    }
    case 16:
    case 17:
    case 18:
    case 19: {
        result = QString("P%1").arg(QString::number(portId + 1));
        break;
    }
    case 20:
    case 21:
    case 22:
    case 23: {
        result = QString("P%1").arg(QString::number(portId - 7));
        break;
    }
    case 24:
    case 25: {
        result = QString("P%1").arg(QString::number(portId - 17));
        break;
    }
    case 26:
    case 27: {
        result = QString("P%1").arg(QString::number(portId - 21));
        break;
    }
    default:
        break;
    }

    return result;
}

int TcpClientThread::portMapping(QString portId)
{
    int ID = portId.split('P')[1].toInt();
    switch (ID) {
    case 1:
    case 2:
    case 3:
    case 4: {
        return (ID - 1);
    }
    case 5:
    case 6: {
        return (ID + 21);
    }
    case 7:
    case 8: {
        return (ID + 17);
        break;
    }
    case 9:
    case 10:
    case 11:
    case 12: {
        return (ID - 5);
        break;
    }
    case 13:
    case 14:
    case 15:
    case 16: {
        return (ID + 7);
        break;
    }
    case 17:
    case 18:
    case 19:
    case 20: {
        return (ID - 1);
        break;
    }
    case 21:
    case 22:
    case 23:
    case 24: {
        return (ID - 9);
        break;
    }
    case 25:
    case 26:
    case 27:
    case 28: {
        return (ID - 17);
        break;
    }
    default:
        break;
    }

    return -1;
}

QString TcpClientThread::chipMapping(int chipId)
{
    if(chipId <= 7) {
        return QString("C%1").arg(QString::number(chipId + 1));
    }
    else if(chipId >= 8 && chipId <= 23) {
        return QString("C%1").arg(QString::number(chipId + 5));
    }
    else if(chipId >= 24 && chipId <= 27) {
        return QString("C%1").arg(QString::number(chipId - 15));
    }

    return QString();
}

char TcpClientThread::portIdToCmd(int portId)
{
    if(portId <= 9) {
        return ('0' + portId);
    }
    else {
        return ('0' + portId + 7);
    }

    return portId;
}

int TcpClientThread::cmdToPortId(char cmd)
{
    if(cmd <= '9') {
        return cmd - '0';
    }
    else {
        return cmd - '0' - 7;
    }
}
