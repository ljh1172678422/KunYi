#include "SerialPortThread.h"

#include "ServiceException.h"
#include <QCoreApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QMessageBox>

SerialPortThread* serialPortThread = nullptr;
SerialPortThread *SerialPortThread::instance()
{
    static QMutex mutex;
    if (!serialPortThread) {
        QMutexLocker locker(&mutex);
        if (!serialPortThread) {
            serialPortThread = new SerialPortThread();
        }
    }

    return serialPortThread;
}

SerialPortThread::SerialPortThread(QObject *parent)
    : QObject{parent}
{
    timeOut = 0;

    thread = new QThread();
    mySerialPort = new QSerialPort();

    connect(thread, SIGNAL(started()), this, SLOT(slotOpenSerialPort()));
}

int SerialPortThread::serialPortSendData(const QByteArray &sendData)
{
    if(!mySerialPort->isOpen()) {
        throw ServiceException("串口未打开，请先打开串口，再发送数据！");
    }

    connect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));

    mySerialPort->write(sendData.data(), sendData.size());

    mySerialPort->waitForBytesWritten(1000);

    while(timeOut < 2000) {
        thread->wait(10);
        QCoreApplication::processEvents();

        //后续添加判断通讯返回数据是否正确

        timeOut += 10;
    }

    return -1;
}

int SerialPortThread::serialPortSendData(int cmd, const QByteArray &sendData)
{
    QByteArray cmdData;
    cmdData.clear();

    cmdData.append(cmd);
    cmdData.append(sendData);

    //后续根据协议添加发送

    return 0;
}

void SerialPortThread::initSerialPort(const QString &serialName,
                                     QSerialPort::BaudRate baudRate,
                                     QSerialPort::DataBits dataBits,
                                     QSerialPort::StopBits stopBits,
                                     QSerialPort::Parity parity)
{    
    mySerialPort->moveToThread(thread);

    this->serialName = serialName;

    auto name = serialName.split(':');
    mySerialPort->setPortName(name[0]);

    mySerialPort->setBaudRate(baudRate);
    mySerialPort->setParity(parity);
    mySerialPort->setDataBits(dataBits);
    mySerialPort->setStopBits(stopBits);
    mySerialPort->setFlowControl(QSerialPort::NoFlowControl);
}

bool SerialPortThread::serialIsOpen()
{
    return mySerialPort->isOpen();
}

QString SerialPortThread::getSerialName()
{
    return serialName;
}

QString SerialPortThread::gerSerialError(int error)
{
    QString result;
    if(error == QSerialPort::SerialPortError::NoError) {
        result = "No Error（无错误）";
    }
    else if(error == QSerialPort::SerialPortError::DeviceNotFoundError) {
        result = "Device Not Found Error（设备未发现错误）";
    }
    else if(error == QSerialPort::SerialPortError::PermissionError) {
        result = "Permission Error（许可错误）";
    }
    else if(error == QSerialPort::SerialPortError::OpenError) {
        result = "Open Error（打开错误）";
    }
    else if(error == QSerialPort::SerialPortError::WriteError) {
        result = "Write Error（写入错误）";
    }
    else if(error == QSerialPort::SerialPortError::ReadError) {
        result = "Read Error（读取错误）";
    }
    else if(error == QSerialPort::SerialPortError::ResourceError) {
        result = "Resource Error（资源错误）";
    }
    else if(error == QSerialPort::SerialPortError::UnsupportedOperationError) {
        result = "Unsupported Operation Error（不支持的操作错误）";
    }
    else if(error == QSerialPort::SerialPortError::UnknownError) {
        result = "Unknown Error（未知错误）";
    }
    else if(error == QSerialPort::SerialPortError::TimeoutError) {
        result = "Timeout Error（超时错误）";
    }
    else if(error == QSerialPort::SerialPortError::NotOpenError) {
        result = "Not Open Error（未打开错误）";
    }

    return result;
}

void SerialPortThread::slotOpenSerialPort()
{
    if(!mySerialPort->open(QIODevice::ReadWrite)) {
        auto msg = QString("[%1]串口打开失败：%2").arg(mySerialPort->portName(), gerSerialError(mySerialPort->error()));
        slotCloseThread();
        QMessageBox::information(NULL, "提示", msg);
        return;
    }

    emit signalSerialPortThreadSuccess();
}

void SerialPortThread::slotStartThread()
{
    if(!thread->isRunning()) {
        thread->start();
    }
    else {
        qDebug() << "线程正在运行：" << thread->currentThreadId();
    }
}

void SerialPortThread::slotReadSerialPortData()
{
    auto result = mySerialPort->readAll();

    if(!result.isEmpty()) {
        emit signalReceiveSerialPortData(result);
    }

    disconnect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));
}

void SerialPortThread::slotCloseThread()
{
    //关闭串口
    if(mySerialPort->isOpen()) {
        mySerialPort->clear();
        mySerialPort->close();
    }

    //杀死线程
    if(thread->isRunning()) {
        thread->quit();
        thread->wait();
    }
}
