#ifndef ONLINETOOL_H
#define ONLINETOOL_H

#include <QObject>

/**
 * @brief The OnlineTool class  判断hostname是否在线工具类
 */
class OnlineTool : public QObject
{
    Q_OBJECT
public:
    explicit OnlineTool(QObject *parent = nullptr);
    ~OnlineTool();

public:
    bool IsOnline(const QString& ip, int timeout = 1000);

private:
    bool ping(const QString& hostName, int timeout = 1000);
};

#endif // ONLINETOOL_H
