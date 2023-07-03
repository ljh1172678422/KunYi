#include "FormTestResult.h"
#include "ui_FormTestResult.h"

#include "PDFHelper.h"
#include <QApplication>


FormTestResult::FormTestResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestResult)
{
    ui->setupUi(this);

    normalSize = this->geometry().size();
    maxSize = this->screen()->size();

    initTestResultTabWidget();
}

FormTestResult::~FormTestResult()
{
    delete ui;
}

void FormTestResult::initThroughput(const QList<QPointF> &theoryData, const QList<QPointF> &testData)
{
    //吞吐量图表初始化
    QLineSeries* throughputSeries = new QLineSeries();
    throughputSeries->setName("理论速率");

    QLineSeries* throughputSeriesTest = new QLineSeries();
    throughputSeriesTest->setName("实际速率");

    throughputSeries->clear();
    throughputSeriesTest->clear();

    throughputSeries->append(theoryData);
    throughputSeries->setPointLabelsClipping(false);
    throughputSeries->setPointLabelsVisible(true);
    throughputSeries->setPointLabelsFormat("@yPoint");
    QFont *font = new QFont();
    font->setPointSize(8);
    throughputSeries->setPointLabelsFont(*font);

    throughputSeriesTest->append(testData);
    throughputSeriesTest->setPointLabelsClipping(false);
    throughputSeriesTest->setPointLabelsVisible(true);
    throughputSeriesTest->setPointLabelsFormat("@yPoint");
    QFont *fontTest = new QFont();
    fontTest->setPointSize(8);
    throughputSeriesTest->setPointLabelsFont(*fontTest);

    QChart* throughputChart = new QChart();

    throughputChart->addSeries(throughputSeries);
    throughputChart->addSeries(throughputSeriesTest);

    throughputChart->createDefaultAxes();
    QList<QAbstractAxis*> axisX = throughputChart->axes(Qt::Vertical);
    axisX[0]->setRange(0, 16000);
    QList<QAbstractAxis*> axisY = throughputChart->axes(Qt::Horizontal);
    axisY[0]->setRange(0, 1600);

    //修改说明样式  设置线条对象的说明文字 格式大小颜色 对齐位置等 就是指标签
    throughputChart->legend()->setVisible(true);
    throughputChart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    throughputChart->legend()->setColor(QColor(222, 233, 251));//设置颜色

    throughputView->setChart(throughputChart);
}

void FormTestResult::initThroughput(const QList<QPointF> &theoryData, const QList<QList<QPointF> > &testData)
{
    QChart* throughputChart = new QChart();

    QLineSeries* throughputSeries = new QLineSeries();
    throughputSeries->setName("理论速率");
    throughputSeries->clear();
    throughputSeries->append(theoryData);
    throughputSeries->setPointLabelsClipping(false);
    throughputSeries->setPointLabelsVisible(true);
    throughputSeries->setPointLabelsFormat("@yPoint");
    throughputChart->addSeries(throughputSeries);

    int count = testData.size();
    for(int i = 0; i < count; i ++){
        QLineSeries* testSeries = new QLineSeries();
        testSeries->setName(QString("测试速率%1").arg(QString::number(i+1)));
        testSeries->clear();
        testSeries->append(testData[i]);
        testSeries->setPointLabelsClipping(false);
        testSeries->setPointLabelsVisible(true);
        testSeries->setPointLabelsFormat("@yPoint");
        throughputChart->addSeries(testSeries);
    }

    throughputChart->createDefaultAxes();
    QList<QAbstractAxis*> axisX = throughputChart->axes(Qt::Vertical);
    axisX[0]->setRange(0, 16000);
    QList<QAbstractAxis*> axisY = throughputChart->axes(Qt::Horizontal);
    axisY[0]->setRange(0, 1600);

    //修改说明样式  设置线条对象的说明文字 格式大小颜色 对齐位置等 就是指标签
    throughputChart->legend()->setVisible(true);
    throughputChart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    throughputChart->legend()->setColor(QColor(222, 233, 251));//设置颜色

    throughputView = new QChartView(throughputChart, ui->gBoxThroughput);
    throughputView->setChart(throughputChart);

    //格栅布局 必须要这一步，如果没有进行布局，那么整个chart只有一个单元那么大
    QGridLayout* m_mainLayout= new QGridLayout();

    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
    m_mainLayout->addWidget(throughputView);

    //最终设置格栅布局，不可缺
    ui->gBoxThroughput->setLayout(m_mainLayout);
}

void FormTestResult::showThroughput()
{
    ui->gBoxThroughput->show();
}

void FormTestResult::hideThroughput()
{
    ui->gBoxThroughput->hide();
}

void FormTestResult::saveThroughput()
{
    PDFHelper::Instance()->insertContent("吞吐量测试结果：");

    PDFHelper::Instance()->insertQChartView(throughputView, "吞吐量测试结果折线图");
}

