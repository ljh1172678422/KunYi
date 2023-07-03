#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMap>
#include <QMenu>
#include <QFile>
#include <QAction>
#include <QMenuBar>
#include <QFileInfo>
#include <QByteArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QButtonGroup>
#include <QContextMenuEvent>

#include "MySerialPort.h"
#include "BurnWritThread.h"
#include "qprogressbar.h"
#include "AutoRefreshThread.h"
#include "DebugPassword.h"
#include "XModemThread.h"

using namespace std;

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief statusBarAddChildren  状态栏添加进度条以及label显示
     */
    void statusBarAddChildren();

    /**
     * @brief setMenuWidgetFocus 设置菜单和窗口的焦点状态
     * @param statu 状态值
     */
    void setMenuWidgetFocus(bool statu);

    /**
     * @brief menuBarAddAction  菜单手动添加Action
     */
    void menuBarAddAction();

    /**
     * @brief setOpenSerialMenuAction   设置打开串口菜单选项
     */
    void setOpenSerialMenuAction();

    /**
     * @brief setCloseSerialMenuAction  设置关闭串口菜单选项
     */
    void setCloseSerialMenuAction(const QString &serialName);

    /**
     * @brief setButtonGroupMember  设置按钮组成员
     */
    void setButtonGroupMember();

    /**
     * @brief serialIsOpen  判断是否已有串口被打开
     */
    bool serialIsOpen(const QMap<QAction *, bool> &map);

    /**
     * @brief send_Cmd 串口发送指令并接收内容
     * @param cmd   指令
     * @param data  发送内容
     * @return  成功返回0，否则返回-1
     */
    int send_Cmd(int cmd, QByteArray data);

    /**
     * @brief calCheckSum 和校验
     * @param data  需要校验的数据
     * @param len   需要校验的数据长度
     * @return  校验值
     */
    QByteArray calCheckSum(QByteArray &data, int len);

    /**
     * @brief hexToAscii    16进制转ASCII
     * @param value         需要转换的数据
     * @return              转换后的数据
     */
    QString hexToAscii(QString& value);

    /**
     * @brief receiveHexToAscii 接收数据转换
     * @param value             需要转换的数据
     * @return                  转换后的数据
     */
    QString receiveHexToAscii(const QString & value);

    /**
     * @brief asciiToHex    ASCII转16进制字符串
     * @param value         需要转换的数据
     * @return              转换后的数据
     */
    QString asciiToHex(const QString& value);

    /**
     * @brief receiveAsciiToHex 接收数据转换
     * @param value             需要转换的数据
     * @return                  转换后的数据
     */
    QString receiveAsciiToHex(const QString & value);

    /**
     * @brief parseHexReceiveData   解析接收到的数据
     * @param value                 需要解析的数据
     */
    void parseHexReceiveData(QString & value);

    /**
     * @brief parseAsciiReceiveData 解析接收到的数据
     * @param value                 需要解析的数据
     */
    void parseAsciiReceiveData(QString& value);

    /**
     * @brief lineEditTextToUint    输入框文本转换无符号整形
     * @param text                  文本内容
     * @param outNum                转换后的数据
     * @return                      转换成功返回true，否则返回false
     */
    bool lineEditTextToUint(const QString& text, uint &outNum);

    /**
     * @brief mdioValueParse        MDIO数据解析
     * @param value                 串口返回数据内容
     */
    void mdioValueParse(const QString& value);

    /**
     * @brief burnFlashDataParse    将BIN的数据写入FLASH返回数据解析
     * @param value                 串口返回数据解析
     */
    void burnFlashDataParse(const QString& value);

    /**
     * @brief parseDeviceResetData  解析复位设备返回数据
     * @param value                 串口返回数据解析
     */
    void parseDeviceResetData(const QString& value);

    /**
     * @brief fpgaValueParse        FPGA数据解析
     * @param value                 串口返回数据内容
     */
    void fpgaValueParse(const QString& value);

    /**
     * @brief writeFpgaValueParse   写入FPGA数据返回解析
     * @param value                 串口返回数据内容
     */
    void writeFpgaValueParse(const QString& value);

    /**
     * @brief getMcuFpgaVersion     获取MCU和FPGA版本
     * @param value                 串口返回数据内容
     */
    void getMcuFpgaVersion(const QString& value);

    /**
     * @brief parseDeviceStatus     解析设备状态
     * @param value                 串口返回数据内容
     */
    void parseDeviceStatus(const QString& value);

    /**
     * @brief parseConfigDevice     解析配置设备返回数据
     * @param value                 串口返回数据内容
     */
    void parseConfigDevice(const QString& value);

    /**
     * @brief parseDeviceConfig     解析设备配置信息
     * @param value                 串口返回数据内容
     */
    void parseDeviceConfig(const QString& value);

    /**
     * @brief parseResetReceive     解析恢复出厂设置返回数据
     * @param value                 串口返回数据内容
     */
    void parseResetReceive(const QString& value);

    /**
     * @brief verify_check_sum
     * @param value
     */
    int verify_check_sum(QList<int> value);
