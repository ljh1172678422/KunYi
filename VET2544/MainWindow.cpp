#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QFileDialog>
#include <QSerialPortInfo>

#include "FormTestResult.h"
#include "ServiceException.h"
#include "DataTypeDef.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置应用程序窗口图标
    this->setWindowIcon(QIcon(":/icons/favicon.ico"));

    //设置窗口菜单栏取消最大化按钮使能
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    initWidget();
    initComboBoxFrameLength();
    initSerialPortComboBox();
    initComboBoxSerialConfig();
    initTableWidget();

    //加载CSS文件设置窗口样式
    QFile file(":/QSS/Sliver.css");
    file.open(QFile::ReadOnly);
    QString css = QLatin1String(file.readAll());
    this->setStyleSheet(css);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidget()
{
    //初始化预览测试结果界面
    formTestResult = new FormTestResult();
    //设置父窗口
    formTestResult->setParent(this);
    //设置为独立窗口
    formTestResult->setWindowFlags(Qt::Window);
    //设置为应用程序的模态窗口，阻止本应用所有窗口的输入
    formTestResult->setWindowModality(Qt::ApplicationModal);

    //初始化保存文件路径
    QString title = QString("RFC2544 %1").arg(getTestOptions());
    QString defaultName = QString("%1/%2.pdf").arg(QDir::currentPath(), title);
    ui->lineEditFilePath->setText(defaultName);

    //窗口状态栏进度条初始化
    progressBar = new QProgressBar();

    //设置进度条样式
    progressBar->setStyleSheet("QProgressBar {"
                                   "border: 1px solid grey;"
                                   "border-radius: 5px;"
                                   "text-align: center;"
                               "}"
                                   "QProgressBar::chunk {"
                                   "background-color: #05B8CC;"
                                   "border-radius: 3px;"
                               "}");

    progressBar->setValue(50);

    QLabel* label = new QLabel("请稍后...");
    ui->statusbar->addPermanentWidget(label);
    ui->statusbar->addPermanentWidget(progressBar);

    timerThread = new TimerThread();

    //设置测试进度提示框只读不可修改
    ui->textEditProgressTips->setReadOnly(true);

    on_cBoxOneThroughput_clicked();
    on_cBoxOneDelay_clicked();
    on_cBoxOnePaketLossRate_clicked();
    on_cBoxOneBackToBack_clicked();

    slotTestOptionsClicked();
    on_cBoxDelayCom_clicked();

    slotTestModeThroughput();
    slotTestModeDelay();
    slotTestModePaketLossRate();
    slotTestModeBackToBack();

    connect(ui->cBoxThroughput, SIGNAL(clicked()), this, SLOT(slotTestOptionsClicked()));
    connect(ui->cBoxDelay, SIGNAL(clicked()), this, SLOT(slotTestOptionsClicked()));
    connect(ui->cBoxPaketLossRate, SIGNAL(clicked()), this, SLOT(slotTestOptionsClicked()));
    connect(ui->cBoxBackToBack, SIGNAL(clicked()), this, SLOT(slotTestOptionsClicked()));

    connect(ui->rBtnTime_TTL, SIGNAL(clicked()), this, SLOT(slotTestModeThroughput()));
    connect(ui->rBtnCount_TTL, SIGNAL(clicked()), this, SLOT(slotTestModeThroughput()));

    connect(ui->rBtnTime_Delay, SIGNAL(clicked()), this, SLOT(slotTestModeDelay()));
    connect(ui->rBtnCount_Delay, SIGNAL(clicked()), this, SLOT(slotTestModeDelay()));

    connect(ui->rBtnTime_DBL, SIGNAL(clicked()), this, SLOT(slotTestModePaketLossRate()));
    connect(ui->rBtnCount_DBL, SIGNAL(clicked()), this, SLOT(slotTestModePaketLossRate()));

    connect(ui->rBtnTime_BtoB, SIGNAL(clicked()), this, SLOT(slotTestModeBackToBack()));
    connect(ui->rBtnCount_BtoB, SIGNAL(clicked()), this, SLOT(slotTestModeBackToBack()));

    connect(this, SIGNAL(signalStartTimerThread()), timerThread, SLOT(slotStartThread()));
    connect(this, SIGNAL(signalCloseTimerThread()), timerThread, SLOT(slotStopThread()));
    connect(timerThread, SIGNAL(sigAutoRefresh(int)), this, SLOT(slotAutoRefresh(int)));
}