void FormTestResult::initDelay(const QString &delayType, const QList<QStringList> &testResult)
{
    QString delayTypeTips = QString("时延类型：%1").arg(delayType);
    ui->labelDelayType->setText(delayTypeTips);

    ui->tableWidgetDelay->clearContents();
    ui->tableWidgetDelay->setRowCount(0);

    int size = testResult.size();
    for(int i = 0; i < size; i ++){
        QStringList contents = testResult[i];
        int curRow = ui->tableWidgetDelay->rowCount();
        ui->tableWidgetDelay->insertRow(curRow);

        for(int column = 0; column < contents.size(); column++){
            ui->tableWidgetDelay->setItem(curRow, column, new QTableWidgetItem(contents[column]));
            ui->tableWidgetDelay->item(curRow, column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
}

void FormTestResult::showDelay()
{
    ui->gBoxDelay->show();
}

void FormTestResult::hideDelay()
{
    ui->gBoxDelay->hide();
}

void FormTestResult::saveDelay()
{
    PDFHelper::Instance()->insertContent("时延测试结果：");

    QString tableTitle = ui->labelDelayType->text();
    PDFHelper::Instance()->insertTable(10, 80, 1, ui->tableWidgetDelay, tableTitle);
}

void FormTestResult::initPaketLossRate(const QMap<QString, QList<QPointF>>& testResult, const QStringList& frameLengthList)
{
    //丢包率图表初始化
    QList<QString> frameLength = testResult.keys();
    for(int i = 0; i < frameLength.size(); i ++)
    {
        if(packgeLossRateSeriesMap.contains(frameLength[i])){//判断是否已经创建过该折线图
            packgeLossRateSeriesMap[frameLength[i]]->clear();
            packgeLossRateSeriesMap[frameLength[i]]->append(testResult[frameLength[i]]);
        }
        else {//新建折线图
            QLineSeries *series = new QLineSeries();
            series->append(testResult[frameLength[i]]);
            series->setPointLabelsClipping(false);
            series->setPointLabelsVisible(true);
            series->setPointLabelsFormat("@yPoint");
            QFont *fontTest = new QFont();
            fontTest->setPointSize(8);
            series->setPointLabelsFont(*fontTest);

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->createDefaultAxes();

            QList<QAbstractAxis*> axisX = chart->axes(Qt::Vertical);
            axisX[0]->setTitleText("丢包率");
            axisX[0]->setRange(0, 1.0);

            QList<QAbstractAxis*> axisY = chart->axes(Qt::Horizontal);
            axisY[0]->setTitleText("负载");
            axisY[0]->setRange(0, 1.2);

            //修改说明样式  设置线条对象的说明文字 格式大小颜色 对齐位置等 就是指标签
            QString title = QString("帧长%1的丢包率测试结果").arg(frameLength[i]);
            chart->setTitle(title);
            chart->legend()->setVisible(false);
            chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
            chart->legend()->setColor(QColor(222,233,251));//设置颜色

            QChartView *chartView = new QChartView(chart, ui->gBoxLossPackgeRate);

            packgeLossRateChartMap.insert(frameLength[i], chart);
            packgeLossRateViewMap.insert(frameLength[i], chartView);
            packgeLossRateSeriesMap.insert(frameLength[i], series);

            //格栅布局 必须要这一步，如果没有进行布局，那么整个chart只有一个单元那么大
            QGridLayout* m_mainLayout = (QGridLayout*)(ui->gBoxLossPackgeRate->layout());
            if(m_mainLayout == nullptr){
                m_mainLayout = new QGridLayout();
            }

            int index = getIndex(frameLength[i], frameLengthList);
            if((frameLengthList.size() % 2) == 0){
                if(index < (frameLengthList.size() / 2)){
                    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
                    m_mainLayout->addWidget(chartView, 0, index);
                }
                else{
                    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
                    m_mainLayout->addWidget(chartView, 1, index-(frameLengthList.size() / 2));
                }
            }
            else{
                if(index < (frameLengthList.size() / 2 + 1)){
                    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
                    m_mainLayout->addWidget(chartView, 0, index);
                }
                else{
                    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
                    m_mainLayout->addWidget(chartView, 1, index-(frameLengthList.size() / 2 + 1));
                }
            }

            //最终设置格栅布局，不可缺
            ui->gBoxLossPackgeRate->setLayout(m_mainLayout);
        }
    }
}

void FormTestResult::showPaketLossRate()
{
    ui->gBoxLossPackgeRate->show();
}

void FormTestResult::hidePaketLossRate()
{
    ui->gBoxLossPackgeRate->hide();
}

void FormTestResult::savePaketLossRate()
{
    PDFHelper::Instance()->insertContent("丢包率测试结果：");
    QGridLayout* layout = (QGridLayout*)ui->gBoxLossPackgeRate->layout();

    for(int column = 0; column < layout->count(); column++){
        if(column < layout->columnCount()){
            PDFHelper::Instance()->insertQChartView((QChartView*)(layout->itemAtPosition(column/layout->columnCount(), column)->widget()), "");
        }
        else{
            PDFHelper::Instance()->insertQChartView((QChartView*)(layout->itemAtPosition(column/layout->columnCount(), column - layout->columnCount())->widget()), "");
        }
    }
}

void FormTestResult::initBackToBack(const QList<QStringList> &testResult)
{
    ui->tableWidgetBackToBack->clearContents();
    ui->tableWidgetBackToBack->setRowCount(0);

    int size = testResult.size();
    for(int i = 0; i < size; i ++){
        QStringList contents = testResult[i];
        int curRow = ui->tableWidgetBackToBack->rowCount();
        ui->tableWidgetBackToBack->insertRow(curRow);

        for(int column = 0; column < contents.size(); column++){
            ui->tableWidgetBackToBack->setItem(curRow, column, new QTableWidgetItem(contents[column]));
            ui->tableWidgetBackToBack->item(curRow, column)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
}

void FormTestResult::showBackToBack()
{
    ui->gBoxBackToBack->show();
}

void FormTestResult::hideBackToBack()
{
    ui->gBoxBackToBack->hide();
}

void FormTestResult::saveBackToBack()
{
    PDFHelper::Instance()->insertContent("背靠背测试结果：");

    PDFHelper::Instance()->insertTable(10, 80, 1, ui->tableWidgetBackToBack, "");
}

void FormTestResult::save()
{
    if(!ui->lineEditFilePath->text().isEmpty()){
        if(ui->gBoxThroughput->isVisible()){
            saveThroughput();
        }
        if(ui->gBoxDelay->isVisible()){
            saveDelay();
        }
        if(ui->gBoxLossPackgeRate->isVisible()){
            savePaketLossRate();
        }
        if(ui->gBoxBackToBack->isVisible()){
            saveBackToBack();
        }
        PDFHelper::Instance()->save();
    }
}

void FormTestResult::initTestResultTabWidget()
{
    ui->tableWidgetBackToBack->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);              //先自适应宽度
    ui->tableWidgetBackToBack->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);  //然后设置要根据内容使用宽度的列
    ui->tableWidgetBackToBack->setSelectionBehavior(QAbstractItemView::SelectRows);                         //整行选中的方式
    ui->tableWidgetBackToBack->setEditTriggers(QAbstractItemView::NoEditTriggers);                          //禁止修改
    ui->tableWidgetBackToBack->setSelectionMode(QAbstractItemView::NoSelection);                            //禁止选中
    ui->tableWidgetBackToBack->verticalHeader()->hide();                                                    //行号隐藏

    ui->tableWidgetDelay->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);                   //先自适应宽度
    ui->tableWidgetDelay->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);       //然后设置要根据内容使用宽度的列
    ui->tableWidgetDelay->setSelectionBehavior(QAbstractItemView::SelectRows);                              //整行选中的方式
    ui->tableWidgetDelay->setEditTriggers(QAbstractItemView::NoEditTriggers);                               //禁止修改
    ui->tableWidgetDelay->setSelectionMode(QAbstractItemView::NoSelection);                                 //禁止选中
    ui->tableWidgetDelay->verticalHeader()->hide();                                                         //行号隐藏

    throughputView = new QChartView(ui->gBoxThroughput);

    //格栅布局 必须要这一步，如果没有进行布局，那么整个chart只有一个单元那么大
    QGridLayout* m_mainLayout = new QGridLayout();

    //把显示的chart视图添加到布局中，这样就可以实现chart视图跟显示窗口一样大
    m_mainLayout->addWidget(throughputView);

    //最终设置格栅布局，不可缺
    ui->gBoxThroughput->setLayout(m_mainLayout);

    connect(ui->BtnOutPut, SIGNAL(clicked()), this, SLOT(slotBtnOutPutClicked()));
}

int FormTestResult::getIndex(const QString &frameLength, const QStringList& frameLengthList)
{
    if(frameLengthList.contains(frameLength))
    {
        return frameLengthList.indexOf(frameLength);
    }

    return -1;
}

void FormTestResult::setFilepath(const QString &newFilepath)
{
    ui->lineEditFilePath->setText(newFilepath);
}

void FormTestResult::showTabWidget(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

void FormTestResult::setTabWidgetEnable(int index, bool status)
{
    ui->tabWidget->setTabEnabled(index, status);
}

void FormTestResult::slotBtnOutPutClicked()
{
    if(ui->lineEditFilePath->text().isEmpty()){
        return;
    }

    PDFHelper::Instance()->init(ui->lineEditFilePath->text());
    PDFHelper::Instance()->initPainter();

    QString title = QString("RFC2544 测试结果");
    PDFHelper::Instance()->insertTitle(title);

    save();
}

