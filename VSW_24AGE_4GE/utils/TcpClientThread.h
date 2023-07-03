#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H

#include <QLabel>
#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QProgressBar>
#include "DataTypeDef.h"

/**
 * @brief The TcpClientThread class TCP客户端线程工具类
 */
class TcpClientThread : public QObject
{
    Q_OBJECT
public:
    static TcpClientThread* instance();

    explicit TcpClientThread(QObject *parent = nullptr);
    ~TcpClientThread();

    void setProgressBar(QProgressBar* progressBar);

    /**
     * @brief setTipslabel  设置提示label
     * @param label
     */
    void setTipslabel(QLabel* label);

    /**
     * @brief initNetConnection 初始化网络连接
     * @param ip                目的ip地址
     * @param port              端口号
     */
    void initNetConnection(const QString& ip, int port);

    /**
     * @brief sendData      发送数据
     * @param cmd           指令操作码
     * @param content       指令内容
     * @return              返回操作结果
     */
    QByteArray sendData(int cmd, QByteArray content);

    /**
     * @brief getPortInfo   获取端口信息
     * @param portId        端口ID
     * @return              PORT_DATA结构体数据
     */
    PORT_DATA getPortInfo(int portId);

    /**
     * @brief getPortInfoList   批量获取端口信息
     * @return                  返回端口PORT_DATA结构体数据
     */
    QList<PORT_DATA> getPortInfoList();

    /**
     * @brief setPortInfo   设置端口属性
     * @param data          端口属性信息
     */
    void setPortInfo(const PORT_DATA &data);

    /**
     * @brief setPortInfoList   批量设置端口属性
     * @param dataList
     */
    void setPortInfoList(const QList<PORT_DATA> &dataList);

    /**
     * @brief getChipInfo   获取芯片属性信息
     * @param portID        端口ID
     * @return              CHIP_DATA结构体数据--芯片属性
     */
    CHIP_DATA getChipInfo(int portID);

    int getSpeed(int speed);

    /**
     * @brief getChipInfoList   批量获取芯片属性信息
     * @return  QList<CHIP_DATA>   CHIP_DATA结构体数据--芯片属性
     */
    QList<CHIP_DATA> getChipInfoList();

    /**
     * @brief setChipInfo   设置芯片属性信息
     * @param data          芯片属性信息
     * @param modifyBit
     */
    void setChipInfo(const CHIP_DATA &data);

    void setChipInfoList(const QList<CHIP_DATA> &dataList);

    void getPortLoopback(PORT_DATA& data);

    void getPortLoopback(QList<PORT_DATA>& portList);

    void setLoopBackTest(QString &portName, int loopback, int enable);

    QList<VLAN_DATA> getAllVlan();

    void createVlanID(int vlanId);

    void createVlanId(QList<int> vlanIdList);

    void deleteVlanId(int vlanId);

    void deleteVlanId(QList<int> vlanIdList);

    void vlanAddPort(int vlanId, const QString& portName);

    void vlanDeletePort(int vlanId, const QString& portName);

    void createMacID(int portId);

    void getMirrorGroupPortMonitorDir(PORT_DATA& data);

    void getMirrorGroupPortMointorDir(QList<PORT_DATA>& portList);

    void createMirrorGroupID(int mirrorGroupId);

    /**
     * @brief setMirrorGroupPortPreproty    设置镜像组端口属性
     * @param portName                      端口名称
     * @param portType                      端口类型（0：source, 1：des）
     * @param enable                        使能（0：disable，1：enable）
     * @param monitorDir                    监控方向（0：输入，1：输出，2：双向）
     */
    void setMirrorGroupPortPreproty(QString portName, int portType, int enable = 0, int monitorDir = 0);

    int getPortStatus(QString status);
    QString getPortStatus(int status);

    int getChipStatus(QString status);
    QString getChipStatus(int status);

    int getPortLinkType(QString type);
    QString getPortLinkType(int type);

    int getChipLinkType(QString type);
    QString getChipLinkType(int type);

    int getPortSpeed(QString speed);
    QString getPortSpeed(int speed);

    int getChipSpeed(QString speed);
    QString getChipSpeed(int speed);

    int getPortDuplex(QString duplex);
    QString getPortDuplex(int duplex);

    int getChipMaster(QString status);
    QString getChipMaster(int status);

    int getChipDuplex(QString duplex);
    QString getChipDuplex(int duplex);

signals:
    void signalServerDisconnect();

public slots:
    void slotStartThread();

    void slotStartSocketConnect();

    void slotCloseThread();

    void parseDataInfo();

public:
    /**
     * @brief portMapping   端口映射函数
     * @param portId        端口ID
     * @return              端口名称
     */
    QString portMapping(int portId);

    int portMapping(QString portId);

    QString chipMapping(int chipId);

    char portIdToCmd(int portId);

    int cmdToPortId(char cmd);

private:
    QThread* thread;

    QByteArray sendResult;

    //声明套接字
    QTcpSocket* tcpSocket;

    QString serverIp;
    int serverPort;

    QLabel* m_label;
    QProgressBar* m_progressBar;
};

#endif // TCPCLIENTTHREAD_H
