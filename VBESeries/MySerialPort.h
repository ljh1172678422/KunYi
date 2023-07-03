#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    MySerialPort(QObject *parent = nullptr);
    ~MySerialPort();

public:
    int serialPortSendData(const QByteArray& sendData);

    int serialPortSendData(int cmd, const QByteArray& sendData);

    int initSerialPort(const QString& serialName);

signals:    
    void Sig_SendSerialPortData(QString);

    void Sig_XModemReceiveData(QByteArray);

public slots:
    //槽函数--开启线程
    void SlotStartThread();

    //槽函数--打开串口
    void SlotOpenSerialPort();

    //槽函数--读取串口数据
    void SlotReadSerialPortData();

    //槽函数--关闭线程
    void SlotCloseThread();

public:
    bool serialPortIsOpen;

private:
    QString burnResult;
    QSerialPort * mySerialPort;
    QThread *thread;
    bool isConnectFlag;

    int timeOut;
};

#endif // MYSERIALPORT_H
