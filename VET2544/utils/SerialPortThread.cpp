#include "SerialPortThread.h"

#include "ServiceException.h"

#include <QCoreApplication>

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
    if(!mySerialPort->isOpen()){
        throw ServiceException("串口未打开，请先打开串口，再发送数据！");
    }

    connect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));

    mySerialPort->write(sendData.data(), sendData.length());

    mySerialPort->waitForBytesWritten(1000);

    while(timeOut < 2000)
    {
        thread->wait(10);
        QCoreApplication::processEvents();


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
    QStringList name = serialName.split(':');
    mySerialPort->setPortName(name[0]);

    mySerialPort->moveToThread(thread);

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

QString SerialPortThread::gerSerialError(int error)
{
    QString result;
    if(error == QSerialPort::SerialPortError::NoError){
        result = "No Error（无错误）";
    }
    else if(error == QSerialPort::SerialPortError::DeviceNotFoundError){
        result = "Device Not Found Error（设备未发现错误）";
    }
    else if(error == QSerialPort::SerialPortError::PermissionError){
        result = "Permission Error（许可错误）";
    }
    else if(error == QSerialPort::SerialPortError::OpenError){
        result = "Open Error（打开错误）";
    }
    else if(error == QSerialPort::SerialPortError::WriteError){
        result = "Write Error（写入错误）";
    }
    else if(error == QSerialPort::SerialPortError::ReadError){
        result = "Read Error（读取错误）";
    }
    else if(error == QSerialPort::SerialPortError::ResourceError){
        result = "Resource Error（资源错误）";
    }
    else if(error == QSerialPort::SerialPortError::UnsupportedOperationError){
        result = "Unsupported Operation Error（不支持的操作错误）";
    }
    else if(error == QSerialPort::SerialPortError::UnknownError){
        result = "Unknown Error（未知错误）";
    }
    else if(error == QSerialPort::SerialPortError::TimeoutError){
        result = "Timeout Error（超时错误）";
    }
    else if(error == QSerialPort::SerialPortError::NotOpenError){
        result = "Not Open Error（未打开错误）";
    }

    return result;
}

void SerialPortThread::slotStartThread()
{
    if(!thread->isRunning())
    {
        thread->start();
        //qDebug() << "线程开始了，线程号：" << QThread::currentThreadId();
    }
    else{
        qDebug() << "线程正在运行：" << QThread::currentThreadId();
    }
}

void SerialPortThread::slotOpenSerialPort()
{
    if(!mySerialPort->open(QIODevice::ReadWrite))
    {
        QString msg = QString("[%1]串口打开失败：%2").arg(mySerialPort->portName(), gerSerialError(mySerialPort->error()));
        throw ServiceException(msg);
    }
}

void SerialPortThread::slotReadSerialPortData()
{
    //qDebug() << "读数据，子线程号：" << QThread::currentThread();
    QByteArray result = mySerialPort->readAll();

    if(!result.isEmpty())
    {
        emit signalReceiveSerialPortData(result);
    }

    result.clear();

    disconnect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));
}

void SerialPortThread::slotCloseThread()
{
    //qDebug()<<"析构函数执行线程："<<QThread::currentThread();

    //关闭串口
    mySerialPort->clear();
    mySerialPort->close();
    //myPort->deleteLater();

    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}