void MainWindow::initComboBoxSerialConfig()
{
    {//配置数据位下拉框鼠标停留提示
        int count = ui->comboBoxDataBits->count();

        QStandardItemModel* model = new QStandardItemModel();
        for(int i = 0; i < count; i ++){
            QStandardItem* item = new QStandardItem(ui->comboBoxDataBits->itemText(i));
            item->setToolTip(getDataBitsToolTip(ui->comboBoxDataBits->itemText(i)));

            model->appendRow(item);
        }

        ui->comboBoxDataBits->setModel(model);
    }

    {//配置停止位下拉框鼠标停留提示
        int count = ui->comboBoxStopBits->count();

        QStandardItemModel* model = new QStandardItemModel();
        for(int i = 0; i < count; i ++){
            QStandardItem* item = new QStandardItem(ui->comboBoxStopBits->itemText(i));
            item->setToolTip(getStopBitsToolTip(ui->comboBoxStopBits->itemText(i)));

            model->appendRow(item);
        }

        ui->comboBoxStopBits->setModel(model);
    }

    {//配置校验位下拉框鼠标停留提示
        int count = ui->comboBoxCheckBits->count();

        QStandardItemModel* model = new QStandardItemModel();
        for(int i = 0; i < count; i ++){
            QStandardItem* item = new QStandardItem(ui->comboBoxCheckBits->itemText(i));
            item->setToolTip(getCheckBitsToolTip(ui->comboBoxCheckBits->itemText(i)));

            model->appendRow(item);
        }

        ui->comboBoxCheckBits->setModel(model);
    }
}

void MainWindow::initSerialPortComboBox()
{
    mySerialPortThread = new SerialPortThread();
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();

    int size = serialPortInfo.size();
    for(int i = 0; i < size; i ++){
        QString serialPortName = serialPortInfo[i].portName();

        ui->comboBoxSerialPort->insertItem(i, serialPortName);
    }
}

void MainWindow::initComboBoxFrameLength()
{
    QStringList itemList;
    itemList.clear();
    itemList << "全选" << "64" << "128" << "256" << "512" << "1024" << "1280" << "1518";

    QList<MenuItem*> menuList;
    menuList.clear();

    for(int i = 0; i < itemList.size(); i ++){
        MenuItem* item = new MenuItem(i, itemList[i], true);
        menuList.append(item);
    }

    ui->comBoxFrameLengthThroughput->addItems(menuList);
    ui->comBoxFrameLengthDelay->addItems(menuList);
    ui->comBoxFrameLengthPaketLossRate->addItems(menuList);
    ui->comBoxFrameLengthBtoB->addItems(menuList);
}

void MainWindow::initTableWidget()
{
    ui->throughputConfigData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //先自适应宽度
    ui->throughputConfigData->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //然后设置要根据内容使用宽度的列
    //ui->throughputConfigData->setSelectionBehavior(QAbstractItemView::SelectRows);                          //整行选中的方式
    //ui->throughputConfigData->setEditTriggers(QAbstractItemView::NoEditTriggers);                           //禁止修改
    ui->throughputConfigData->setSelectionMode(QAbstractItemView::SingleSelection);                         //可以选中单个
    ui->throughputConfigData->verticalHeader()->hide();                                                     //行号隐藏

    ui->delayConfigData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //先自适应宽度
    ui->delayConfigData->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //然后设置要根据内容使用宽度的列
    //ui->delayConfigData->setSelectionBehavior(QAbstractItemView::SelectRows);                          //整行选中的方式
    //ui->delayConfigData->setEditTriggers(QAbstractItemView::NoEditTriggers);                           //禁止修改
    ui->delayConfigData->setSelectionMode(QAbstractItemView::SingleSelection);                         //可以选中单个
    ui->delayConfigData->verticalHeader()->hide();                                                     //行号隐藏

    ui->paketLossRateConfigData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //先自适应宽度
    ui->paketLossRateConfigData->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //然后设置要根据内容使用宽度的列
    //ui->paketLossRateConfigData->setSelectionBehavior(QAbstractItemView::SelectRows);                          //整行选中的方式
    //ui->paketLossRateConfigData->setEditTriggers(QAbstractItemView::NoEditTriggers);                           //禁止修改
    ui->paketLossRateConfigData->setSelectionMode(QAbstractItemView::SingleSelection);                         //可以选中单个
    ui->paketLossRateConfigData->verticalHeader()->hide();                                                     //行号隐藏

    ui->backToBackConfigData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);               //先自适应宽度
    ui->backToBackConfigData->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);   //然后设置要根据内容使用宽度的列
    //ui->backToBackConfigData->setSelectionBehavior(QAbstractItemView::SelectRows);                          //整行选中的方式
    //ui->backToBackConfigData->setEditTriggers(QAbstractItemView::NoEditTriggers);                           //禁止修改
    ui->backToBackConfigData->setSelectionMode(QAbstractItemView::SingleSelection);                         //可以选中单个
    ui->backToBackConfigData->verticalHeader()->hide();                                                     //行号隐藏
}

