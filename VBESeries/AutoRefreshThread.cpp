#include "AutoRefreshThread.h"

AutoRefreshThread::AutoRefreshThread(QObject *parent)
    : QObject{parent}
{
    thread = new QThread();

    myTimer = new QTimer();
    myTimer->moveToThread(thread);
    myTimer->setTimerType(Qt::PreciseTimer);
    myTimer->setInterval(1000);

    connect(thread, SIGNAL(started()), myTimer, SLOT(start()));
    connect(myTimer, SIGNAL(timeout()), this, SLOT(slotAutoRefresh()));
    connect(thread, SIGNAL(finished()), myTimer, SLOT(stop()));
}

AutoRefreshThread::~AutoRefreshThread()
{
    slotStopThread();
}

void AutoRefreshThread::slotStartThread()
{
    if(!thread->isRunning())
    {
        thread->start();
    }
}

void AutoRefreshThread::slotStopThread()
{
    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
    }
}

void AutoRefreshThread::slotAutoRefresh()
{
    emit sigAutoRefresh();
}
