#include "MySerialPort.h"
#include "qdebug.h"

#include <QCoreApplication>

MySerialPort::MySerialPort(QObject *parent)
    : QObject{parent}
{
    burnResult.clear();
    isConnectFlag = true;
    serialPortIsOpen = false;
    timeOut = 0;

    thread = new QThread();

    connect(thread, SIGNAL(started()), this, SLOT(SlotOpenSerialPort()));
    //qDebug() << "创建对象初始化线程为：" << QThread::currentThread();
}

MySerialPort::~MySerialPort()
{
    SlotCloseThread();
}

int MySerialPort::serialPortSendData(const QByteArray &sendData)
{
    if(!mySerialPort->isOpen())
    {
        QMessageBox::information(NULL, "提示", "串口未打开，请先打开串口，再发送数据！");
        return -1;
    }

    QString str = sendData.toHex(' ').toUpper();
    qDebug() << "发送数据为：" << str;
    connect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));

    mySerialPort->write(sendData.data(), sendData.count());

    mySerialPort->waitForBytesWritten(1000);
    while(timeOut < 2000)
    {
        thread->wait(10);
        QCoreApplication::processEvents();
        if(!burnResult.isEmpty())
        {
            if(burnResult.contains("52 50")) {
                burnResult.clear();
                return 0;
            }
            else{
                return -1;
            }
        }

        timeOut += 10;
    }

    return -1;
}

int MySerialPort::serialPortSendData(int cmd, const QByteArray &sendData)
{
    if(!mySerialPort->isOpen())
    {
        QMessageBox::information(NULL, "提示", "串口未打开，请先打开串口，再发送数据！");
        return -1;
    }

    int dataSize = sendData.count();

    QByteArray cmdData;
    cmdData.resize(5);

    cmdData[0] = (0x4F);
    cmdData[1] = (0x44);
    cmdData[2] = ((6 + dataSize) >> 8);
    cmdData[3] = (6 + dataSize);
    cmdData[4] = (cmd);
    cmdData.append(sendData);

    //发送指令添加校验值
    QByteArray checkSum;
    checkSum.resize(1);
    checkSum[0] = 0x00;
    for(int i = 0; i < (5 + dataSize); i ++)
    {
        checkSum[0] = checkSum[0] + cmdData[i];
    }
    cmdData.append(checkSum);

    QString str = cmdData.toHex(' ').toUpper();
    qDebug() << "发送数据为：" << str;
    connect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));

    mySerialPort->write(cmdData.data(), cmdData.count());

    mySerialPort->waitForBytesWritten(1000);
    while(timeOut < 2000)
    {
        thread->wait(10);
        QCoreApplication::processEvents();
        if(!burnResult.isEmpty())
        {
            if(burnResult.contains("52 50")) {
                burnResult.clear();
                return 0;
            }
            else{
                return -1;
            }
        }

        timeOut += 10;
    }

    return -1;
}

int MySerialPort::initSerialPort(const QString &serialName)
{
    mySerialPort = new QSerialPort();
    QStringList name = serialName.split(':');
    mySerialPort->setPortName(name[0]);

    mySerialPort->moveToThread(thread);

    mySerialPort->setBaudRate(230400);
    mySerialPort->setParity(QSerialPort::NoParity);
    mySerialPort->setDataBits(QSerialPort::Data8);
    mySerialPort->setStopBits(QSerialPort::OneStop);
    mySerialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(mySerialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "串口打开成功，子线程号：" << QThread::currentThread();
        serialPortIsOpen = true;
    }
    else
    {
        qDebug() << "串口打开失败";
        return -1;
    }

    return 0;
}

void MySerialPort::SlotStartThread()
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

void MySerialPort::SlotOpenSerialPort()
{
}

void MySerialPort::SlotReadSerialPortData()
{
    //qDebug() << "读数据，子线程号：" << QThread::currentThread();
    QByteArray result = mySerialPort->readAll();

    if(!result.isEmpty())
    {
        burnResult = result.toHex(' ').toUpper();
        qDebug() << "串口接收数据为：" << burnResult;
        if(burnResult.contains("52 50")) {
            emit Sig_SendSerialPortData(burnResult);
        }
        else {
            emit Sig_XModemReceiveData(result);
        }
    }

    result.clear();

    disconnect(mySerialPort, SIGNAL(readyRead()), this, SLOT(SlotReadSerialPortData()));
}

void MySerialPort::SlotCloseThread()
{
    //qDebug()<<"析构函数执行线程："<<QThread::currentThread();

    //关闭串口
    mySerialPort->clear();
    mySerialPort->close();
    //myPort->deleteLater();
    serialPortIsOpen = false;

    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}
