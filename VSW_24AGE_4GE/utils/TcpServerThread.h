#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QMap>
#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

/**
 * @brief The TcpServerThread class TCP服务端线程工具类
 */
class TcpServerThread : public QObject
{
    Q_OBJECT
public:
    static TcpServerThread* instance();
    explicit TcpServerThread(QObject *parent = nullptr);
    ~TcpServerThread();

    void initNetConnect(int port);

signals:

    void signalNewConnection(QString newConnection);

    void signalClientSendData(QString data);

public slots:
    void slotStartThread();

    void slotStartSocketConnect();

    void slotNewConnection();

    void slotCloseThread();

private:
    QThread* thread;

    //声明两种套接字
    QTcpServer* tcpServer;
    QMap<QString, QTcpSocket*> tcpSocketList;
};

#endif // TCPSERVERTHREAD_H
