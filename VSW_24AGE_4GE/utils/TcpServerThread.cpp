#include "TcpServerThread.h"

#include <QMutex>
#include <QMutexLocker>

TcpServerThread* tcpServerThread = nullptr;
TcpServerThread *TcpServerThread::instance()
{
    static QMutex mutex;
    if (!tcpServerThread) {
        QMutexLocker locker(&mutex);
        if (!tcpServerThread) {
            tcpServerThread = new TcpServerThread();
        }
    }

    return tcpServerThread;
}

TcpServerThread::TcpServerThread(QObject *parent)
    : QObject{parent}
    , tcpServer(NULL)
{    
    thread = new QThread();

    connect(thread, SIGNAL(started()), this, SLOT(slotStartSocketConnect()));
}

TcpServerThread::~TcpServerThread()
{}

void TcpServerThread::initNetConnect(int port)
{
    //创建监听套接字
    tcpServer = new QTcpServer(this);//指定父对象 回收空间
    //bind+listen
    tcpServer->listen(QHostAddress::Any, port); //绑定当前网卡所有的ip 绑定端口 也就是设置服务器地址和端口号
}

void TcpServerThread::slotStartThread()
{
    if(!thread->isRunning()) {
        thread->start();
        //qDebug() << "线程开始了，线程号：" << QThread::currentThreadId();
    }
    else {
        //qDebug() << "线程正在运行：" << QThread::currentThreadId();
    }
}

void TcpServerThread::slotStartSocketConnect()
{
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void TcpServerThread::slotNewConnection()
{
    QTcpSocket* tcpSocket;
    //取出连接好的套接字
    tcpSocket = tcpServer->nextPendingConnection();

    //获得通信套接字的控制信息
    auto ip = tcpSocket->peerAddress().toString();   //获取连接的ip地址
    auto port = tcpSocket->peerPort();               //获取连接的端口号

    tcpSocketList.insert(QString("[%1:%2]"), tcpSocket);

    auto temp = QString("[%1:%2] 客户端连接成功").arg(ip, QString::number(port));
    qDebug() << temp;

    //发送连接成功信号
    emit signalNewConnection(temp);

    //接收信息  必须放到连接中的槽函数 不然tcpsocket就是一个野指针
    connect(tcpSocket,
            &QTcpSocket::readyRead,
            [=]() {
                //从通信套接字中取出内容
                auto str = tcpSocket->readAll();

                //后续添加数据处理

                qDebug() << QString("客户端[%1:%2]：%3").arg(ip, QString::number(port), str);
                tcpSocket->write("hello");

                //发送接受信息信号
                //emit signalClientSendData(QString("客户端[%1:%2]：%3").arg(ip, QString::number(port), str));
            });
}

void TcpServerThread::slotCloseThread()
{
    //关闭 通信套接字
    auto list = tcpSocketList.values();
    auto size = list.size();
    for(int i = 0; i < size; i ++) {
        QTcpSocket* tempSocket = list[i];
        tempSocket->disconnectFromHost();
        tempSocket->close();
    }

    if(tcpServer) {
        tcpServer->close();
        disconnect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    }

    //杀死线程
    if(thread->isRunning()) {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}
