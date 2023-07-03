#ifndef AUTOREFRESHTHREAD_H
#define AUTOREFRESHTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>

class AutoRefreshThread : public QObject
{
    Q_OBJECT
public:
    explicit AutoRefreshThread(QObject *parent = nullptr);
    ~AutoRefreshThread();

signals:
    void sigAutoRefresh();

public slots:
    void slotStartThread();

    void slotStopThread();

    void slotAutoRefresh();

private:
    QThread* thread;
    QTimer *myTimer;
};

#endif // AUTOREFRESHTHREAD_H
