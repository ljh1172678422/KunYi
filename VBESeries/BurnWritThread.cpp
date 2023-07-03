#include "BurnWritThread.h"

#include <QFile>
#include <QTime>
#include <QString>
#include <QFileInfo>
#include <QDateTime>

BurnWritThread::BurnWritThread(QObject *parent)
    : QThread{parent}
{}

BurnWritThread::~BurnWritThread()
{
    slotCloseThread();
}

void BurnWritThread::initBurn(MySerialPort* serialPort, QString &fileName, bool mcuFlag, QProgressBar *progressBar)
{
    myPort = serialPort;
    myFilename = fileName;
    isMcuBin = mcuFlag;
    myProgressBar = progressBar;
}

void BurnWritThread::run()
{
    int PACKAGE_LEN = 0x100;

    QFileInfo *fileInfo = new QFileInfo(myFilename);
    if(!fileInfo->exists())
    {
        QString message = QString("Firmware file %1 does not exist!").arg(myFilename);
        QMessageBox::information(NULL, "提示", message);
        return;
    }

    uint offSet = 0;
    if(isMcuBin)
    {
        offSet = 0x80000000;
        if(fileInfo->size() > 0x8000)
        {
            QString message = QString("Firmware file %1 over size!").arg(myFilename);
            QMessageBox::information(NULL, "提示", message);
            return;
        }
    }
    else
    {
        if(fileInfo->size() > 0x400000 || (fileInfo->size() < 0x8000))
        {
            QString message = QString("Firmware file %1 over size!").arg(myFilename);
            QMessageBox::information(NULL, "提示", message);
            return;
        }
    }

    QDateTime startTime = QDateTime::currentDateTime();
    QFile *file = new QFile(myFilename);
    if(!file->open(QIODevice::ReadOnly))
    {
        QString message = QString("文件打开失败:%1").arg(file->errorString());
        QMessageBox::information(NULL, "错误", message);
        return;
    }
    QByteArray firmware = file->readAll();

    int write_times = (int)(firmware.count() / PACKAGE_LEN);
    int last_write_len = (int)(firmware.count() % PACKAGE_LEN);

    if(last_write_len != 0){
        write_times++;
    }
    else{
        last_write_len = PACKAGE_LEN;
    }

    myProgressBar->setMaximum(write_times);
    myProgressBar->setValue(0);
    int i;
    for(i = 0; i < write_times - 1; i ++)
    {
        if(exitBurnFlash)
        {
            goto SPIFLASH_UPDATE_FAIL;
        }

        QByteArray content;
        content.clear();
        content.append((offSet + i) >> 24);
        content.append((offSet + i) >> 16);
        content.append((offSet + i) >> 8);
        content.append((offSet + i));

        //创建临时数组接收从 PACKAGE_LEN * i 位置之后的剩余元素
        QByteArray tempByte = firmware.right(PACKAGE_LEN * i);

        //截取开始的PACKAGE_LEN字节元素
        tempByte = tempByte.left(PACKAGE_LEN);

        content.append(tempByte);

        int ret = myPort->serialPortSendData(0x65, content);
        if(ret == -1){
            goto SPIFLASH_UPDATE_FAIL;
        }

        myProgressBar->setValue(i+1);
    }

    //最后一包
    {
        QByteArray content;
        content.clear();
        content.append((offSet + i) >> 24);
        content.append((offSet + i) >> 16);
        content.append((offSet + i) >> 8);
        content.append((offSet + i));

        //创建临时数组接收从 PACKAGE_LEN * i 位置之后的剩余元素
        QByteArray tempByte = firmware.right(PACKAGE_LEN * i);

        //截取开始的PACKAGE_LEN字节元素
        tempByte = tempByte.left(last_write_len);

        content.append(tempByte);

        int ret = myPort->serialPortSendData(0x65, content);
        if(ret == -1){
            goto SPIFLASH_UPDATE_FAIL;
        }
        myProgressBar->setValue(i+1);
    }

    //写入文件长度
    {
        QByteArray content;
        content.clear();
        content.append((isMcuBin ? 1 : 0));
        content.append(fileInfo->size() >> 24);
        content.append(fileInfo->size() >> 16);
        content.append(fileInfo->size() >> 8);
        content.append(fileInfo->size());

        int ret = myPort->serialPortSendData(0x64, content);
        if(ret == -1){
            goto SPIFLASH_UPDATE_FAIL;
        }

        QDateTime endTime = QDateTime::currentDateTime();
        double time = startTime.msecsTo(endTime) / 1000.0;
        QString message = QString(": 耗时 %1 秒!").arg(time);
        emit sigUpdateSpiFlashWriteText(message);
        myProgressBar->setTextVisible(true);
        file->close();
        return;
    }

    SPIFLASH_UPDATE_FAIL:
    if(!exitBurnFlash)
    {
        QDateTime endTime = QDateTime::currentDateTime();
        double time = startTime.msecsTo(endTime) / 1000.0;
        QString message = QString("Burn Fail, take about %1 seconds").arg(time);
        QMessageBox::information(NULL, "提示", message);
    }

    QDateTime endTime = QDateTime::currentDateTime();
    double time = startTime.msecsTo(endTime) / 1000.0;
    QString message = QString(": 耗时 %1 秒!").arg(time);
    emit sigUpdateSpiFlashWriteText(message);
    myProgressBar->setTextVisible(true);
    file->close();
    return;
}

void BurnWritThread::slotStartThread()
{
    if(!this->isRunning())
    {
        this->start();
    }
}

void BurnWritThread::slotCloseThread()
{
    //杀死线程
    if(this->isRunning())
    {
        this->quit();
        this->wait();
        //thread->deleteLater();
    }
}