signals:
    /**
     * @brief SignalStartThread     开启串口线程信号
     */
    void SignalStartThread();

    /**
     * @brief SignalCloseThread     关闭串口线程信号
     */
    void SignalCloseThread();

    /**
     * @brief SignalStartBurnThread 开启烧写线程信号
     */
    void SignalStartBurnThread();

    /**
     * @brief SignalCloseBurnThread 关闭烧写线程信号
     */
    void SignalCloseBurnThread();

    /**
     * @brief SignalStartAutoRefreshThread  开启自动刷新设备状态线程信号
     */
    void SignalStartAutoRefreshThread();

    /**
     * @brief SignalCloseAutoRefreshThread  关闭自动刷新设备状态线程信号
     */
    void SignalCloseAutoRefreshThread();

    /**
     * @brief SignalStartSendXModemThread   开启发送XModem线程信号
     */
    void SignalStartSendXModemThread();

    /**
     * @brief SignalCloseSendXModemThread   关闭发送XModem线程信号
     */
    void SignalCloseSendXModemThread();

private slots:
    /**
     * @brief SlotReceiveData   接收数据处理槽函数
     * @param revData   数据
     */
    void SlotReceiveData(QString revData);

    /**
     * @brief slotOpenSerialClicked 处理打开串口点击事件
     */
    void slotOpenSerialClicked(QAction* action);

    /**
     * @brief slotCloseSerialClicked    处理关闭串口点击事件
     * @param action
     */
    void slotCloseSerialClicked(QAction* action);

    /**
     * @brief slotBorderCardSelectMenuClicked   槽函数--板卡选择菜单按钮点击事件
     * @param action
     */
    void slotBorderCardSelectMenuClicked(QAction* action);

    /**
     * @brief slotModeSwitchMenuClicked     槽函数--模式选择菜单按钮点击事件
     * @param action
     */
    void slotModeSwitchMenuClicked(QAction* action);

    /**
     * @brief slotClearReceiveDataClicked 处理清空接收数据按钮点击事件
     */
    void slotClearReceiveDataClicked();

    /**
     * @brief slotSendDataClikced 处理发送按钮点击事件
     */
    void slotSendDataClicked();

    /**
     * @brief slotSelectPathClicked 处理选择路径按钮点击事件
     */
    void slotSelectPathClicked();

    /**
     * @brief slotGetVersionClicked 处理获取版本按钮点击事件
     */
    void slotGetVersionClicked();

    /**
     * @brief slotReceiveDataTypeChanged 槽函数--接收数据类型改变
     */
    void slotReceiveDataTypeChanged();

    /**
     * @brief slotSendDataTypeChanged 槽函数--发送数据类型改变
     */
    void slotSendDataTypeChanged();

    /**
     * @brief slotTextEditReceiveChanged    槽函数--接收数据内容改变
     */
    void slotTextEditReceiveChanged();

    /**
     * @brief slotBtnMdioReadClicked    槽函数--MDIO接口信息读取
     */
    void slotBtnMdioReadClicked();

    /**
     * @brief slotBtnMdioWriteClicked   槽函数--MDIO接口信息写入
     */
    void slotBtnMdioWriteClicked();

    /**
     * @brief slotBtnFpgaReadClicked    槽函数--FPGA接口信息读取
     */
    void slotBtnFpgaReadClicked();

    /**
     * @brief slotBtnFpgaWriteClicked   槽函数--FPGA接口信息写入
     */
    void slotBtnFpgaWriteClicked();

    /**
     * @brief slotBtnBurnClicked    槽函数--烧写按钮点击
     */
    void slotBtnBurnClicked();

    /**
     * @brief slotBurnBtnTextUpdate     槽函数--烧写按钮文本内容更新
     * @param value                     文本数据
     */
    void slotBurnBtnTextUpdate(QString value);

    /**
     * @brief slotBtnSetT1AClicked      槽函数--设置T1-1参数
     */
    void slotBtnSetT1AClicked();

    /**
     * @brief slotBtnSetT1AClicked      槽函数--设置T1-2参数
     */
    void slotBtnSetT1BClicked();

    /**
     * @brief slotBtnSetT1AClicked      槽函数--设置RJ45-1参数
     */
    void slotBtnSetRJ45AClicked();

    /**
     * @brief slotBtnSetT1AClicked      槽函数--设置RJ45-2参数
     */
    void slotBtnSetRJ45BClicked();

    /**
     * @brief slotBtnStatusFreshClicked 槽函数--自动刷新按钮点击
     */
    void slotBtnStatusFreshClicked();

    /**
     * @brief slotAutoRefreshConfigData 槽函数--自动刷新获取配置信息
     */
    void slotAutoRefreshConfigData();

    /**
     * @brief slotDebugWindow           槽函数--调试窗口是否显示
     */
    void slotDebugWindow();

    /**
     * @brief slotDebugDialogShow       槽函数--将调试人员专用控件解封
     */
    void slotDebugDialogShow();

    /**
     * @brief slotSynConfigActionClicked    槽函数--同步配置Action点击事件
     */
    void slotSynConfigActionClicked();

    /**
     * @brief slotDataResetActionClicked    槽函数--恢复出厂设置Action点击事件
     */
    void slotDataResetActionClicked();

    /**
     * @brief slotSendXmodemActionClicked   槽函数--发送Xmodem Action点击事件
     */
    void slotSendXmodemActionClicked();

    /**
     * @brief slotSendXModemEnd             槽函数--发送XModem完毕
     */
    void slotSendXModemEnd();

    /**
     * @brief slotResetBoardActionClicked   槽函数--板卡复位Action点击事件
     */
    void slotResetBoardActionClicked();

    void slotRBtnT1AAnegGroupChanged(bool status);

    void slotRBtnT1BAnegGroupChanged(bool status);

    void slotRBtnRJ45AAnegGroupChanged(bool status);

    void slotRBtnRJ45BAnegGroupChanged(bool status);

