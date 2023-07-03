#include "AutoGetChipDataThread.h"

#include <QCoreApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QMessageBox>

AutoGetChipDataThread* autoGetChipDataThread = nullptr;
AutoGetChipDataThread *AutoGetChipDataThread::instance()
{
    static QMutex mutex;
    if (!autoGetChipDataThread) {
        QMutexLocker locker(&mutex);
        if (!autoGetChipDataThread) {
            autoGetChipDataThread = new AutoGetChipDataThread();
        }
    }

    return autoGetChipDataThread;
}

AutoGetChipDataThread::AutoGetChipDataThread()
{
    thread = new QThread();

    myTimer = new QTimer();
    myTimer->moveToThread(thread);
    myTimer->setTimerType(Qt::PreciseTimer);

    connect(thread, SIGNAL(started()), myTimer, SLOT(start()));
    connect(myTimer, SIGNAL(timeout()), this, SLOT(run()));
    connect(thread, SIGNAL(finished()), myTimer, SLOT(stop()));
}

AutoGetChipDataThread::~AutoGetChipDataThread()
{
    delete thread;
    delete myTimer;
}

void AutoGetChipDataThread::setTimeoutInterval(int timeout)
{
    myTimer->setInterval(timeout);
}

void AutoGetChipDataThread::slotStartThread()
{
    if(!thread->isRunning())
    {
        thread->start();
    }
}

void AutoGetChipDataThread::slotCloseThread()
{
    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}

void AutoGetChipDataThread::run()
{
    //后续添加获取芯片信息指令
}
