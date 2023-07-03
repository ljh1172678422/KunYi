#ifndef DATATYPEDEF_H
#define DATATYPEDEF_H

#include <QList>
#include <QString>
#include <QMetaType>

typedef enum ReadWtiteType{
    CHIP_INFO = 1,              /* CHIP INFORMATION*/
    PORT_INFO = 2,              /* PORT INFORMATION*/
    MIRROR_INFO = 3,            /* PORT mirroring*/
    VLAN_INFO = 4,              /* VLAN configure*/
    MAC_INFO = 5,               /* MAC configure*/
    LOOPBACK_INFO = 6,          /* LOOPBACK configure*/
}R_W_TYPE;

typedef enum VlanConfigType{
    CREATE_VLAN = 1,
    DELETE_VLAN = 2,
    VLAN_ADD_PORT = 3,
    VLAN_DELETE_PORT = 4,
    VLAN_GET_PORT = 5,
    ALL_VLAN = 6
}VLAN_CONFIG;

//配置芯片信息指令类型
typedef enum ModifyChipProperty
{
    CHIP_PROPERTY_ALL = 15,                         // 修改自协商使能、连接速率、连接状态、保留项属性
    ANEG_AND_STATUS_AND_SPEED_AND_RESERVE = 14,     // 修改自协商使能、连接状态、连接速率、保留项属性
    ANEG_AND_STATUS_AND_RESERVE = 13,               // 修改自协商使能、连接状态、保留项属性
    ANEG_AND_STATUS= 12,                            // 修改自协商使能、连接状态
    ANEG_AND_RESERVE_AND_SPEED = 11,                // 修改自协商使能、连接速率、保留项属性
    ANEG_AND_SPEED = 10,                            // 修改自协商使能、连接速率
    ANEG_AND_RESERVE = 9,                           // 修改自协商使能、保留项属性
    ONLY_ANEG = 8,                                  // ANEG 单独修改自协商
    EXCEPT_ANEG = 7,                                // Link status And Link speed And Reserve 修改连接速率、连接状态、保留项属性
    STATUES_AND_SPEED = 6,                          // Link status And Link speed   修改连接状态、连接速率
    STATUES_AND_RESERVE = 5,                        // Link status And Reserve  修改连接状态、保留项属性
    ONLY_LINK_STATUES = 4,                          // Link status  单独修改连接状态
    RESERVE_AND_SPEED = 3,                          // Reserve And Link speed   修改连接速率、保留项属性
    ONLY_LINK_SPEED = 2,                            // Link speed   单独修改连接速率
    ONLY_RESERVE = 1,                               // Reserve  单独修改保留项属性（普通芯片为主从属性、车载芯片为双工属性）
}CHIP_BIT;

typedef enum FunctionCode{
    READ_CMD = 1,
    WRITE_CMD
}CMD;

//端口信息
typedef struct port_data_info{
    QString portName;                               //端口名称
    int chipID;                                     //芯片ID
    QString portStatus;                             //端口类型
    QString portType;                               //端口连接类型
    QString portSpeed;                              //端口速率
    QString portDuplex;                             //端口双工状态

    QString netLineType = "Normal";                 //网线类型
    QString flowControl = "Disable";                //流量控制
    QString energyMode = "Disable";                 //节能模式
    int maxMacCount = 0;                            //最大MAC地址数 默认为0，代表不限制

    QString broadcast = "";                         //广播风暴控制比  默认为空，格式为type:speed，例如（pps:100M; kbps:100M）
    QString multicast = "";                         //多播风暴控制比  默认为空，格式为type:speed，例如（pps:100M; kbps:100M）
    QString unknownUnicast = "";                    //未知单播风暴控制比  默认为空，格式为type:speed，例如（pps:100M; kbps:100M）

    int portVlanGroup = 0;                          //端口VLAN ID 默认为0  Untagged VLAN ID 号
    QList<int> taggedVlanID;                        //端口所属的 Tagged VLAN ID号集合
    int PVID = 0;                                   //默认为0， 代表无缺省VLAN ID
    int mGroupID = -1;                              //端口镜像组ID 默认为 -1
    QString vlanPortType = "Untagged";              //VLAN端口类型，默认为NonMember:非成员

    int loopback;                                   //环回测试模式：0：内环，1：外环
    int loopbackEnable;                             //环回测试使能：0：Disable，1：Enbale

    int mirrorPortEnable = 0;                       //端口镜像使能  0：Disable，1：Enbale
    int mirrorPortType = 0;                         //镜像端口类型    0:Mirror Port镜像端口；1:Monitor Port监控端口
    int mirrorPortMonitorDir = 0;                   //镜像端口监控方向 0：双向；1：入；2：出
}PORT_DATA;
Q_DECLARE_METATYPE(PORT_DATA);

//芯片状态信息
typedef struct chip_data_info{
    QString chipName;           //芯片名称
    int chipType;               //芯片类型：0：普通，1：车载以太网
    int autoNego;               //使能状态
    int linkStatus;             //连接状态
    int linkSpeed;              //连接速率
    int masterSlave;            //主从类型
    int duplex;                 //工作模式
    int modify = 0;
    CHIP_BIT modifyType;        //修改芯片类型
}CHIP_DATA;
Q_DECLARE_METATYPE(CHIP_DATA);

//端口镜像组信息
typedef struct port_mirror_group_info{
    int ID;
    QString type;
}MGROUP_DATA;
Q_DECLARE_METATYPE(MGROUP_DATA);

//VLAN信息
typedef struct vlan_data_info{
    int ID;
    QString describe;
}VLAN_DATA;
Q_DECLARE_METATYPE(VLAN_DATA);

typedef struct mac_data_info{
    int ID;
    QString macAddress;
    int vlanID;
    QString macType;
    QString portName;
    int oldTime = 0;    //老化时间，为0时说明不老化
}MAC_DATA;
Q_DECLARE_METATYPE(MAC_DATA);

#endif // DATATYPEDEF_H
