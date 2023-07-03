#ifndef BURNWRITTHREAD_H
#define BURNWRITTHREAD_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QMessageBox>
#include "qprogressbar.h"

#include "MySerialPort.h"

class BurnWritThread : public QThread
{
    Q_OBJECT
public:
    explicit BurnWritThread(QObject *parent = nullptr);
    ~BurnWritThread();

public:
    void initBurn(MySerialPort* serialPort,
                  QString &fileName,
                  bool mcuFlag,
                  QProgressBar *progressBar);

signals:
    //更新烧写按钮文本信息信号
    void sigUpdateSpiFlashWriteText(QString);

    void sigSendData(int, QByteArray);

public slots:
    //槽函数--开启线程
    void slotStartThread();

    //槽函数--关闭线程
    void slotCloseThread();

    //线程运行函数
    void run();

public:
    bool exitBurnFlash;

private:
    MySerialPort* myPort;

    QString myFilename;
    bool isMcuBin;
    QProgressBar *myProgressBar;
};

#endif // BURNWRITTHREAD_H
