#ifndef DATATYPEDEF_H
#define DATATYPEDEF_H

#include <QString>
#include <QStringList>

//吞吐量测试配置信息
typedef struct ThroughputConfigData{
    int sendMode;                   //发送模式：0：定时模式；1：定量模式
    int sendTime;                   //定时模式下的发送时长
    int sendFrameCount;             //定量模式下的发送帧数量
    int unitSpeed;                  //初始速度
    QString testFrameLength;        //测试帧长

    int testTime;                   //测试时长 单位：微妙
}TTL_DATA;

//时延测试配置信息
typedef struct DelayConfigData{
    int sendMode;                   //发送模式：0：定时模式；1：定量模式
    int sendTime;                   //定时模式下的发送时长
    int sendFrameCount;             //定量模式下的发送帧数量
    int unitSpeed;                  //初始速度
    QString testFrameLength;        //测试帧长
    int calcMode;                   //计算方式：0：先进先出；1：先进后出；2：后进先出；3：后进后出
    int delayCompensation;          //时延补偿

    int testTime;                   //测试时长 单位：微妙
}SY_DATA;

//丢包率测试配置信息
typedef struct PaketLossRateConfigData{
    int sendMode;                   //发送模式：0：定时模式；1：定量模式
    int sendTime;                   //定时模式下的发送时长
    int sendFrameCount;             //定量模式下的发送帧数量

    QString testFrameLength;        //测试帧长

    int testTime;                   //测试时长 单位：微妙
}DBL_DATA;

//背靠背测试配置信息
typedef struct BackToBackConfigData{
    int sendMode;                   //发送模式：0：定时模式；1：定量模式
    int sendTime;                   //定时模式下的发送时长
    int sendFrameCount;             //定量模式下的发送帧数量
    int unitSpeed;                  //初始速度
    QString testFrameLength;        //测试帧长

    int testTime;                   //测试时长 单位：微妙
}BDB_DATA;

#endif // DATATYPEDEF_H
