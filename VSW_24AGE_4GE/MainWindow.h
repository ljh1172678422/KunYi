#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DataTypeDef.h"
#include "FormNetConfig.h"
#include "FormSerialPortConfig.h"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QLabel>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    /**
     * @brief signalStopSerialPortThread    信号--停止串口通讯线程信号
     */
    void signalStopSerialPortThread();

    /**
     * @brief signalCloseNetThread      信号--停止网络通讯线程信号
     */
    void signalCloseNetThread();

private:
    /**
     * @brief initWidget    初始化窗口部件
     */
    void initWidget();

    /**
     * @brief initStatusBar 初始化窗口状态栏
     */
    void initStatusBar();

    /**
     * @brief initTabWidget 初始化窗口TabWidget
     */
    void initTabWidget();

    /**
     * @brief initStatusTableWidget 初始化状态显示表格
     */
    void initStatusTableWidget();

    /**
     * @brief initPortManagetWidget 初始化端口管理窗口
     */
    void initPortManagetWidget();

    /**
     * @brief initPortMirrorWidget  初始化端口镜像窗口
     */
    void initPortMirrorWidget();

    /**
     * @brief initLoopbackTestWidget    初始化环回测试窗口
     */
    void initLoopbackTestWidget();

    /**
     * @brief initCableTestWidget   初始化线缆检测窗口
     */
    void initCableTestWidget();

    /**
     * @brief initVLANConfigWidget  初始化VLAN配置窗口
     */
    void initVLANConfigWidget();

    /**
     * @brief initMACConfigWidget   初始化MAC配置窗口
     */
    void initMACConfigWidget();

    /**
     * @brief addStatusTableWidgetItems   状态显示表格添加表项
     * @param chipDataList
     */
    void statusTableWidgetAddItems(const QList<CHIP_DATA>& chipDataList);

    /**
     * @brief statusTableWidgetAddItem  状态显示表格添加表项
     * @param tableWidget
     * @param chipData
     */
    void statusTableWidgetAddItem(QTableWidget *tableWidget, const CHIP_DATA& chipData);

    /**
     * @brief portTableWidgetAddItems   端口信息表格添加表项
     * @param portDataList
     */
    void portTableWidgetAddItems(const QList<PORT_DATA>& portDataList);

    /**
     * @brief portMirrorGroupTableWidgetAddItems    端口镜像组表格添加表项
     * @param mGroupInfoList
     */
    void portMirrorGroupTableWidgetAddItems(const QList<PORT_DATA>& portInfoList);

    /**
     * @brief mirrorGroupPortTreeWidgetAddItems     镜像组端口树窗口添加内容
     * @param portInfoList
     */
    void mirrorGroupPortTreeWidgetAddItems(const QList<PORT_DATA>& portInfoList, int mGroupID = 0);

    /**
     * @brief vlanTableWidgetAddItems       VLAN表格添加内容
     * @param vlanInfoList
     */
    void vlanTableWidgetAddItems(const QList<VLAN_DATA>& vlanInfoList, int minID = 0, int maxID = 10240);

    /**
     * @brief vlanPortInfoTableWidgetAddItems   VLAN 端口信息表格添加内容
     * @param portList
     * @param vlanID
     * @param vlanPortType
     */
    void vlanPortInfoTableWidgetAddItems(const QList<PORT_DATA>& portList, int vlanID = 0, QString vlanPortType = "Untagged");

    /**
     * @brief vlanPortInfoTableWidgetAddItem    VLAN 端口信息表格添加行
     * @param tableWidget
     * @param data
     */
    void vlanPortInfoTableWidgetAddItem(QTableWidget* tableWidget, const PORT_DATA& data);

    /**
     * @brief loopbackTestPortTreeWidgetAddItems    环回测试端口树结构添加子项目
     * @param portList
     */
    void loopbackTestPortTreeWidgetAddItems(const QList<PORT_DATA>& portList);

    /**
     * @brief cableTestPortTreeWidgetAddItems       线缆测试端口树结构添加子项目
     * @param portList
     */
    void cableTestPortTreeWidgetAddItems(const QList<PORT_DATA>& portList);

    /**
     * @brief macInfoTableWidgetAddItems        mac信息表格添加子项目
     * @param macInfoList
     */
    void macInfoTableWidgetAddItems(const QList<MAC_DATA>& macInfoList, const QString& macType = "");

    /**
     * @brief setTableWidgetItemBackGround  表格Item设置背景颜色
     * @param item                          item
     * @param color                         颜色
     */
    void setTableWidgetItemBackGround(QTableWidgetItem* item, QColor& color);

    bool vlanIDIsExist(int id);

    void setChipPreproty(const CHIP_DATA& data);

    void setSpeedEnable(bool status);

