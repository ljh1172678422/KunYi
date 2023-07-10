#ifndef VSW_24AGE_4GE_H
#define VSW_24AGE_4GE_H

#include <QMainWindow>
#include <QMap>

#include "DataTypeDef.h"
#include "Widget/CustomToolButton.h"

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QLabel>
#include <QProgressBar>
#include <QCheckBox>

namespace Ui {
class VSW_24AGE_4GE;
}

class VSW_24AGE_4GE : public QMainWindow
{
    Q_OBJECT

public:
    explicit VSW_24AGE_4GE(QWidget *parent = nullptr);
    ~VSW_24AGE_4GE();

private:
    void initPortConnect();

    void initStatusWidget();

    void initVlanManage();

    void initPortButtonMap();

    void initVlanPortMap();

    void initMirrorPortManage();

    void setPortButtonStatus(const QList<CHIP_DATA>& portData);

    void setToolButtonStatus(bool status);

    void setComboBoxAllPort();

    void setChipProperty();

    void setChipAneg(int aneg);

    void setChipLinkSpeed(int linkSpeed);

    void setChipMaster(int master);

    void setChipDuplex(int duplex);

    void setSpeedEnable(bool status);

    /**
     * @brief vlanTableWidgetAddItems       VLAN表格添加内容
     * @param vlanInfoList
     */
    void vlanTableWidgetAddItems(const QList<VLAN_DATA>& vlanInfoList, int minID = 0, int maxID = 4096);

    bool vlanIDIsExist(int id);

    void vlanPortSetStatus(int vlanID);

private slots:
    void slotToolButtonClicked(int curId);

    void slotBtnChipModifyClicked();

    void slotRadioButtonAnegClicked();

    void slotRadioButtonSpeedClicked();

    void slotRadioButtonMasterClicked();

    void slotRadioButtonDuplexClicked();

    void slotAutoRefreshClicked();

    void slotBtnMirrorPortSetClicked();

    void slotSetMonitorPortClicked();

    void slotBtnLoopbackSetClicked();

    void slotBtnSetPvid();

    void slotCheckBoxScopeCreateClicked();

    void slotBtnCreateClicked();

    void slotBtnDelectVlanId();

    /**
     * @brief slotVlanInfoTableDoubleClicked    槽函数--Vlan表格双击事件
     * @param index
     */
    void slotVlanInfoTableDoubleClicked(QModelIndex index);
private:
    Ui::VSW_24AGE_4GE *ui;

    int curPortId;
    CustomToolButton* curPortButton;
    CHIP_DATA curChipData;
    QList<CHIP_DATA> chipInfoList;
    QList<PORT_DATA> portInfoList;
    QList<VLAN_DATA> vlanInfoList;

    QMap<int, CustomToolButton*> portButtonMap;
    QMap<int, QCheckBox*> vlanPortMap;
};

#endif // VSW_24AGE_4GE_H
