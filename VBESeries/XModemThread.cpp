#include "XModemThread.h"

XModemThread::XModemThread(QObject *parent)
    : QThread{parent}
{
    Sender_Packet.resize(3);
    Sender_Data.resize(1024);
    Sender_EOT.resize(1);
    Sender_CheckSum.resize(1);

    Sender_Crc.resize(2);

    resultData.resize(0);

    check_mode = 0;
    Sender_Packet_Number.resize(1);
    Sender_Packet_Number[0] = 0;

    connect(myPort, SIGNAL(Sig_XModemReceiveData(QByteArray)), this, SLOT(slotXModemReceiveData(QByteArray)));
}

XModemThread::~XModemThread()
{
    slotCloseThread();
}

int XModemThread::init_xmodem(MySerialPort *port, QProgressBar *bar, const QString& filename)
{
    Sender_EOT[0] = EOT;

    myPort = port;
    myBar = bar;

    myFileName = filename;

    return 0;
}

void XModemThread::xmodem_send()
{
    int err = 0;
    uint send_count = 128;
    check_mode = wait_c();

    QFile file(myFileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QString message = QString("文件打开失败:%1").arg(file.errorString());
        QMessageBox::information(NULL, "错误", message);
        return;
    }

    QByteArray readData = file.readAll();

    myBar->setMaximum(readData.count());
    myBar->setValue(0);

    int index = 0;
    while(true)
    {
        if(err == 1)
        {            
            index++;

            myBar->setValue(Sender_Data.count());

            //创建临时数组接收从 send_count * index 位置之后的剩余元素
            QByteArray senderData = readData.right(send_count * index);

            //截取开始的PACKAGE_LEN字节元素
            senderData = senderData.left(send_count);

            Sender_Data.clear();
            Sender_Data.append(senderData);

            if(Sender_Data.count() == 0) {
                break;
            }

            Sender_Packet_Number[0] = Sender_Packet_Number[0] + 1;
            err = Send_Packet(Sender_Data, Sender_Packet_Number, Sender_Data.size());
            if(Sender_Data.size() < send_count)
            {
                break;
            }
        }
        else
        {
            //创建临时数组接收从 send_count * index 位置之后的剩余元素
            QByteArray senderData = readData.right(send_count * index);

            //截取开始的PACKAGE_LEN字节元素
            senderData = senderData.left(send_count);

            Sender_Data.clear();
            Sender_Data.append(senderData);

            if(Sender_Data.count() == 0) {
                break;
            }

            Sender_Packet_Number[0] = 1;
            err = Send_Packet(Sender_Data, Sender_Packet_Number, Sender_Data.count());
            if(Sender_Data.count() < send_count)
            {
                break;
            }
        }
    }

    myPort->serialPortSendData(Sender_EOT);
    file.close();
    emit SignalSendXModemEnd();
}

int XModemThread::wait_c()
{
    while(true)
    {
        if(resultData[0] == 0x15)
        {
            return 0;
        }
        else if(resultData[0] == 'C')
        {
            return 1;
        }
    }
}

int XModemThread::Send_Packet(QByteArray data, QByteArray SPN, int length)
{
    if(length == 128) {
        Sender_Packet[0] = SOH;
    }
    else if(length == 1024){
        Sender_Packet[0] = SOX;
    }

    Sender_Packet[1] = SPN[0];
    Sender_Packet[2] = (~SPN[0]);

    myPort->serialPortSendData(Sender_Packet);

    myPort->serialPortSendData(data);

    if(check_mode)
    {
        crc16 check;
        Sender_Crc_us = check.CRC16_ccitt(data, 0, length);
        Sender_Crc[0] = (Sender_Crc_us >> 8) & 0xFF;
        Sender_Crc[1] = Sender_Crc_us & 0xFF;

        myPort->serialPortSendData(Sender_Crc);
    }
    else
    {
        Sender_CheckSum = Cal_CheckSum(data, 0, length);

        myPort->serialPortSendData(Sender_CheckSum);
    }

    return Wait_ACK_NAK(length);
}

QByteArray XModemThread::Cal_CheckSum(QByteArray data, int index, int count)
{
    QByteArray result;
    result.resize(1);
    result[0] = 0x0;

    if(data.size() < (count + index))
        return result;

    for(int i = 0; i < count; i ++)
    {
        result[0] = result[0] + data[index + i];
    }

    return result;
}

int XModemThread::Wait_ACK_NAK(int length)
{
    int ret = 0;

    while(true)
    {
        if(resultData[0] == NAK)
        {
            return length;
        }
        else if(resultData[0] == ACK)
        {
            return 1;
        }
        else
        {

        }
    }

    return ret;
}

QByteArray XModemThread::charBufferToByte(char *buffer)
{
    QByteArray result;
    size_t size = strlen(buffer);
    result.resize(size);

    for(int i = 0; i < size; i ++)
    {
        result[i] = buffer[i];
    }

    return result;
}

void XModemThread::run()
{
    xmodem_send();
}

void XModemThread::slotStartThread()
{
    if(!this->isRunning())
    {
        this->start();
    }
}

void XModemThread::slotCloseThread()
{
    //杀死线程
    if(this->isRunning())
    {
        this->quit();
        this->wait();
        //thread->deleteLater();
    }
}

void XModemThread::slotXModemReceiveData(QByteArray value)
{
    resultData.clear();
    resultData.append(value);
}
