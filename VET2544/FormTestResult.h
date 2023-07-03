#ifndef FORMTESTRESULT_H
#define FORMTESTRESULT_H

#include <QWidget>
#include <QLineSeries>
#include <QChartView>
#include <QtCharts>

namespace Ui {
class FormTestResult;
}

class FormTestResult : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestResult(QWidget *parent = nullptr);
    ~FormTestResult();

public:
    /**
     * @brief initThroughput            初始化吞吐量图表模块
     * @param theoryData                理论数据
     * @param testData                  测试数据
     */
    void initThroughput(const QList<QPointF> &theoryData, const QList<QPointF>& testData);

    void initThroughput(const QList<QPointF> &theoryData, const QList<QList<QPointF>>& testData);

    /**
     * @brief showThroughput            显示吞吐量模块
     */
    void showThroughput();

    /**
     * @brief hideThroughput            隐藏吞吐量模块
     */
    void hideThroughput();

    void saveThroughput();

    /**
     * @brief initDelay                 初始化时延模块
     * @param delayType                 时延类型
     * @param testResult                时延测试结果
     */
    void initDelay(const QString& delayType, const QList<QStringList> &testResult);

    /**
     * @brief showDelay                 显示时延模块
     */
    void showDelay();

    /**
     * @brief hideDelay                 隐藏时延模块
     */
    void hideDelay();

    void saveDelay();

    /**
     * @brief initPaketLossRate         初始化丢包率图表信息
     * @param testResult                图表信息Map
     * @param frameLengthList           帧长列表
     */
    void initPaketLossRate(const QMap<QString, QList<QPointF>>& testResult, const QStringList &frameLengthList);

    /**
     * @brief showPaketLossRate         显示丢包率模块
     */
    void showPaketLossRate();

    /**
     * @brief hidePaketLossRate         隐藏丢包率模块
     */
    void hidePaketLossRate();

    /**
     * @brief savePaketLossRate         保存丢包率测试结果至文件
     */
    void savePaketLossRate();

    /**
     * @brief initBackToBack            初始化背靠背图表
     * @param testResult                图表信息
     */
    void initBackToBack(const QList<QStringList> &testResult);

    /**
     * @brief showBackToBack            显示背靠背模块
     */
    void showBackToBack();

    /**
     * @brief hideBackToBack            隐藏背靠背模块
     */
    void hideBackToBack();

    void saveBackToBack();

    void save();

    void setFilepath(const QString &newFilepath);

    void showTabWidget(int index);

    void setTabWidgetEnable(int index, bool status);

private slots:
    void slotBtnOutPutClicked();

private:
    /**
     * @brief initTestResultTabWidget   初始化测试结果界面
     */
    void initTestResultTabWidget();

    /**
     * @brief getIndex                  获取下标--获取目标QString在QStringList中的下标
     * @param frameLength               目标QString
     * @param frameLengthList           目标QList
     * @return                          下标
     */
    int getIndex(const QString& frameLength, const QStringList &frameLengthList);

private:
    Ui::FormTestResult *ui;

    QSize normalSize;
    QSize maxSize;

//    QLineSeries* throughputSeries;      //吞吐量图表
//    QLineSeries* throughputSeriesTest;
//    QChart* throughputChart;
    QChartView* throughputView;

    QMap<QString, QLineSeries*> packgeLossRateSeriesMap;    //丢包率图表
    QMap<QString, QChart*> packgeLossRateChartMap;
    QMap<QString, QChartView*> packgeLossRateViewMap;
};

#endif // FORMTESTRESULT_H
