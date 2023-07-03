#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QNetworkDatagram>

/**
 * @brief The UdpThread class   UDP通讯线程工具类
 */
class UdpThread : public QObject
{
    Q_OBJECT
public:
    static UdpThread* instance();

    explicit UdpThread(QObject *parent = nullptr);

    void setListenPort(int port);

    void setTargetInfo(const QString &hostName, int port);

    void udpSendData(QByteArray& sendData);

private:
    void processTheDatagram(QByteArray datagram);

signals:

private slots:
    void slotOpenUdpSocket();

    void slotReadPendingDatagrams();

    void slotStartThread();

    void slotCloseThread();

private:
    QThread* thread;
    QUdpSocket* udpSocket;

    QString targetHostName;
    int targetPort;
};

#endif // UDPTHREAD_H
