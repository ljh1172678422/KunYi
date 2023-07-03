#ifndef AUTOGETCHIPDATATHREAD_H
#define AUTOGETCHIPDATATHREAD_H

#include <QTimer>
#include <QObject>
#include <QThread>
#include <QByteArray>
#include <UdpThread.h>

/**
 * @brief The AutoGetChipDataThread class   自动获取芯片信息定时器线程类
 */
class AutoGetChipDataThread : public QObject
{
    Q_OBJECT
public:
    static AutoGetChipDataThread* instance();

    explicit AutoGetChipDataThread();
    ~AutoGetChipDataThread();

    void setTimeoutInterval(int timeout);

public slots:
    void slotStartThread();

    void slotCloseThread();

    void run();

private:
    QThread *thread;
    QTimer  *myTimer;
};

#endif // AUTOGETCHIPDATATHREAD_H