QString MainWindow::getTestOptions()
{
    QString result;
    if(ui->cBoxBackToBack->isChecked()){
        result = QString("背靠背测试");
    }
    if(ui->cBoxPaketLossRate->isChecked()){
        result = QString("丢包率测试");
    }
    if(ui->cBoxDelay->isChecked()){
        result = QString("时延测试");
    }
    if(ui->cBoxThroughput->isChecked()){
        result = QString("吞吐量测试");
    }
    if(ui->cBoxBackToBack->isChecked() &&
            ui->cBoxPaketLossRate->isChecked() &&
            ui->cBoxDelay->isChecked()  &&
            ui->cBoxThroughput->isChecked()){
        result = QString("测试结果");
    }

    return result;
}

QString MainWindow::getCheckBitsToolTip(const QString &text)
{
    if(text == "NoParity"){
        return "没有发送的校验位。这是最常见的奇偶校验设置。错误检测由通信协议处理。";
    }
    else if(text == "EvenParity"){
        return "偶数校验：每个字符中1的位数，包括奇偶校验位，始终为偶数。";
    }
    else if(text == "OddParity"){
        return "奇数奇偶校验：每个字符的1位数，包括奇偶校验位，总是奇数。它确保每个字符中至少发生一次状态转换。";
    }
    else if(text == "SpaceParity"){
        return "空间校验：奇偶校验位在空间信号条件下发送。它不提供错误检测信息。";
    }
    else if(text == "MarkParity"){
        return "标记校验：校验位总是被设置为标记信号条件(逻辑1)。它不提供错误检测信息";
    }
    return "";
}

QString MainWindow::getStopBitsToolTip(const QString &text)
{
    if(text == "1"){
        return "1位停止位。";
    }
    else if(text == "3"){
        return "1.5个停止位。这仅适用于Windows平台。";
    }
    else if(text == "2"){
        return "2位停止位。";
    }

    return "";
}

QString MainWindow::getDataBitsToolTip(const QString &text)
{
    if(text == "5"){
        return "每个字符的数据位数为5。用于博多码。它通常只适用于老式设备，如电传打字机。";
    }
    else if(text == "6"){
        return "每个字符的数据位数为6。它很少使用。";
    }
    else if(text == "7"){
        return "每个字符的数据位数为7。它用于真正的ASCII。它通常只适用于老式设备，如电传打字机。";
    }
    else if(text == "8"){
        return "每个字符的数据位数为8。它用于大多数类型的数据，因为这个大小与字节的大小相匹配。它几乎普遍用于较新的应用程序。";
    }
    return "";
}

QSerialPort::Parity MainWindow::getParity(int parity)
{
    switch (parity) {
    case 0:
        return QSerialPort::NoParity;
        break;
    case 1:
        return QSerialPort::EvenParity;
        break;
    case 2:
        return QSerialPort::OddParity;
        break;
    case 3:
        return QSerialPort::SpaceParity;
        break;
    case 4:
        return QSerialPort::MarkParity;
        break;

    default:
        return QSerialPort::Parity();
        break;
    }

    return QSerialPort::Parity();
}

QSerialPort::BaudRate MainWindow::getBaudRate(int baudRate)
{
    switch (baudRate) {
    case 0:
        return QSerialPort::Baud1200;
        break;
    case 1:
        return QSerialPort::Baud2400;
        break;
    case 2:
        return QSerialPort::Baud4800;
        break;
    case 3:
        return QSerialPort::Baud9600;
        break;
    case 4:
        return QSerialPort::Baud19200;
        break;
    case 5:
        return QSerialPort::Baud38400;
        break;
    case 6:
        return QSerialPort::Baud57600;
        break;
    case 7:
        return QSerialPort::Baud115200;
        break;

    default:
        return QSerialPort::BaudRate();
        break;
    }

    return QSerialPort::BaudRate();
}

