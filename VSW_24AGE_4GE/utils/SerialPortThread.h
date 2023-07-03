#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QSerialPort>

/**
 * @brief The SerialPortThread class    串口通讯工具类
 */
class SerialPortThread : public QObject
{
    Q_OBJECT
public:
    static SerialPortThread* instance();

    explicit SerialPortThread(QObject *parent = nullptr);

public:
    int serialPortSendData(const QByteArray& sendData);

    int serialPortSendData(int cmd, const QByteArray& sendData);

    /**
     * @brief initSerialPort        初始化串口信息
     * @param serialName            串口名称
     * @param baudRate              波特率
     * @param dataBits              数据位
     * @param stopBits              停止位
     * @param parity                奇偶校验
     * @return                      返回串口是否开启成功
     */
    void initSerialPort(const QString& serialName,
                       QSerialPort::BaudRate baudRate,
                       QSerialPort::DataBits dataBits,
                       QSerialPort::StopBits stopBits,
                       QSerialPort::Parity parity);

    bool serialIsOpen();

    QString getSerialName();

private:
    QString gerSerialError(int error);

signals:
    void signalReceiveSerialPortData(QString);

    void signalSerialPortThreadSuccess();

public slots:
    void slotOpenSerialPort();

    void slotStartThread();

    void slotReadSerialPortData();

    void slotCloseThread();

private:
    QSerialPort* mySerialPort;
    QThread* thread;

    QString serialName;

    int timeOut;
};

#endif // SERIALPORTTHREAD_H
