#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FormTestResult.h"
#include "SerialPortThread.h"
#include "TimerThread.h"

#include <QMainWindow>
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

private:
    /**
     * @brief initWidget                初始化窗口部件
     */
    void initWidget();

    void initComboBoxSerialConfig();

    QString getCheckBitsToolTip(const QString& text);

    QString getStopBitsToolTip(const QString& text);

    QString getDataBitsToolTip(const QString& text);

    /**
     * @brief initSerialPortComboBox    初始化串口下拉框
     */
    void initSerialPortComboBox();

    /**
     * @brief initComboBoxFrameLength   初始化各项测试帧长下拉框
     */
    void initComboBoxFrameLength();

    void initTableWidget();

    /**
     * @brief getTestOptions            获取测试选项名称
     * @return                          名称
     */
    QString getTestOptions();

    QSerialPort::Parity getParity(int parity);

    QSerialPort::BaudRate getBaudRate(int baudRate);

    QSerialPort::DataBits getDataBits(int dataBits);

    QSerialPort::StopBits getStopBits(int stopBits);

signals:
    void signalStartSerialPortThread();

    void signalCloseSerialPortThread();

    void signalStartTimerThread();

    void signalCloseTimerThread();

private slots:
    /**
     * @brief slotTestOptionsClicked                        槽函数--测试选项复选按钮点击事件
     */
    void slotTestOptionsClicked();

    /**
     * @brief slotTestModeThroughput                        槽函数--吞吐量测试方式单选按钮点击事件
     */
    void slotTestModeThroughput();

    /**
     * @brief slotTestModeDelay                             槽函数--时延测试方式单选按钮点击事件
     */
    void slotTestModeDelay();

    /**
     * @brief slotTestModePaketLossRate                     槽函数--丢包率测试方式单选按钮点击事件
     */
    void slotTestModePaketLossRate();

    /**
     * @brief slotTestModeBackToBack                        槽函数--背靠背测试方式单选按钮点击事件
     */
    void slotTestModeBackToBack();

    /**
     * @brief on_tBtnSelectFilePath_clicked                 槽函数--选择文件路径按钮点击事件
     */
    void on_tBtnSelectFilePath_clicked();

    /**
     * @brief on_cBoxDelayCom_clicked                       槽函数--时延测试时延补偿复选框点击事件
     */
    void on_cBoxDelayCom_clicked();

    /**
     * @brief on_tBtnSetSpeedThroughput_clicked             槽函数--设置吞吐量测试速率按钮点击事件
     */
    void on_tBtnSetSpeedThroughput_clicked();

    /**
     * @brief on_tBtnSetFrameLengthThroughput_clicked       槽函数--设置吞吐量测试帧长按钮点击事件
     */
    void on_tBtnSetFrameLengthThroughput_clicked();

    /**
     * @brief on_tBtnSetSpeedDelay_clicked                  槽函数--设置时延测试速率按钮点击事件
     */
    void on_tBtnSetSpeedDelay_clicked();

    /**
     * @brief on_tBtnSetFrameLengthDelay_clicked            槽函数--设置时延测试帧长按钮点击事件
     */
    void on_tBtnSetFrameLengthDelay_clicked();

    /**
     * @brief on_tBtnDelayComSet_clicked                    槽函数--设置时延测试时延补偿按钮点击事件
     */
    void on_tBtnDelayComSet_clicked();

    /**
     * @brief on_tBtnSetFrameLengthPaketLossRate_clicked    槽函数--设置丢包率测试按钮点击事件
     */
    void on_tBtnSetFrameLengthPaketLossRate_clicked();

    /**
     * @brief on_tBtnSetSpeedBtoB_clicked           槽函数--设置背靠背测试速率按钮点击事件
     */
    void on_tBtnSetSpeedBtoB_clicked();

    /**
     * @brief on_tBtnSetFrameLengthBtoB_clicked     槽函数--设置背靠背测试帧长按钮点击事件
     */
    void on_tBtnSetFrameLengthBtoB_clicked();

    /**
     * @brief on_BtnOutPut_clicked          槽函数--预览按钮点击事件
     */
    void on_BtnOutPut_clicked();

    /**
     * @brief on_BtnOpenSerial_clicked      槽函数--打开串口按钮点击事件
     */
    void on_BtnOpenSerial_clicked();

    void on_BtnTimerStart_clicked();

    void slotAutoRefresh(int curInt);

    /**
     * @brief on_tBtnSetCalcMode_clicked    槽函数--设置时延测试计算方式
     */
    void on_tBtnSetCalcMode_clicked();

    void on_cBoxOneThroughput_clicked();

    void on_BtnStartThroughput_clicked();

    void on_cBoxOneDelay_clicked();

    void on_cBoxOnePaketLossRate_clicked();

    void on_cBoxOneBackToBack_clicked();

private:
    Ui::MainWindow *ui;
    FormTestResult* formTestResult;
    SerialPortThread* mySerialPortThread;
    TimerThread* timerThread;

    QProgressBar* progressBar;
};
#endif // MAINWINDOW_H