QSerialPort::DataBits MainWindow::getDataBits(int dataBits)
{
    switch (dataBits) {
    case 0:
        return QSerialPort::Data5;
        break;
    case 1:
        return QSerialPort::Data6;
        break;
    case 2:
        return QSerialPort::Data7;
        break;
    case 3:
        return QSerialPort::Data8;
        break;

    default:
        return QSerialPort::DataBits();
        break;
    }

    return QSerialPort::DataBits();

}

QSerialPort::StopBits MainWindow::getStopBits(int stopBits)
{
    switch (stopBits) {
    case 0:
        return QSerialPort::OneStop;
        break;
    case 1:
        return QSerialPort::OneAndHalfStop;
        break;
    case 2:
        return QSerialPort::TwoStop;
        break;

    default:
        return QSerialPort::StopBits();
        break;
    }

    return QSerialPort::StopBits();

}

void MainWindow::slotTestOptionsClicked()
{
    ui->gBoxThroughput->setVisible(ui->cBoxThroughput->isChecked());
    ui->gBoxDelay->setVisible(ui->cBoxDelay->isChecked());
    ui->gBoxPaketLossRate->setVisible(ui->cBoxPaketLossRate->isChecked());
    ui->gBoxBackToBack->setVisible(ui->cBoxBackToBack->isChecked());

    if(ui->cBoxThroughput->isChecked()){
        formTestResult->showThroughput();
        formTestResult->setTabWidgetEnable(0, true);
        formTestResult->showTabWidget(0);
    }
    else{
        formTestResult->hideThroughput();
        formTestResult->setTabWidgetEnable(0, false);
    }

    if(ui->cBoxDelay->isChecked()){
        formTestResult->showDelay();
        formTestResult->setTabWidgetEnable(1, true);
        formTestResult->showTabWidget(1);
    }
    else{
        formTestResult->hideDelay();
        formTestResult->setTabWidgetEnable(1, false);
    }

    if(ui->cBoxPaketLossRate->isChecked()){
        formTestResult->showPaketLossRate();
        formTestResult->setTabWidgetEnable(2, true);
        formTestResult->showTabWidget(2);
    }
    else{
        formTestResult->hidePaketLossRate();
        formTestResult->setTabWidgetEnable(2, false);
    }

    if(ui->cBoxBackToBack->isChecked()){
        formTestResult->showBackToBack();
        formTestResult->setTabWidgetEnable(3, true);
        formTestResult->showTabWidget(3);
    }
    else{
        formTestResult->hideBackToBack();
        formTestResult->setTabWidgetEnable(3, false);
    }
}

void MainWindow::slotTestModeThroughput()
{
    ui->sBoxTimeThroughput->setEnabled(ui->rBtnTime_TTL->isChecked());
    ui->sBoxCountThroughput->setEnabled(ui->rBtnCount_TTL->isChecked());
}

void MainWindow::slotTestModeDelay()
{
    ui->sBoxTimeDelay->setEnabled(ui->rBtnTime_Delay->isChecked());
    ui->sBoxCountDelay->setEnabled(ui->rBtnCount_Delay->isChecked());
}

void MainWindow::slotTestModePaketLossRate()
{
    ui->sBoxTimePaketLossRate->setEnabled(ui->rBtnTime_DBL->isChecked());
    ui->sBoxCountPaketLossRate->setEnabled(ui->rBtnCount_DBL->isChecked());
}

void MainWindow::slotTestModeBackToBack()
{
    ui->sBoxTimeBtoB->setEnabled(ui->rBtnTime_BtoB->isChecked());
    ui->sBoxCountBtoB->setEnabled(ui->rBtnCount_BtoB->isChecked());
}

void MainWindow::on_tBtnSelectFilePath_clicked()
{
    QString title = QString("RFC2544 %1").arg(getTestOptions());
    QString defaultName = QString("%1/%2.pdf").arg(QDir::currentPath(), title);
    QString file = QFileDialog::getSaveFileName(this, "保存文件", defaultName, "pdf(*.pdf)");
    if(!file.isEmpty()){
        ui->lineEditFilePath->setText(file);
    }
}

