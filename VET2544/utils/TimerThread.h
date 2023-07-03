#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <QThread>
#include <QObject>
#include <QTimer>

class TimerThread : public QObject
{
    Q_OBJECT
public:
    explicit TimerThread(QObject *parent = nullptr);

    bool getIsStart() const;

    void setCurInt(int newCurInt);

signals:
    void sigAutoRefresh(int);

public slots:
    void slotStartThread();

    void slotStopThread();

    void slotAutoRefresh();

private:
    QThread* thread;
    QTimer *myTimer;

    int curInt;
    bool isStart;
};

#endif // TIMERTHREAD_H