private:
    Ui::MainWindow *ui;
    DebugPassword* debugDialog;

    //手动添加菜单Action
    QAction* synConfigAction;       //同步配置 Action
    QAction* dataResetAction;       //恢复出厂设置 Action
    QAction* sendXmodemAction;      //发送Xmodem Action
    QAction* resetBoardAction;      //板卡复位 Action
    QAction* debugAction;           //调试 Action


    QLabel *modeLabel;              //模式Label提示
    QLabel *borderCardLabel;        //板卡Label提示
    QLabel *statusLabel;            //状态Label提示
    QProgressBar *pProgressBar;     //进度条提示

    bool isSerialOpen;              //串口是否打开
    QList<QSerialPortInfo> serialPortList;
    QMap<QAction*, bool> openSerialPorts;

    BurnWritThread *burnWritThread;         //烧写线程类
    bool isBurnWriteThreadStart;
    MySerialPort *mySerialPort;             //串口类，开启线程

    bool isAutoRefresh;                     //是否自动刷新
    AutoRefreshThread* autoRefreshThread;   //自动刷新线程

    bool isSendXModem;                      //是否发送XModem
    XModemThread* mySendXModemThread;       //发送XModem线程

    bool isShowDebugWindow;                 //是否显示调试窗口

    QStringList closeSerialPorts;           //关闭串口列表

    QButtonGroup rBtnSerialRecvGroup;       //串口接收按钮组
    QButtonGroup rBtnSerialSendGroup;       //串口发送按钮组

    QButtonGroup rBtnT1AAnegGroup;          //T1-1 Aneg 按钮组
    QButtonGroup rBtnT1ASpeedGroup;         //T1-1 Speed 按钮组
    QButtonGroup rBtnT1AModeGroup;          //T1-1 Mode 按钮组

    QButtonGroup rBtnT1BAnegGroup;          //T1-2 Aneg 按钮组
    QButtonGroup rBtnT1BSpeedGroup;         //T1-2 Speed 按钮组
    QButtonGroup rBtnT1BModeGroup;          //T1-2 Mode 按钮组

    QButtonGroup rBtnRJ45AAnegGroup;        //RJ45-1 Aneg 按钮组
    QButtonGroup rBtnRJ45ASpeedGroup;       //RJ45-1 Speed 按钮组
    QButtonGroup rBtnRJ45ADuplexGroup;      //RJ45-1 Duplex 按钮组

    QButtonGroup rBtnRJ45BAnegGroup;        //RJ45-2 Aneg 按钮组
    QButtonGroup rBtnRJ45BSpeedGroup;       //RJ45-2 Speed 按钮组
    QButtonGroup rBtnRJ45BDuplexGroup;      //RJ45-2 Duplex 按钮组

};
#endif // MAINWINDOW_H