void MainWindow::on_cBoxDelayCom_clicked()
{
    if(ui->cBoxDelayCom->isChecked()){
        ui->labelDelayCom->show();
        ui->lineEditDelayCom->show();
        ui->tBtnDelayComSet->show();
    }
    else{
        ui->labelDelayCom->hide();
        ui->lineEditDelayCom->hide();
        ui->tBtnDelayComSet->hide();
    }
}

void MainWindow::on_tBtnSetSpeedThroughput_clicked()
{

}

void MainWindow::on_tBtnSetFrameLengthThroughput_clicked()
{
    QStringList testFrameLength = ui->comBoxFrameLengthThroughput->getItemsList();
    int count = testFrameLength.count();

    QList<TTL_DATA> ttlConfigData;

    for(int i = 0; i < count; i ++){
        TTL_DATA ttlData;
        ttlData.sendMode = !ui->rBtnTime_TTL->isChecked();
        ttlData.sendTime = ui->sBoxTimeThroughput->value();
        ttlData.sendFrameCount = ui->sBoxCountThroughput->value();
        ttlData.unitSpeed = ui->comBoxSpeedThroughput->currentIndex();
        ttlData.testFrameLength = testFrameLength[i];

        ttlConfigData.append(ttlData);
    }
}

void MainWindow::on_tBtnSetSpeedDelay_clicked()
{

}

void MainWindow::on_tBtnSetFrameLengthDelay_clicked()
{

}

void MainWindow::on_tBtnDelayComSet_clicked()
{

}

void MainWindow::on_tBtnSetFrameLengthPaketLossRate_clicked()
{

}

void MainWindow::on_tBtnSetSpeedBtoB_clicked()
{

}

void MainWindow::on_tBtnSetFrameLengthBtoB_clicked()
{

}

void MainWindow::on_BtnOutPut_clicked()
{
    formTestResult->setFilepath(ui->lineEditFilePath->text());

    //吞吐量折线图测试
    {
        QList<QPointF> speed;
        speed.append(QPointF(64, 14880));
        speed.append(QPointF(128, 8445));
        speed.append(QPointF(256, 4528));
        speed.append(QPointF(512, 2349));
        speed.append(QPointF(1024, 1197));
        speed.append(QPointF(1280, 961));
        speed.append(QPointF(1518, 812));

        QList<QPointF> speedTest;
        speedTest.append(QPointF(64, 14000));
        speedTest.append(QPointF(128, 8000));
        speedTest.append(QPointF(256, 4008));
        speedTest.append(QPointF(512, 1564));
        speedTest.append(QPointF(1024, 756));
        speedTest.append(QPointF(1280, 437));
        speedTest.append(QPointF(1518, 334));

        formTestResult->initThroughput(speed, speedTest);
    }

    //时延图表测试
    {
        QString delayType = "存储转发时延";
        QList<QStringList> result;

        result.append({"64", "10M", "Test1", "10us"});
        result.append({"128", "100M", "Test2", "10us"});
        result.append({"256", "1000M", "Test3", "10us"});
        result.append({"512", "100M", "Test4", "10us"});
        result.append({"1024", "10M", "Test5", "10us"});
        result.append({"1280", "100M", "Test6", "10us"});
        result.append({"1518", "1000M", "Test7", "10us"});

        formTestResult->initDelay(delayType, result);
    }

    //丢包率折线图测试
    {
        QMap<QString, QList<QPointF>> result;
        QList<QPointF> speedTest;
        speedTest.append(QPointF(0, 0));
        speedTest.append(QPointF(0.1, 0.01));
        speedTest.append(QPointF(0.2, 0.1));
        speedTest.append(QPointF(0.3, 0.26));
        speedTest.append(QPointF(0.4, 0.34));
        speedTest.append(QPointF(0.5, 0.37));
        speedTest.append(QPointF(0.6, 0.44));
        speedTest.append(QPointF(0.7, 0.60));
        speedTest.append(QPointF(0.8, 0.85));
        speedTest.append(QPointF(0.9, 0.90));
        speedTest.append(QPointF(1.0, 0.94));

        result.insert("64", speedTest);
        result.insert("128", speedTest);
        result.insert("256", speedTest);
        result.insert("512", speedTest);
        result.insert("1024", speedTest);
        result.insert("1280", speedTest);
        result.insert("1518", speedTest);

        QStringList frameLengthList;
        frameLengthList << "64";
        frameLengthList << "128";
        frameLengthList << "256";
        frameLengthList << "512";
        frameLengthList << "1024";
        frameLengthList << "1280";
        frameLengthList << "1518";

        formTestResult->initPaketLossRate(result, frameLengthList);
    }

    //背靠背图表测试
    {
        QList<QStringList> result;

        result.append({"64", "Test1", "10M", "123", "321"});
        result.append({"128", "Test2", "100M", "234", "432"});
        result.append({"256", "Test3", "1000M", "345", "543"});
        result.append({"512", "Test4", "100M", "456", "654"});
        result.append({"1024", "Test5", "10M", "567", "765"});
        result.append({"1280", "Test6", "100M", "678", "876"});
        result.append({"1518", "Test7", "1000M", "789", "987"});

        formTestResult->initBackToBack(result);
    }

    formTestResult->show();
}