private slots:
    /**
     * @brief slotMenuSerialTriggered   槽函数--串口配置菜单槽函数
     * @param action
     */
    void slotMenuSerialTriggered(QAction* action);

    /**
     * @brief slotMenuNetTriggered      槽函数--网络配置菜单槽函数
     * @param action
     */
    void slotMenuNetTriggered(QAction* action);

    /**
     * @brief slotMenuStyleSheetTriggered   槽函数--窗口样式菜单槽函数
     * @param action
     */
    void slotMenuStyleSheetTriggered(QAction* action);

    /**
     * @brief slotTabWidgetCurrentChanged   槽函数--窗口Tab Widget更改当前页事件
     * @param index
     */
    void slotTabWidgetCurrentChanged(int index);

    void slotTcpClientDisConnect();

    /**
     * @brief slotTableWidgetItemDoubleClicked
     * @param item
     */
    void slotTableWidgetItemDoubleClicked(QTableWidgetItem* item);    

    void slotRadioButtonAnegClicked();

    void slotRadioButtonSpeedClicked();

    void slotRadioButtonMasterClicked();

    void slotRadioButtonDuplexClicked();

    /**
     * @brief slotBtnChipModifyClicked
     */
    void slotBtnChipModifyClicked();

    /**
     * @brief slotSerialPortThreadSuccess           槽函数--串口打开成功
     */
    void slotSerialPortThreadSuccess();

    /**
     * @brief slotCurrentNetStatusTips              槽函数--当前网络连接提示
     * @param status
     */
    void slotCurrentNetStatusTips(QString status);

    /**
     * @brief slotTableWidgetPortInfoDoubleClicked  槽函数--端口信息表格双击事件
     * @param item
     */
    void slotTableWidgetPortInfoDoubleClicked(QTableWidgetItem* item);

    /**
     * @brief slotPortInfoCurrentTextChanged 槽函数--端口信息表格中的下拉框更改当前选中事件
     * @param row
     */
    void slotPortInfoCurrentTextChanged(int row);

    /**
     * @brief slotBtnPackUpClicked              槽函数--收起按钮点击事件
     */
    void slotBtnPackUpClicked();

    /**
     * @brief slotBtnModifyPortInfoClicked      槽函数--修改端口信息按钮点击事件
     */
    void slotBtnModifyPortInfoClicked();

    /**
     * @brief slotCheckBoxPVIDClicked           槽函数--PVID复选框按钮点击事件
     */
    void slotCheckBoxPVIDClicked();

    /**
     * @brief slotCreatePortMirrorGroupClicked  槽函数--创建端口镜像组按钮点击事件
     */
    void slotCreatePortMirrorGroupClicked();

    void slotBtnSetMonitorPortClicked();

    void slotTableWidgetMirrorPortChanged(int row);

    void slotListWidgetLoopbackClicked(QListWidgetItem* item);

    void slotListWidgetLoopbackDoubleClicked(QListWidgetItem* item);

    /**
     * @brief slotLoopbackTestStartClicked      槽函数--环回测试按钮点击事件
     */
    void slotBtnSetPortLoopbackClicked();

    /**
     * @brief slotCableTestStartClicked         槽函数--线缆检测测试按钮点击事件
     */
    void slotCableTestStartClicked();

    /**
     * @brief slotBtnScreenClicked              槽函数--确定筛选按钮点击事件
     */
    void slotBtnScreenClicked();

    /**
     * @brief slotVlanInfoTableDoubleClicked    槽函数--Vlan表格双击事件
     * @param index
     */
    void slotVlanInfoTableDoubleClicked(QModelIndex index);

    /**
     * @brief slotVlanPortInfoTableDoubleClicked    槽函数--VLAN配置表格双击事件
     * @param index
     */
    void slotVlanPortInfoTableDoubleClicked(QModelIndex index);

    /**
     * @brief slotVlanPortTypeChanged           槽函数--VLAN端口类型更改事件
     */
    void slotVlanPortTypeChanged();

    /**
     * @brief slotBtnModifyPortInfoVLANClicked  槽函数--修改VLAN ID所属端口信息按钮点击事件
     */
    void slotBtnModifyPortInfoVLANClicked();

    void slotCboxVlanPortTypeCurIndexChanged(int index);

    void slotMacInfoTableWidgetItemDoubleClicked(QTableWidgetItem* item);

    /**
     * @brief slotMacVlanIDCurrentChanged       槽函数--MAC VLAN ID下拉框 更改事件
     * @param currentText
     */
    void slotMacVlanIDCurrentChanged(QString currentText);

    /**
     * @brief slotCheckBoxOldClicked            槽函数--老化复选框点击事件
     */
    void slotCheckBoxOldClicked();

    /**
     * @brief slotMacInfoTableWidgetShow        槽函数--MAC地址表格显示
     */
    void slotMacInfoTableWidgetShow();

    /**
     * @brief slotCheckBoxScopeCreateClicked    槽函数--范围查询复选按钮点击事件
     */
    void slotCheckBoxScopeCreateClicked();

    /**
     * @brief slotBtnCreateClicked              槽函数--VLAN ID创建按钮点击事件
     */
    void slotBtnCreateClicked();

    /**
     * @brief slotBtnDeleteVlanPort             槽函数--VLAN 删除端口按钮点击事件
     */
    void slotBtnDeleteVlanPort();

    void slotBtnDelectVlanId();

private:
    Ui::MainWindow *ui;

    CHIP_DATA curChipData;

    QLabel* statusBarTipLabel;
    QLabel* instructionExecTipLabel;
    QProgressBar* m_progressBar;

    FormNetConfig* formNetConfig;
    FormSerialPortConfig* formSerialPortConfig;

    QList<VLAN_DATA> vlanList;
    QList<CHIP_DATA> chipDataList;
    QList<PORT_DATA> portInfoList;
    QList<MGROUP_DATA> mGroupInfoList;
    QList<MAC_DATA> macInfoList;
};
#endif // MAINWINDOW_H
