#include "UdpThread.h"

#include <QMutex>
#include <QMutexLocker>

#include "ServiceException.h"

UdpThread* udpThread = nullptr;
UdpThread *UdpThread::instance()
{
    static QMutex mutex;
    if (!udpThread) {
        QMutexLocker locker(&mutex);
        if (!udpThread) {
            udpThread = new UdpThread();
        }
    }

    return udpThread;
}

UdpThread::UdpThread(QObject *parent)
    : QObject{parent}
    , udpSocket(NULL)
    , targetHostName("127.0.0.1")
    , targetPort(8081)
{
    thread = new QThread();
    udpSocket = new QUdpSocket();

    connect(thread, SIGNAL(started()), this, SLOT(slotOpenUdpSocket()));
}

void UdpThread::setListenPort(int port)
{
    if(udpSocket) {
        udpSocket->disconnectFromHost();
        udpSocket->close();
        udpSocket->open(QIODevice::ReadWrite);

        disconnect(udpSocket, SIGNAL(readyRead()), this, SLOT(slotReadPendingDatagrams()));
    }

    bool ret = udpSocket->bind(QHostAddress::LocalHost, port);
    if(!ret) {
        throw ServiceException(QString("端口：%2 监听失败").arg(QString::number(port)));
    }
}

void UdpThread::setTargetInfo(const QString &hostName, int port)
{
    this->targetHostName = hostName;
    this->targetPort = port;
}

void UdpThread::udpSendData(QByteArray &sendData)
{
    QHostAddress hostAddress(targetHostName);
    QNetworkDatagram datagram(sendData, hostAddress, targetPort);
    auto ret = udpSocket->writeDatagram(datagram);

    //udpSocket->waitForBytesWritten(1000);

    if(ret == -1) {
        QString msg = QString("[%1:%2]写入数据失败:%3").arg(targetHostName, QString::number(targetPort), udpSocket->errorString());
        throw ServiceException(msg);
    }
}

void UdpThread::processTheDatagram(QByteArray /*datagram*/)
{

}

void UdpThread::slotOpenUdpSocket()
{
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(slotReadPendingDatagrams()));
}

void UdpThread::slotReadPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()) {
        QHostAddress srcAddress;
        quint16 nSrcPort;
        QByteArray datagram;

        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size(), &srcAddress, &nSrcPort);

        qDebug() << "[" + srcAddress.toString() + " " + QString::number(nSrcPort) + "]：" + datagram;

        processTheDatagram(datagram);
    }
}

void UdpThread::slotStartThread()
{
    if(!thread->isRunning()) {
        thread->start();
    }
}

void UdpThread::slotCloseThread()
{
    //关闭套接字
    if(udpSocket) {
        udpSocket->disconnectFromHost();
        udpSocket->close();
        udpSocket->open(QIODevice::ReadWrite);

        disconnect(udpSocket, SIGNAL(readyRead()), this, SLOT(slotReadPendingDatagrams()));
    }


    //杀死线程
    if(thread->isRunning()) {
        thread->quit();
        thread->wait();
    }
}
