#include "OnlineTool.h"

#include <QTimer>
#include <QProcess>
#include <QTcpSocket>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

OnlineTool::OnlineTool(QObject *parent)
    : QObject{parent}
{}

OnlineTool::~OnlineTool()
{}

bool OnlineTool::IsOnline(const QString &ip, int timeout)
{
    return ping(ip, timeout);
}

bool OnlineTool::ping(const QString &hostName, int timeout)
{
#ifdef Q_OS_LINUX
QString strArg = "ping -s 1 -c 1% " + hostName;                                 //linux 平台下的格式
#else
QString strArg = "ping " + hostName + " -n 1 -w " + QString::number(timeout) ;  //windows 下的格式
#endif

    QProcess cmd;
    cmd.startCommand(strArg);
    cmd.waitForReadyRead(timeout);
    cmd.waitForFinished(timeout);

    auto result = QString::fromLocal8Bit(cmd.readAll());

    if (result.indexOf("TTL") == -1) {
        return false;
    }

    return true;
}