void MainWindow::on_BtnOpenSerial_clicked()
{
    try {
        if(mySerialPortThread->serialIsOpen()){
            emit signalCloseSerialPortThread();
            ui->BtnOpenSerial->setText("打开串口");
        }
        else{
            mySerialPortThread->initSerialPort(ui->comboBoxSerialPort->currentText(),
                                               getBaudRate(ui->comboBoxBaud->currentIndex()),
                                               getDataBits(ui->comboBoxDataBits->currentIndex()),
                                               getStopBits(ui->comboBoxStopBits->currentIndex()),
                                               getParity(ui->comboBoxCheckBits->currentIndex()));

            emit signalStartSerialPortThread();
            ui->BtnOpenSerial->setText("关闭串口");
        }

        //根据串口是否已打开设置串口设置部分控件使能
        ui->comboBoxSerialPort->setEnabled(!mySerialPortThread->serialIsOpen());
        ui->comboBoxBaud->setEnabled(!mySerialPortThread->serialIsOpen());
        ui->comboBoxCheckBits->setEnabled(!mySerialPortThread->serialIsOpen());
        ui->comboBoxDataBits->setEnabled(!mySerialPortThread->serialIsOpen());
        ui->comboBoxStopBits->setEnabled(!mySerialPortThread->serialIsOpen());
    }
    catch (ServiceException& e) {
        QMessageBox::information(this, "提示", e.getMessage());
    }
}

void MainWindow::on_BtnTimerStart_clicked()
{
    if(timerThread->getIsStart()){
        ui->BtnTimerStart->setText("开始");
        emit signalCloseTimerThread();
    }
    else{
        ui->BtnTimerStart->setText("暂停");
        emit signalStartTimerThread();
    }
}

void MainWindow::slotAutoRefresh(int curInt)
{
    progressBar->setValue(curInt);
    if(curInt == 100){
        emit signalCloseTimerThread();
        ui->BtnTimerStart->setText("开始");
        timerThread->setCurInt(0);
        QMessageBox::information(this, "提示", "测试已完成！");
        return;
    }
}

void MainWindow::on_tBtnSetCalcMode_clicked()
{

}

void MainWindow::on_cBoxOneThroughput_clicked()
{
    ui->gBoxSameConfig->setVisible(!ui->cBoxOneThroughput->isChecked());
    ui->gBoxOneConfig->setVisible(ui->cBoxOneThroughput->isChecked());
}

void MainWindow::on_BtnStartThroughput_clicked()
{
    if(ui->cBoxOneThroughput->isChecked()){
        QList<QStringList> result = ui->throughputConfigData->getItemList();

        qDebug() << result;
    }
    else{

    }
}

void MainWindow::on_cBoxOneDelay_clicked()
{
    ui->gBoxSameConfigDelay->setVisible(!ui->cBoxOneDelay->isChecked());
    ui->gBoxOneConfigDelay->setVisible(ui->cBoxOneDelay->isChecked());
}

void MainWindow::on_cBoxOnePaketLossRate_clicked()
{
    ui->gBoxSameConfigPaketLossRate->setVisible(!ui->cBoxOnePaketLossRate->isChecked());
    ui->gBoxOneConfigPaketLossRate->setVisible(ui->cBoxOnePaketLossRate->isChecked());
}

void MainWindow::on_cBoxOneBackToBack_clicked()
{
    ui->gBoxSameConfigBackToBack->setVisible(!ui->cBoxOneBackToBack->isChecked());
    ui->gBoxOneConfigBackToBack->setVisible(ui->cBoxOneBackToBack->isChecked());
}

