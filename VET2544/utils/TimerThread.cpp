#include "TimerThread.h"

TimerThread::TimerThread(QObject *parent)
    : QObject{parent}
    , curInt(0)
    , isStart(false)
{
    thread = new QThread();
    //parent->moveToThread(thread);

    myTimer = new QTimer();
    myTimer->moveToThread(thread);
    myTimer->setTimerType(Qt::PreciseTimer);
    myTimer->setInterval(100);

    connect(thread, SIGNAL(started()), myTimer, SLOT(start()));
    connect(myTimer, SIGNAL(timeout()), this, SLOT(slotAutoRefresh()));
    connect(thread, SIGNAL(finished()), myTimer, SLOT(stop()));
}

void TimerThread::slotStartThread()
{
    if(!thread->isRunning())
    {
        thread->start();
        isStart = true;
    }
}

void TimerThread::slotStopThread()
{
    //杀死线程
    if(thread->isRunning())
    {
        thread->quit();
        thread->wait();
        //thread->deleteLater();
        isStart = false;
    }
}

void TimerThread::slotAutoRefresh()
{
    curInt++;
    emit sigAutoRefresh(curInt);
}

void TimerThread::setCurInt(int newCurInt)
{
    curInt = newCurInt;
}

bool TimerThread::getIsStart() const
{
    return isStart;
}
