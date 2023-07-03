#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QThread>
#include <QTextDocument>
#include <QPalette>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isSerialOpen(false)
    , burnWritThread(NULL)
    , isBurnWriteThreadStart(false)
    , isAutoRefresh(false)
    , isShowDebugWindow(false)
{
    ui->setupUi(this);
    //状态栏添加信息
    ui->statusBar->showMessage("WellCome", 20*1000);

    autoRefreshThread = new AutoRefreshThread();
    burnWritThread = new BurnWritThread();
    mySerialPort = new MySerialPort();

    debugDialog = new DebugPassword();

    statusBarAddChildren();
    this->setWindowIcon(QIcon(":/favicon.ico"));

    //遍历设备串口，并在打开串口菜单栏添加选项
    serialPortList = QSerialPortInfo::availablePorts();

    //设置接收数据显示栏无焦点
    ui->textEditReceiveData->setFocusPolicy(Qt::NoFocus);

    //手动添加菜单Action
    menuBarAddAction();

    //设置菜单和窗口的焦点状态
    setMenuWidgetFocus(false);

    //设置打开串口菜单选项
    setOpenSerialMenuAction();

    //设置按钮组成员
    setButtonGroupMember();

    slotDebugWindow();

    //菜单按钮点击事件
    connect(ui->OpenSerialMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotOpenSerialClicked(QAction*)));
    connect(ui->BoardCardSelect, SIGNAL(triggered(QAction*)), this, SLOT(slotBorderCardSelectMenuClicked(QAction*)));
    connect(ui->CloseSerialMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotCloseSerialClicked(QAction*)));
    connect(ui->ModeSwitch, SIGNAL(triggered(QAction*)), this, SLOT(slotModeSwitchMenuClicked(QAction*)));
    connect(synConfigAction, SIGNAL(triggered()), this, SLOT(slotSynConfigActionClicked()));
    connect(dataResetAction, SIGNAL(triggered()), this, SLOT(slotDataResetActionClicked()));
    connect(sendXmodemAction, SIGNAL(triggered()), this, SLOT(slotSendXmodemActionClicked()));
    connect(resetBoardAction, SIGNAL(triggered()), this, SLOT(slotResetBoardActionClicked()));
    connect(debugAction, SIGNAL(triggered()), this, SLOT(slotDebugWindow()));


    //窗口按钮点击事件
    connect(ui->BtnClearReceiveData, SIGNAL(clicked()), this, SLOT(slotClearReceiveDataClicked()));
    connect(ui->BtnSendData, SIGNAL(clicked()), this, SLOT(slotSendDataClicked()));
    connect(ui->tBtnSelectPath, SIGNAL(clicked()), this, SLOT(slotSelectPathClicked()));
    connect(ui->BtnGetVersion, SIGNAL(clicked()), this, SLOT(slotGetVersionClicked()));
    connect(ui->rBtnReceiveASCII, SIGNAL(clicked()), this, SLOT(slotReceiveDataTypeChanged()));
    connect(ui->rBtnReceiveHEX, SIGNAL(clicked()), this, SLOT(slotReceiveDataTypeChanged()));
    connect(ui->rBtnSendDataASCII, SIGNAL(clicked()), this, SLOT(slotSendDataTypeChanged()));
    connect(ui->rBtnSendDataHex, SIGNAL(clicked()), this, SLOT(slotSendDataTypeChanged()));
    connect(ui->BtnMdioRead, SIGNAL(clicked()), this, SLOT(slotBtnMdioReadClicked()));
    connect(ui->BtnMdioWrite, SIGNAL(clicked()), this, SLOT(slotBtnMdioWriteClicked()));
    connect(ui->BtnFpgaRead, SIGNAL(clicked()), this, SLOT(slotBtnFpgaReadClicked()));
    connect(ui->BtnFpgaWrite, SIGNAL(clicked()), this, SLOT(slotBtnFpgaWriteClicked()));
    connect(ui->BtnBurn, SIGNAL(clicked()), this, SLOT(slotBtnBurnClicked()));
    connect(ui->BtnSetT1_1, SIGNAL(clicked()), this, SLOT(slotBtnSetT1AClicked()));
    connect(ui->BtnSetT1_2, SIGNAL(clicked()), this, SLOT(slotBtnSetT1BClicked()));
    connect(ui->BtnSetRJ45_1, SIGNAL(clicked()), this, SLOT(slotBtnSetRJ45AClicked()));
    connect(ui->BtnSetRJ45_2, SIGNAL(clicked()), this, SLOT(slotBtnSetRJ45BClicked()));
    connect(ui->BtnStatusFresh, SIGNAL(clicked()), this, SLOT(slotBtnStatusFreshClicked()));

    //车载T1-1
    connect(ui->rBtnAnegDisableT1_1, SIGNAL(toggled(bool)), this, SLOT(slotRBtnT1AAnegGroupChanged(bool)));
    connect(ui->rBtnAnegEnableT1_1, SIGNAL(toggled(bool)), this, SLOT(slotRBtnT1AAnegGroupChanged(bool)));

    //车载T1-2
    connect(ui->rBtnAnegDisableT1_2, SIGNAL(toggled(bool)), this, SLOT(slotRBtnT1BAnegGroupChanged(bool)));
    connect(ui->rBtnAnegEnableT1_2, SIGNAL(toggled(bool)), this, SLOT(slotRBtnT1BAnegGroupChanged(bool)));

    //车载RJ45-1
    connect(ui->rBtnAnegDisableRJ45_1, SIGNAL(toggled(bool)), this, SLOT(slotRBtnRJ45AAnegGroupChanged(bool)));
    connect(ui->rBtnAnegEnableRJ45_1, SIGNAL(toggled(bool)), this, SLOT(slotRBtnRJ45AAnegGroupChanged(bool)));

    //车载RJ45-2
    connect(ui->rBtnAnegDisableRJ45_2, SIGNAL(toggled(bool)), this, SLOT(slotRBtnRJ45BAnegGroupChanged(bool)));
    connect(ui->rBtnAnegEnableRJ45_2, SIGNAL(toggled(bool)), this, SLOT(slotRBtnRJ45BAnegGroupChanged(bool)));

    //接收输入框
    connect(ui->textEditReceiveData, SIGNAL(textChanged()), this, SLOT(slotTextEditReceiveChanged()));

    //自动刷新线程
    connect(autoRefreshThread, SIGNAL(sigAutoRefresh()), this, SLOT(slotAutoRefreshConfigData()));
    connect(this, SIGNAL(SignalStartAutoRefreshThread()), autoRefreshThread, SLOT(slotStartThread()));
    connect(this, SIGNAL(SignalCloseAutoRefreshThread()), autoRefreshThread, SLOT(slotStopThread()));

    //烧写线程
    connect(this, SIGNAL(SignalStartBurnThread()), burnWritThread, SLOT(slotStartThread()));
    connect(this, SIGNAL(SignalCloseBurnThread()), burnWritThread, SLOT(slotCloseThread()));
    connect(burnWritThread, SIGNAL(sigUpdateSpiFlashWriteText(QString)), this, SLOT(slotBurnBtnTextUpdate(QString)));

    //串口线程
    connect(mySerialPort, SIGNAL(Sig_SendSerialPortData(QString)), this, SLOT(SlotReceiveData(QString)));
    connect(this, SIGNAL(SignalStartThread()), mySerialPort, SLOT(SlotStartThread()));
    connect(this, SIGNAL(SignalCloseThread()), mySerialPort, SLOT(SlotCloseThread()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::statusBarAddChildren()
{
    modeLabel = new QLabel();           //模式Label提示
    //设置蓝底黑字
    if(ui->action_Bypass->isChecked())
    {//直通（Bypass）
        modeLabel->setText("直通（Bypass）");
    }
    else if(ui->action_Mirror->isChecked())
    {//镜像（Mirror）
        modeLabel->setText("镜像（Mirror）");
    }
    modeLabel->setStyleSheet("background-color: rgb(170, 255, 255);");

    borderCardLabel = new QLabel();     //板卡Label提示
    QPalette borderCardPe;
    //设置青底黑字
    borderCardPe.setColor(QPalette::Window, Qt::cyan);
    borderCardPe.setColor(QPalette::WindowText, Qt::black);
    borderCardLabel->setPalette(borderCardPe);
    if(ui->actionVBE1000->isChecked())
    {//直通（Bypass）
        borderCardLabel->setText("VBE1000");
    }
    else if(ui->actionVBE1200->isChecked())
    {//镜像（Mirror）
        borderCardLabel->setText("VBE1200");
    }
    borderCardLabel->setStyleSheet("background-color: rgb(180, 255, 148);");

    pProgressBar = new QProgressBar();  //进度条提示
    pProgressBar->setMaximumWidth(200);
    pProgressBar->setRange(0,100);

    statusLabel = new QLabel();     //状态Label提示
    statusLabel->setText("状态提示");

    ui->statusBar->addPermanentWidget(statusLabel);
    ui->statusBar->addPermanentWidget(pProgressBar);
    ui->statusBar->addPermanentWidget(modeLabel);
    ui->statusBar->addPermanentWidget(borderCardLabel);
}

void MainWindow::setMenuWidgetFocus(bool statu)
{
    ui->CloseSerialMenu->setEnabled(statu);     //设置关闭串口菜单按钮无法点击
    ui->BoardCardSelect->setEnabled(statu); //设置板卡选择菜单按钮无法点击
    synConfigAction->setEnabled(statu);   //设置同步配置菜单按钮无法点击
    ui->ModeSwitch->setEnabled(statu);  //设置模式切换菜单按钮无法点击
    dataResetAction->setEnabled(statu); //设置恢复出厂设置菜单按钮无法点击
    sendXmodemAction->setEnabled(statu); //设置发送Xmodem菜单按钮无法点击
    resetBoardAction->setEnabled(statu); //设置板卡复位菜单按钮无法点击
    debugAction->setEnabled(statu);   //设置调试菜单按钮无法点击

    //ui->groupBoxSerialReceive->setEnabled(statu); //设置串口接收组框无法点击
    //ui->groupBoxSerialSend->setEnabled(statu); //设置串口发送组框无法点击
    //ui->groupBoxMdioInterface->setEnabled(statu); //设置MDIO接口组框无法点击
    //ui->groupBoxFpgaInterface->setEnabled(statu); //设置FPGA接口组框无法点击
    ui->groupBoxFirmwareWrite->setEnabled(statu); //设置固件烧写组框无法点击
    ui->groupBox_T1_1->setEnabled(statu); //设置T1-1组框无法点击
    ui->groupBox_T1_2->setEnabled(statu); //设置T1-2组框无法点击
    ui->groupBox_RJ45_1->setEnabled(statu); //设置RJ45-1组框无法点击
    ui->groupBox_RJ45_2->setEnabled(statu); //设置RJ45-2组框无法点击
    ui->groupBox_Status->setEnabled(statu); //设置Status组框无法点击
}

void MainWindow::menuBarAddAction()
{
    synConfigAction = new QAction("同步配置");
    dataResetAction = new QAction("恢复出厂设置");
    sendXmodemAction = new QAction("发送Xmodem");
    resetBoardAction = new QAction("板卡复位");
    debugAction = new QAction("调试");

    ui->menubar->addAction(synConfigAction);
    ui->menubar->addAction(dataResetAction);
    ui->menubar->addAction(sendXmodemAction);
    ui->menubar->addAction(resetBoardAction);
    ui->menubar->addAction(debugAction);
}

void MainWindow::setOpenSerialMenuAction()
{
    int size = serialPortList.size();
    for(int i = 0 ; i < size; i ++)
    {
        QSerialPortInfo info = serialPortList[i];
        QString serialPortName = info.portName() + ":" + info.description();

        //在打开串口菜单添加新选项
        QAction* action = new QAction(serialPortName);
        action->setCheckable(true);
        ui->OpenSerialMenu->addAction(action);
        openSerialPorts.insert(action, false);
    }
}

void MainWindow::setCloseSerialMenuAction(const QString& serialName)
{
    ui->CloseSerialMenu->clear();

    if(!serialName.isEmpty())
    {
        //在打开串口菜单添加新选项
        QAction* action = new QAction(serialName);
        action->setCheckable(false);
        ui->CloseSerialMenu->addAction(action);
    }
}

void MainWindow::setButtonGroupMember()
{
    {
        rBtnSerialRecvGroup.addButton(ui->rBtnReceiveASCII);
        rBtnSerialRecvGroup.addButton(ui->rBtnReceiveHEX);
        ui->rBtnReceiveHEX->setChecked(true);
    }
    {
        rBtnSerialSendGroup.addButton(ui->rBtnSendDataASCII);
        rBtnSerialSendGroup.addButton(ui->rBtnSendDataHex);
        ui->rBtnSendDataHex->setChecked(true);
    }

    {
        rBtnT1AAnegGroup.addButton(ui->rBtnAnegEnableT1_1);
        rBtnT1AAnegGroup.addButton(ui->rBtnAnegDisableT1_1);
        ui->rBtnAnegEnableT1_1->setChecked(true);

        rBtnT1ASpeedGroup.addButton(ui->rBtnFeSpeedT1_1);
        rBtnT1ASpeedGroup.addButton(ui->rBtnGeSpeedT1_1);
        ui->rBtnFeSpeedT1_1->setChecked(true);

        rBtnT1AModeGroup.addButton(ui->rBtnMasterModeT1_1);
        rBtnT1AModeGroup.addButton(ui->rBtnSlaverModeT1_1);
        ui->rBtnMasterModeT1_1->setChecked(true);
    }

    {
        rBtnT1BAnegGroup.addButton(ui->rBtnAnegEnableT1_2);
        rBtnT1BAnegGroup.addButton(ui->rBtnAnegDisableT1_2);
        ui->rBtnAnegEnableT1_2->setChecked(true);

        rBtnT1BSpeedGroup.addButton(ui->rBtnFeSpeedT1_2);
        rBtnT1BSpeedGroup.addButton(ui->rBtnGeSpeedT1_2);
        ui->rBtnFeSpeedT1_2->setChecked(true);

        rBtnT1BModeGroup.addButton(ui->rBtnMasterModeT1_2);
        rBtnT1BModeGroup.addButton(ui->rBtnSlaverModeT1_2);
        ui->rBtnMasterModeT1_2->setChecked(true);
    }

    {
        rBtnRJ45AAnegGroup.addButton(ui->rBtnAnegEnableRJ45_1);
        rBtnRJ45AAnegGroup.addButton(ui->rBtnAnegDisableRJ45_1);
        ui->rBtnAnegEnableRJ45_1->setChecked(true);

        rBtnRJ45ASpeedGroup.addButton(ui->rBtnFeSpeedRJ45_1);
        rBtnRJ45ASpeedGroup.addButton(ui->rBtnGeSpeedRJ45_1);
        ui->rBtnFeSpeedRJ45_1->setChecked(true);

        rBtnRJ45ADuplexGroup.addButton(ui->rBtnFullDuplexRJ45_1);
        rBtnRJ45ADuplexGroup.addButton(ui->rBtnHalfDuplexRJ45_1);
        ui->rBtnFullDuplexRJ45_1->setChecked(true);
    }

    {
        rBtnRJ45BAnegGroup.addButton(ui->rBtnAnegEnableRJ45_2);
        rBtnRJ45BAnegGroup.addButton(ui->rBtnAnegDisableRJ45_2);
        ui->rBtnAnegEnableRJ45_2->setChecked(true);

        rBtnRJ45BSpeedGroup.addButton(ui->rBtnFeSpeedRJ45_2);
        rBtnRJ45BSpeedGroup.addButton(ui->rBtnGeSpeedRJ45_2);
        ui->rBtnFeSpeedRJ45_2->setChecked(true);

        rBtnRJ45BDuplexGroup.addButton(ui->rBtnFullDuplexRJ45_2);
        rBtnRJ45BDuplexGroup.addButton(ui->rBtnHalfDuplexRJ45_2);
        ui->rBtnFullDuplexRJ45_2->setChecked(true);
    }

}

bool MainWindow::serialIsOpen(const QMap<QAction*, bool> &map)
{
    QList<QAction*> actionList = map.keys();
    int size = actionList.size();
    for(int i = 0; i < size; i ++)
    {
        if(map[actionList[i]])
        {
            return true;
        }
    }

    return false;
}

int MainWindow::send_Cmd(int cmd, QByteArray data)
{
    int dataSize = data.count();

    QByteArray cmdData;
    cmdData.resize(5);

    cmdData[0] = (0x4F);
    cmdData[1] = (0x44);
    cmdData[2] = ((6 + dataSize) >> 8);
    cmdData[3] = (6 + dataSize);
    cmdData[4] = (cmd);
    cmdData.append(data);

    //发送指令添加校验值
    QByteArray checkSum = calCheckSum(cmdData, 5 + dataSize);
    cmdData.append(checkSum);

    int ret = mySerialPort->serialPortSendData(cmdData);

    return ret;
}

QByteArray MainWindow::calCheckSum(QByteArray &data, int len)
{
    QByteArray tempByte;
    tempByte.resize(1);
    tempByte[0] = 0;
    for(int i = 0; i < len; i ++)
    {
        tempByte[0] = tempByte[0] + data[i];
    }

    return tempByte;
}

QString MainWindow::hexToAscii(QString &value)
{
    value = value.replace(" ", "");
    QString result;
    result.clear();

    for(int i = 0; i < value.size(); i ++)
    {
        int sum = value.at(i).toLatin1();
        if(i == value.size() - 1) {
            result = result + QString::number(sum) + "\n";
        }
        else {
            result = result + QString::number(sum) + " ";
        }
    }

    return result;
}

QString MainWindow::receiveHexToAscii(const QString &value)
{
    QStringList tempList = value.split("\n");
    QString result;
    result.clear();

    for(int i = 0; i < tempList.size(); i ++)
    {
        if(tempList[i].isEmpty())
        {
            continue;
        }
        //把输入框中的空格替换掉
        QStringList str = tempList[i].split(":");

        result += "Receive Data:";
        if(str.size() == 1) {
            result += hexToAscii(str[0]);
        }
        else {
            result += hexToAscii(str[1]);
        }
    }

    return result;
}

QString MainWindow::asciiToHex(const QString &value)
{
    QString result;
    result.clear();

    QStringList tempStr = value.split(" ");
    for(int j = 0; j < tempStr.size(); j += 2)
    {
        QByteArray tempByte;
        tempByte.clear();
        bool ok;
        int ascii1 = tempStr[j].toInt(&ok, 10);
        tempByte.append(ascii1);
        int ascii2 = tempStr[j+1].toInt(&ok, 10);
        tempByte.append(ascii2);
        if(!ok){
            QMessageBox::information(this, "提示", "数据转换失败");
        }

        if(j == tempStr.size() - 2) {
            result = result + QChar(tempByte.at(0)) + QChar(tempByte.at(1)) + "\n";
        }
        else {
            result = result + QChar(tempByte.at(0)) + QChar(tempByte.at(1)) + " ";
        }
    }

    return result;
}

QString MainWindow::receiveAsciiToHex(const QString &value)
{
    QStringList tempList = value.split("\n");
    QString result;
    result.clear();

    for(int i = 0; i < tempList.size(); i ++)
    {
        if(tempList[i].isEmpty())
        {
            continue;
        }
        //获取后续数据部分
        QStringList str = tempList[i].split(":");

        result += "Receive Data:";
        if(str.size() == 1) {
            result += asciiToHex(str[0]);
        }
        else {
            result += asciiToHex(str[1]);
        }
    }

    return result;
}

void MainWindow::parseHexReceiveData(QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int cmd = tempList[4].toInt(&ok, 16);
    if(!ok){
        statusLabel->setText("命令值解析失败！");
        return;
    }

    QList<int> tempResult;
    tempResult.resize(tempList.size());
    for(int i = 0; i < tempList.size(); i ++){
        tempResult[i] = tempList[i].toInt(&ok, 16);
    }

    if(tempList.size() > 6)
    {
        if(tempResult[0] == 0x45 &&
                tempResult[1] == 0x52 &&
                tempResult[2] == 0x52){
            statusLabel->setText("执行命令失败！");
            return;
        }
        else if(tempResult[0] == 0x52 &&
                tempResult[1] == 0x50){
            int ret = verify_check_sum(tempResult);

            if (ret == 3)
            {
                statusLabel->setText("命令返回长度错误");
            }
            else if (ret == 2)
            {
                statusLabel->setText("命令校验失败");
            }
            else if (ret == 1)
            {
                statusLabel->setText("命令返回长度不符");
            }
        }
    }

    switch (cmd) {
    case 0x61://读MDIO寄存器
        mdioValueParse(value);
        break;

    case 0x62://写MDIO寄存器
        break;

    case 0x64://将BIN的长度写入FLASH
        break;

    case 0x65://将BIN的数据写入FLASH
        burnFlashDataParse(value);
        break;

    case 0x66://复位设备
        parseDeviceResetData(value);
        break;

    case 0x68://读FPGA数据
        fpgaValueParse(value);
        break;

    case 0x69://写FPGA数据
        writeFpgaValueParse(value);
        break;

    case 0x70://获取FPGA和MCU的版本
        getMcuFpgaVersion(value);
        break;

    case 0x71://获取设备状态
        parseDeviceStatus(value);
        break;

    case 0xA1://获取设备配置
        parseDeviceConfig(value);
        break;

    case 0xA2://配置设备
        parseConfigDevice(value);
        break;

    case 0xA3:
        parseResetReceive(value);
        break;

    default:
        break;
    }
}

void MainWindow::parseAsciiReceiveData(QString &value)
{
    QString tempValue = receiveAsciiToHex(value);
    QStringList dataList = tempValue.split(":");
    parseHexReceiveData(dataList[1]);
}

bool MainWindow::lineEditTextToUint(const QString &text, uint &outNum)
{
    bool ok;
    outNum = text.toUInt(&ok, 16);
    if(!ok)
    {
        outNum = 0;
        return false;
    }

    return true;
}

void MainWindow::mdioValueParse(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }

    QString mdioValueHigh = tempList[6];        //MDIO寄存器数据高位
    QString mdioValueLow = tempList[7];         //MDIO寄存器数据地位

    uint valueHigh = mdioValueHigh.toUInt(&ok, 16);
    uint valueLow = mdioValueLow.toUInt(&ok, 16);

    uint mdioValue = (valueHigh << 8) + valueLow;

    ui->lineEditMdioValue->setText(QString::number(mdioValue, 16));
}

void MainWindow::burnFlashDataParse(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        statusLabel->setText("数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        statusLabel->setText(message);
        emit SignalCloseBurnThread();

        burnWritThread->exitBurnFlash = true;
        ui->BtnBurn->setText("烧写");
        isBurnWriteThreadStart = false;

        return;
    }
}

void MainWindow::parseDeviceResetData(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("复位失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }
    else
    {
        QString message = QString("设备已复位");
        QMessageBox::information(this, "提示", message);
        return;
    }
}

void MainWindow::fpgaValueParse(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }

    QString fpgaValueStr = tempList[6];

    uint fpgaValue = fpgaValueStr.toUInt(&ok, 16);

    ui->lineEditFpgaValue->setText(QString::number(fpgaValue, 16));
}

void MainWindow::writeFpgaValueParse(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        statusLabel->setText(message);
        return;
    }
    else
    {
        statusLabel->setText("配置写入成功！");
    }
}

void MainWindow::getMcuFpgaVersion(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }

    QString mcuVersion = ui->labelCurFirmwareVersion->text();
    QStringList tempMcuList = mcuVersion.split(':');

    QString fpgaVersion = ui->labelCurFpgaVersion->text();
    QStringList tempFPGAList = fpgaVersion.split(':');

    QString mcuVersionStr = QString("%1:%2.%3.%4").arg(tempMcuList[0]).arg(tempList[6]).arg(tempList[7]).arg(tempList[8]);
    QString fpgaVersionStr = QString("%1:%2.%3.%4").arg(tempFPGAList[0]).arg(tempList[9]).arg(tempList[10]).arg(tempList[11]);

    ui->labelCurFirmwareVersion->setText(mcuVersionStr);
    ui->labelCurFpgaVersion->setText(fpgaVersionStr);
}

void MainWindow::parseDeviceStatus(const QString &value)
{
    QStringList tempList = value.split(" ");
    bool ok;

    //解析 车载T1-1状态数据
    {
        int status = tempList[6].toUInt(&ok, 16);
        if((status & 1) == 0)
        {
            ui->T1AAutoNegoLabel->setText("Disable");
            ui->T1AAutoNegoLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnAnegDisableT1_1->setChecked(true);
            ui->rBtnAnegEnableT1_1->setChecked(false);
        }
        else
        {
            ui->T1AAutoNegoLabel->setText("Enable");
            ui->T1AAutoNegoLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnAnegDisableT1_1->setChecked(false);
            ui->rBtnAnegEnableT1_1->setChecked(true);
        }

        if((status & 2) == 0)
        {
            ui->T1ALinkStatusLabel->setText("Down");
            ui->T1ALinkStatusLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->T1ALinkStatusLabel->setText("Up");
            ui->T1ALinkStatusLabel->setStyleSheet("background-color: #FF008000;");
        }

        if((status & 0xC) == 0x8)
        {
            ui->T1ALinkSpeedLabel->setText("1000 Mbps");
            ui->T1ALinkSpeedLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnGeSpeedT1_1->setChecked(true);
            ui->rBtnFeSpeedT1_1->setChecked(false);
        }
        else {
            ui->T1ALinkSpeedLabel->setText("100 Mbps");
            ui->T1ALinkSpeedLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnGeSpeedT1_1->setChecked(false);
            ui->rBtnFeSpeedT1_1->setChecked(true);
        }

        if((status & 0x10) == 0)
        {
            ui->T1AForceModeLabel->setText("Slaver");
            ui->T1AForceModeLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnMasterModeT1_1->setChecked(false);
            ui->rBtnSlaverModeT1_1->setChecked(true);
        }
        else {
            ui->T1AForceModeLabel->setText("Master");
            ui->T1AForceModeLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnMasterModeT1_1->setChecked(true);
            ui->rBtnSlaverModeT1_1->setChecked(false);
        }

        if((status & 0x20) == 0)
        {
            ui->T1AModeLabel->setText("Bypass");
            ui->T1AModeLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->T1AModeLabel->setText("Mirror");
            ui->T1AModeLabel->setStyleSheet("background-color: #FF008000;");
        }
    }

    //解析 车载T1-2状态数据
    {
        int status = tempList[7].toUInt(&ok, 16);
        if((status & 1) == 0)
        {
            ui->T1BAutoNegoLabel->setText("Disable");
            ui->T1BAutoNegoLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnAnegDisableT1_2->setChecked(true);
            ui->rBtnAnegEnableT1_2->setChecked(false);
        }
        else
        {
            ui->T1BAutoNegoLabel->setText("Enable");
            ui->T1BAutoNegoLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnAnegDisableT1_2->setChecked(false);
            ui->rBtnAnegEnableT1_2->setChecked(true);
        }

        if((status & 2) == 0)
        {
            ui->T1BLinkStatusLabel->setText("Down");
            ui->T1BLinkStatusLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->T1BLinkStatusLabel->setText("Up");
            ui->T1BLinkStatusLabel->setStyleSheet("background-color: #FF008000;");
        }

        if((status & 0xC) == 0x8)
        {
            ui->T1BLinkSpeedLabel->setText("1000 Mbps");
            ui->T1BLinkSpeedLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnGeSpeedT1_2->setChecked(true);
            ui->rBtnFeSpeedT1_2->setChecked(false);
        }
        else {
            ui->T1BLinkSpeedLabel->setText("100 Mbps");
            ui->T1BLinkSpeedLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnGeSpeedT1_2->setChecked(false);
            ui->rBtnFeSpeedT1_2->setChecked(true);
        }

        if((status & 0x10) == 0)
        {
            ui->T1BForceModeLabel->setText("Slaver");
            ui->T1BForceModeLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnSlaverModeT1_2->setChecked(true);
            ui->rBtnMasterModeT1_2->setChecked(false);
        }
        else {
            ui->T1BForceModeLabel->setText("Master");
            ui->T1BForceModeLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnSlaverModeT1_2->setChecked(false);
            ui->rBtnMasterModeT1_2->setChecked(true);
        }

        if((status & 0x20) == 0)
        {
            ui->T1BModeLabel->setText("Bypass");
            ui->T1BModeLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->T1BModeLabel->setText("Mirror");
            ui->T1BModeLabel->setStyleSheet("background-color: #FF008000;");
        }
    }

    //解析 车载TX-1状态数据
    {
        int status = tempList[8].toUInt(&ok, 16);
        if((status & 1) == 0)
        {
            ui->RJ45AAutoNegoLabel->setText("Disable");
            ui->RJ45AAutoNegoLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnAnegDisableRJ45_1->setChecked(true);
            ui->rBtnAnegEnableRJ45_1->setChecked(false);
        }
        else
        {
            ui->RJ45AAutoNegoLabel->setText("Enable");
            ui->RJ45AAutoNegoLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnAnegDisableRJ45_1->setChecked(false);
            ui->rBtnAnegEnableRJ45_1->setChecked(true);
        }

        if((status & 2) == 0)
        {
            ui->RJ45ALinkStatusLabel->setText("Down");
            ui->RJ45ALinkStatusLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->RJ45ALinkStatusLabel->setText("Up");
            ui->RJ45ALinkStatusLabel->setStyleSheet("background-color: #FF008000;");
        }

        if((status & 0xC) == 0x8)
        {
            ui->RJ45ALinkSpeedLabel->setText("1000 Mbps");
            ui->RJ45ALinkSpeedLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnGeSpeedRJ45_1->setChecked(true);
            ui->rBtnFeSpeedRJ45_1->setChecked(false);
        }
        else {
            ui->RJ45ALinkSpeedLabel->setText("100 Mbps");
            ui->RJ45ALinkSpeedLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnGeSpeedRJ45_1->setChecked(false);
            ui->rBtnFeSpeedRJ45_1->setChecked(true);
        }

        if((status & 0x40) == 0)
        {
            ui->RJ45ADuplexTypeLabel->setText("Half");
            ui->RJ45ADuplexTypeLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnHalfDuplexRJ45_1->setChecked(true);
            ui->rBtnFullDuplexRJ45_1->setChecked(false);
        }
        else {
            ui->RJ45ADuplexTypeLabel->setText("Full");
            ui->RJ45ADuplexTypeLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnHalfDuplexRJ45_1->setChecked(false);
            ui->rBtnFullDuplexRJ45_1->setChecked(true);
        }

        if((status & 0x20) == 0)
        {
            ui->RJ45AModeLabel->setText("Bypass");
            ui->RJ45AModeLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->RJ45AModeLabel->setText("Mirror");
            ui->RJ45AModeLabel->setStyleSheet("background-color: #FF008000;");
        }
    }

    //解析 车载TX-2状态数据
    {
        int status = tempList[9].toUInt(&ok, 16);
        if((status & 1) == 0)
        {
            ui->RJ45BAutoNegoLabel->setText("Disable");
            ui->RJ45BAutoNegoLabel->setStyleSheet("background-color: #FFFF0000;");//红色
            ui->rBtnAnegDisableRJ45_2->setChecked(true);
            ui->rBtnAnegEnableRJ45_2->setChecked(false);
        }
        else
        {
            ui->RJ45BAutoNegoLabel->setText("Enable");
            ui->RJ45BAutoNegoLabel->setStyleSheet("background-color: #FF008000;");//绿色
            ui->rBtnAnegDisableRJ45_2->setChecked(false);
            ui->rBtnAnegEnableRJ45_2->setChecked(true);
        }

        if((status & 2) == 0)
        {
            ui->RJ45BLinkStatusLabel->setText("Down");
            ui->RJ45BLinkStatusLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->RJ45BLinkStatusLabel->setText("Up");
            ui->RJ45BLinkStatusLabel->setStyleSheet("background-color: #FF008000;");
        }

        if((status & 0xC) == 0x8)
        {
            ui->RJ45BLinkSpeedLabel->setText("1000 Mbps");
            ui->RJ45BLinkSpeedLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnGeSpeedRJ45_2->setChecked(true);
            ui->rBtnFeSpeedRJ45_2->setChecked(false);
        }
        else {
            ui->RJ45BLinkSpeedLabel->setText("100 Mbps");
            ui->RJ45BLinkSpeedLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnGeSpeedRJ45_2->setChecked(false);
            ui->rBtnFeSpeedRJ45_2->setChecked(true);
        }

        if((status & 0x40) == 0)
        {
            ui->RJ45BDuplexTypeLabel->setText("Half");
            ui->RJ45BDuplexTypeLabel->setStyleSheet("background-color: #FFFF0000;");
            ui->rBtnHalfDuplexRJ45_2->setChecked(true);
            ui->rBtnFullDuplexRJ45_2->setChecked(false);
        }
        else {
            ui->RJ45BDuplexTypeLabel->setText("Full");
            ui->RJ45BDuplexTypeLabel->setStyleSheet("background-color: #FF008000;");
            ui->rBtnHalfDuplexRJ45_2->setChecked(false);
            ui->rBtnFullDuplexRJ45_2->setChecked(true);
        }

        if((status & 0x20) == 0)
        {
            ui->RJ45BModeLabel->setText("Bypass");
            ui->RJ45BModeLabel->setStyleSheet("background-color: #FFFF0000;");
        }
        else {
            ui->RJ45BModeLabel->setText("Mirror");
            ui->RJ45BModeLabel->setStyleSheet("background-color: #FF008000;");
        }
    }
}

void MainWindow::parseConfigDevice(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }
    else if(ret == 0)
    {
        QString message = QString("配置设备成功");
        statusLabel->setText(message);
        return;
    }
}

void MainWindow::parseDeviceConfig(const QString &value)
{
    QStringList tempList = value.split(" ");
    bool ok;

    //解析 T1-A配置信息
    {
        int status = tempList[6].toUInt(&ok, 16);
        if((status & 1) != 0)
        {
            ui->rBtnAnegEnableT1_1->setChecked(true);

            ui->rBtnFeSpeedT1_1->setCheckable(false);
            ui->rBtnGeSpeedT1_1->setCheckable(false);

            ui->rBtnMasterModeT1_1->setText("Force Master");
            ui->rBtnSlaverModeT1_1->setText("Auto");
        }
        else
        {
            ui->rBtnAnegDisableT1_1->setChecked(true);

            ui->rBtnFeSpeedT1_1->setCheckable(true);
            ui->rBtnGeSpeedT1_1->setCheckable(true);

            ui->rBtnMasterModeT1_1->setText("Force Master");
            ui->rBtnSlaverModeT1_1->setText("Force Slaver");
        }

        ui->rBtnFeSpeedT1_1->setChecked((status & 2) != 0);
        ui->rBtnGeSpeedT1_1->setChecked((status & 4) != 0);

        if((status & 8) != 0)
        {
            ui->rBtnMasterModeT1_1->setChecked(true);
        }
        else
        {
            ui->rBtnSlaverModeT1_1->setChecked(true);
        }
    }

    //解析 T1-B配置信息
    {
        int status = tempList[7].toUInt(&ok, 16);
        if((status & 1) != 0)
        {
            ui->rBtnAnegEnableT1_2->setChecked(true);

            ui->rBtnFeSpeedT1_2->setCheckable(false);
            ui->rBtnGeSpeedT1_2->setCheckable(false);

            ui->rBtnMasterModeT1_2->setText("Force Master");
            ui->rBtnSlaverModeT1_2->setText("Auto");
        }
        else
        {
            ui->rBtnAnegDisableT1_2->setChecked(true);

            ui->rBtnFeSpeedT1_2->setCheckable(true);
            ui->rBtnGeSpeedT1_2->setCheckable(true);

            ui->rBtnMasterModeT1_2->setText("Force Master");
            ui->rBtnSlaverModeT1_2->setText("Force Slaver");
        }

        ui->rBtnFeSpeedT1_2->setChecked((status & 2) != 0);
        ui->rBtnGeSpeedT1_2->setChecked((status & 4) != 0);

        if((status & 8) != 0)
        {
            ui->rBtnMasterModeT1_2->setChecked(true);
        }
        else
        {
            ui->rBtnSlaverModeT1_2->setChecked(true);
        }
    }

    //解析 RJ45-A配置信息
    {
        int status = tempList[8].toUInt(&ok, 16);
        if((status & 1) != 0)
        {
            ui->rBtnAnegEnableRJ45_1->setChecked(true);

            ui->rBtnFeSpeedRJ45_1->setEnabled(false);
            ui->rBtnGeSpeedRJ45_1->setEnabled(false);

            ui->rBtnFullDuplexRJ45_1->setEnabled(false);
            ui->rBtnHalfDuplexRJ45_1->setEnabled(false);
        }
        else
        {
            ui->rBtnAnegDisableRJ45_1->setChecked(true);

            ui->rBtnFeSpeedRJ45_1->setEnabled(true);
            ui->rBtnGeSpeedRJ45_1->setEnabled(true);

            ui->rBtnFullDuplexRJ45_1->setEnabled(true);
            ui->rBtnHalfDuplexRJ45_1->setEnabled(true);
        }

        if ((status & 4) != 0)
            ui->rBtnGeSpeedRJ45_1->setEnabled(true);
        else
            ui->rBtnFeSpeedRJ45_1->setEnabled(true);

        if ((status & 0x10) != 0)
            ui->rBtnFullDuplexRJ45_1->setEnabled(true);
        else
            ui->rBtnHalfDuplexRJ45_1->setEnabled(true);
    }

    //解析 RJ45-B配置信息
    {
        int status = tempList[9].toUInt(&ok, 16);
        if((status & 1) != 0)
        {
            ui->rBtnAnegEnableRJ45_2->setChecked(true);

            ui->rBtnFeSpeedRJ45_2->setEnabled(false);
            ui->rBtnGeSpeedRJ45_2->setEnabled(false);

            ui->rBtnFullDuplexRJ45_2->setEnabled(false);
            ui->rBtnHalfDuplexRJ45_2->setEnabled(false);
        }
        else
        {
            ui->rBtnAnegDisableRJ45_2->setChecked(true);

            ui->rBtnFeSpeedRJ45_2->setEnabled(true);
            ui->rBtnGeSpeedRJ45_2->setEnabled(true);

            ui->rBtnFullDuplexRJ45_2->setEnabled(true);
            ui->rBtnHalfDuplexRJ45_2->setEnabled(true);
        }

        if ((status & 4) != 0)
            ui->rBtnGeSpeedRJ45_2->setEnabled(true);
        else
            ui->rBtnFeSpeedRJ45_2->setEnabled(true);

        if ((status & 0x10) != 0)
            ui->rBtnFullDuplexRJ45_2->setEnabled(true);
        else
            ui->rBtnHalfDuplexRJ45_2->setEnabled(true);
    }

    //解析工作模式配置信息
    {
        int status = tempList[10].toUInt(&ok, 16);
        if(status != 0)
        {
            modeLabel->setText("镜像（Mirror）");

            ui->action_Mirror->setChecked(true);
            ui->action_Bypass->setChecked(false);
        }
        else
        {
            modeLabel->setText("直通（Bypass）");

            ui->action_Mirror->setChecked(false);
            ui->action_Bypass->setChecked(true);
        }
    }

    statusLabel->setText("获取配置成功");
}

void MainWindow::parseResetReceive(const QString &value)
{
    QStringList tempList = value.split(" ");

    bool ok;
    int ret = tempList[5].toInt(&ok, 16);
    if(!ok){
        QMessageBox::information(this, "提示", "数据解析失败！");
        return;
    }
    if(ret != 0)
    {
        QString message = QString("命令执行失败，返回：%1").arg(ret);
        QMessageBox::information(this, "提示", message);
        return;
    }
    else
    {
        QString message = QString("恢复出厂设置成功，请重启设备");
        QMessageBox::information(this, "提示", message);
        return;
    }
}

int MainWindow::verify_check_sum(QList<int> value)
{
    if(value.size() < 4){
        return 3;
    }

    //判断长度是否符合
    if(((value[2] << 8) + value[3]) != value.size()){
        return 1;
    }

    QByteArray temp;
    temp.resize(value.size());
    for(int i = 0; i < value.size(); i ++){
        temp[i] = value[i];
    }

    QByteArray ret = calCheckSum(temp, temp.size() - 1);
    if(ret[0] != temp[temp.size() - 1]) {
        return 2;
    }

    return 0;
}

void MainWindow::SlotReceiveData(QString revData)
{
    if(revData.isEmpty())
    {
        return;
    }

    //保持编辑器在光标最后一行
    QTextCursor cursor = ui->textEditReceiveData->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEditReceiveData->setTextCursor(cursor);

    QString result;
    result.clear();

    if(ui->rBtnReceiveHEX->isChecked())
    {
        result = "Receive Data:" + revData + "\n";
    }
    else
    {
        result = receiveHexToAscii(revData);
    }

    //添加一行新数据
    ui->textEditReceiveData->insertPlainText(result);
}

void MainWindow::slotOpenSerialClicked(QAction *action)
{
    if(serialIsOpen(openSerialPorts))
    {
        //添加窗口提示--判断是否关闭串口
        QMessageBox::information(this, "错误", "已有串口打开");
        if(action->isChecked()) {
            action->setChecked(false);
        }
        else {
            action->setChecked(true);
        }
        return;
    }

    //初始化串口属性
    int ret = mySerialPort->initSerialPort(action->text());

    if(ret == 0)
    {
        emit SignalStartThread();
        isSerialOpen = true;
        setMenuWidgetFocus(true);

        action->setChecked(true);
        openSerialPorts.insert(action, true);

        //在关闭串口列表中添加一个元素
        setCloseSerialMenuAction(action->text());
    }
    else if(ret == -1)
    {
        QMessageBox::information(this, "提示", "串口打开失败！");
        action->setChecked(false);
    }
}

void MainWindow::slotCloseSerialClicked(QAction *action)
{
    emit SignalCloseThread();
    setCloseSerialMenuAction("");

    QList<QAction*> openMenu = openSerialPorts.keys();
    for(int i = 0; i < openMenu.size(); i ++)
    {
        if(openMenu[i]->text() == action->text())
        {
            openSerialPorts[openMenu[i]] = false;
            openMenu[i]->setChecked(false);
        }
    }

    QString message = QString("串口[%1]已关闭").arg(action->text());
    setMenuWidgetFocus(false);
    QMessageBox::information(this, "提示", message);
}

void MainWindow::slotBorderCardSelectMenuClicked(QAction *action)
{
    if(action->text() == "VBE1000")
    {
        ui->actionVBE1000->setChecked(true);
        ui->actionVBE1200->setChecked(false);

        ui->groupBox_T1_2->hide();
        ui->groupBox_RJ45_2->hide();

        ui->rBtnFeSpeedRJ45_1->setEnabled(false);
        ui->rBtnGeSpeedRJ45_1->setEnabled(false);
        ui->rBtnFullDuplexRJ45_1->setEnabled(false);
        ui->rBtnHalfDuplexRJ45_1->setEnabled(false);

        ui->T1BAutoNegoLabel->hide();
        ui->T1BForceModeLabel->hide();
        ui->T1BModeLabel->hide();
        ui->T1BLinkSpeedLabel->hide();
        ui->T1BLinkStatusLabel->hide();
        ui->T1BDuplexLabel->hide();
        ui->label_T1_B->hide();

        ui->RJ45BAutoNegoLabel->hide();
        ui->RJ45BDuplexTypeLabel->hide();
        ui->RJ45BForceModeLabel->hide();
        ui->RJ45BModeLabel->hide();
        ui->RJ45BLinkSpeedLabel->hide();
        ui->RJ45BLinkStatusLabel->hide();
        ui->label_RJ45_B->hide();

        ui->labelCurFpgaVersion->hide();
    }
    else if(action->text() == "VBE1200")
    {
        ui->actionVBE1000->setChecked(false);
        ui->actionVBE1200->setChecked(true);

        ui->groupBox_T1_2->show();
        ui->groupBox_RJ45_2->show();

        ui->rBtnFeSpeedRJ45_1->setEnabled(true);
        ui->rBtnGeSpeedRJ45_1->setEnabled(true);
        ui->rBtnFullDuplexRJ45_1->setEnabled(true);
        ui->rBtnHalfDuplexRJ45_1->setEnabled(true);

        ui->T1BAutoNegoLabel->show();
        ui->T1BForceModeLabel->show();
        ui->T1BModeLabel->show();
        ui->T1BLinkSpeedLabel->show();
        ui->T1BLinkStatusLabel->show();
        ui->T1BDuplexLabel->show();
        ui->label_T1_B->show();

        ui->RJ45BAutoNegoLabel->show();
        ui->RJ45BDuplexTypeLabel->show();
        ui->RJ45BForceModeLabel->show();
        ui->RJ45BModeLabel->show();
        ui->RJ45BLinkSpeedLabel->show();
        ui->RJ45BLinkStatusLabel->show();
        ui->label_RJ45_B->show();

        ui->labelCurFpgaVersion->show();
    }

    borderCardLabel->setText(action->text());
}

void MainWindow::slotModeSwitchMenuClicked(QAction *action)
{
    if(!isSerialOpen){

        if(action->text() == "直通（Bypass）")
        {
            if(ui->action_Bypass->isChecked())
                ui->action_Bypass->setChecked(false);
            else
                ui->action_Bypass->setChecked(true);
        }
        else if(action->text() == "镜像（Mirror）")
        {
            if(ui->action_Mirror->isChecked())
                ui->action_Mirror->setChecked(false);
            else
                ui->action_Mirror->setChecked(true);
        }
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QByteArray content;
    content.resize(3);
    content[0] = 0;
    content[1] = 0x18;

    if(action->text() == "直通（Bypass）")
    {
        ui->action_Bypass->setChecked(true);
        ui->action_Mirror->setChecked(false);
        content[2] = 0x33;
    }
    else if(action->text() == "镜像（Mirror）")
    {
        ui->action_Bypass->setChecked(false);
        ui->action_Mirror->setChecked(true);
        content[2] = 0;
    }

    modeLabel->setText(action->text());

    send_Cmd(0x69, content);
}

void MainWindow::slotClearReceiveDataClicked()
{
    //接收输入框文本改变信号槽连接
    disconnect(ui->textEditReceiveData, SIGNAL(textChanged()), this, SLOT(slotTextEditReceiveChanged()));

    ui->textEditReceiveData->clear();

    //接收输入框文本改变信号槽连接
    connect(ui->textEditReceiveData, SIGNAL(textChanged()), this, SLOT(slotTextEditReceiveChanged()));
}

void MainWindow::slotSendDataClicked()
{
    if(!isSerialOpen)
    {
        QMessageBox::information(this, "错误", "串口未打开");
        return;
    }

    QByteArray sendData;
    sendData.clear();
    //判断数据类型是否选择HEX
    if(ui->rBtnSendDataHex->isChecked())
    {
        QStringList hexString = ui->textEditSendData->toPlainText().split(" ");
        for(int i = 0; i < hexString.size(); i ++)
        {
            sendData.append(QByteArray::fromHex(hexString[i].toLocal8Bit()));
        }
    }
    else
    {//数据类型选择为ASCII
        QString asciiString = ui->textEditSendData->toPlainText();
        QStringList asciiStrList = asciiString.split(" ");
        int size = asciiStrList.size();
        if(size % 2 != 0)
        {
            QMessageBox::information(this, "错误", "输入内容数据量错误，请检查后重新输入");
            return;
        }

        QByteArray tempData;
        tempData.clear();
        for(int i = 0; i < asciiStrList.size(); i ++)
        {
            tempData.append(QByteArray::fromHex(asciiStrList[i].toLocal8Bit()));
        }

        for(int i = 0; i < tempData.size(); i += 2)
        {
            QChar highChar = QChar(tempData[i]);
            QChar lowChar = QChar(tempData[i+1]);

            QString str = QString(highChar) + QString(lowChar);
            sendData.append(QByteArray::fromHex(str.toLocal8Bit()));
        }
    }

    if (!sendData.isEmpty() && !sendData.isNull())
    {
        mySerialPort->serialPortSendData(sendData);
    }
}

void MainWindow::slotSelectPathClicked()
{
    QString fileFull, fileName;
    QFileInfo fileinfo;
    //获取整个文件名
    fileFull = QFileDialog::getOpenFileName(this,tr("选择文件"),"/",tr("(*)"));

    //获取文件信息
    fileinfo = QFileInfo(fileFull);

    //获取文件名
    fileName = fileinfo.fileName();

    //设置文件名显示
    ui->lineEditPath->setText(fileFull);
}

void MainWindow::slotGetVersionClicked()
{
    if(!isSerialOpen)
    {
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    send_Cmd(0x70, QByteArray());
}

void MainWindow::slotReceiveDataTypeChanged()
{
    QString textStr = ui->textEditReceiveData->toPlainText();
    QString result;
    result.clear();

    if(ui->rBtnReceiveASCII->isChecked())
    {
        result = receiveHexToAscii(textStr);
    }

    if(ui->rBtnReceiveHEX->isChecked())
    {
        result = receiveAsciiToHex(textStr);
    }


    //接收输入框文本改变信号槽连接
    disconnect(ui->textEditReceiveData, SIGNAL(textChanged()), this, SLOT(slotTextEditReceiveChanged()));

    ui->textEditReceiveData->clear();

    //接收输入框文本改变信号槽连接
    connect(ui->textEditReceiveData, SIGNAL(textChanged()), this, SLOT(slotTextEditReceiveChanged()));
    ui->textEditReceiveData->insertPlainText(result);
}

void MainWindow::slotSendDataTypeChanged()
{
    QString textStr = ui->textEditSendData->toPlainText();
    QString result;
    result.clear();

    textStr = textStr.replace("\n", "");
    if(ui->rBtnSendDataASCII->isChecked()) {
        result = hexToAscii(textStr);
    }

    if(ui->rBtnSendDataHex->isChecked()) {
        result = asciiToHex(textStr);
    }

    ui->textEditSendData->clear();
    ui->textEditSendData->insertPlainText(result);
}

void MainWindow::slotTextEditReceiveChanged()
{
    //获取最新接收的数据
    QString strPlainText = ui->textEditReceiveData->toPlainText();
    QStringList tempList = strPlainText.split("\n");

    int size = tempList.size();
    QString result = tempList[size - 2];
    QStringList dataList = result.split(":");
    if(ui->rBtnReceiveHEX->isChecked()) {
        parseHexReceiveData(dataList[1]);
    }
    else {
        parseAsciiReceiveData(dataList[1]);
    }

}

void MainWindow::slotBtnMdioReadClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QString phyAddrStr = ui->lineEditPhyAddr->text();
    QString devAddrStr = ui->lineEditDevAddr->text();
    QString regAddrStr = ui->lineEditRegAddr->text();

    uint phyAddr = 0;
    uint devAddr = 0;
    uint regAddr = 0;

    if(!lineEditTextToUint(phyAddrStr, phyAddr)){
        QString statusText = QString("Invalid MDIO PHY:%1!").arg(phyAddrStr);
        statusLabel->setText(statusText);
        return;
    }
    if(!lineEditTextToUint(devAddrStr, devAddr) || devAddr > 0x1F){
        QString statusText = QString("Invalid MDIO DEV:%1!").arg(devAddrStr);
        statusLabel->setText(statusText);
        return;
    }
    if(!lineEditTextToUint(regAddrStr, regAddr)){
        QString statusText = QString("Invalid MDIO REG:%1!").arg(regAddrStr);
        statusLabel->setText(statusText);
        return;
    }

    QByteArray contentData;
    contentData.clear();
    contentData.append(phyAddr);
    contentData.append(devAddr);
    contentData.append(regAddr >> 8);
    contentData.append(regAddr & 0xFF);

    int ret = send_Cmd(0x61, contentData);
    if(ret)
    {
        statusLabel->setText("读MDIO寄存器成功");
    }
    else
    {
        statusLabel->setText("读MDIO寄存器失败");
    }
}

void MainWindow::slotBtnMdioWriteClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QString phyAddrStr = ui->lineEditPhyAddr->text();
    QString devAddrStr = ui->lineEditDevAddr->text();
    QString regAddrStr = ui->lineEditRegAddr->text();
    QString valueStr = ui->lineEditMdioValue->text();

    uint phyAddr = 0;
    uint devAddr = 0;
    uint regAddr = 0;
    uint value = 0;

    if(!lineEditTextToUint(phyAddrStr, phyAddr)){
        QString statusText = QString("Invalid MDIO PHY:%1!").arg(phyAddrStr);
        statusLabel->setText(statusText);
        return;
    }
    if(!lineEditTextToUint(devAddrStr, devAddr) || devAddr > 0x1F){
        QString statusText = QString("Invalid MDIO DEV:%1!").arg(devAddrStr);
        statusLabel->setText(statusText);
        return;
    }
    if(!lineEditTextToUint(regAddrStr, regAddr)){
        QString statusText = QString("Invalid MDIO REG:%1!").arg(regAddrStr);
        statusLabel->setText(statusText);
        return;
    }
    if(!lineEditTextToUint(valueStr, value)){
        QString statusText = QString("Invalid MDIO VALUE:%1!").arg(valueStr);
        statusLabel->setText(statusText);
        return;
    }

    QByteArray contentData;
    contentData.clear();
    contentData.append(phyAddr);
    contentData.append(devAddr);
    contentData.append(regAddr >> 8);
    contentData.append(regAddr & 0xFF);
    contentData.append(value >> 8);
    contentData.append(value & 0xFF);

    int ret = send_Cmd(0x62, contentData);
    if(ret)
    {
        statusLabel->setText("写MDIO寄存器成功");
    }
    else
    {
        statusLabel->setText("写MDIO寄存器失败");
    }
}

void MainWindow::slotBtnFpgaReadClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QString fpgaAddrStr = ui->lineEditFpgaAddr->text();
    uint fpgaAddr = 0;
    if(!lineEditTextToUint(fpgaAddrStr, fpgaAddr))
    {
        QString statusText = QString("Invalid FPGA Addr:%1!").arg(fpgaAddrStr);
        statusLabel->setText(statusText);
        return;
    }

    QByteArray contentData;
    contentData.clear();
    contentData.append(fpgaAddr >> 8);
    contentData.append(fpgaAddr & 0xFF);

    int ret = send_Cmd(0x68, contentData);
    if(ret)
    {
        statusLabel->setText("访问FPGA寄存器成功");
    }
    else
    {
        statusLabel->setText("访问FPGA寄存器超时/失败");
    }
}

void MainWindow::slotBtnFpgaWriteClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QString fpgaAddrStr = ui->lineEditFpgaAddr->text();
    uint fpgaAddr = 0;
    if(!lineEditTextToUint(fpgaAddrStr, fpgaAddr))
    {
        QString statusText = QString("Invalid FPGA Addr:%1!").arg(fpgaAddrStr);
        statusLabel->setText(statusText);
        return;
    }

    QString fpgaValueStr = ui->lineEditFpgaValue->text();
    uint value = 0;
    if(!lineEditTextToUint(fpgaValueStr, value))
    {
        QString statusText = QString("Invalid FPGA Addr:%1!").arg(fpgaValueStr);
        statusLabel->setText(statusText);
        return;
    }

    QByteArray contentData;
    contentData.clear();
    contentData.append(fpgaAddr >> 8);
    contentData.append(fpgaAddr & 0xFF);
    contentData.append(value);

    int ret = send_Cmd(0x69, contentData);
    if(ret)
    {
        statusLabel->setText("写FPGA寄存器成功");
    }
    else
    {
        statusLabel->setText("写FPGA寄存器失败");
    }
}

void MainWindow::slotBtnBurnClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QString fileName = ui->lineEditPath->text();
    if(fileName.isEmpty())
    {
        statusLabel->setText("Firmware file path is empty!");
        QMessageBox::information(this, "提示", "Firmware file path is empty!");
        return;
    }

    if(!isBurnWriteThreadStart)
    {
        bool isMcu = ui->rBtnMcu->isChecked();
        QString fileName = ui->lineEditPath->text();

        burnWritThread->initBurn(mySerialPort, fileName, isMcu, pProgressBar);
        burnWritThread->exitBurnFlash = false;

        //burnWritThread->start();
        isBurnWriteThreadStart = true;
        ui->BtnBurn->setText("停止");

        emit SignalStartBurnThread();
    }
    else
    {
        if(isBurnWriteThreadStart)
        {
            burnWritThread->exitBurnFlash = true;
            isBurnWriteThreadStart = false;
            burnWritThread->wait(1000);
        }
        emit SignalCloseBurnThread();

        //delete burnWritThread;
        //burnWritThread = NULL;
        ui->BtnBurn->setText("烧写");

        pProgressBar->setValue(0);
        pProgressBar->setTextVisible(true);
    }
}

void MainWindow::slotBurnBtnTextUpdate(QString value)
{    
    burnWritThread->exitBurnFlash = true;
    ui->BtnBurn->setText("烧写");
    isBurnWriteThreadStart = false;

    QString message = QString("烧写结束%1").arg(value);
    QMessageBox::information(this, "提示", message);

    emit SignalCloseBurnThread();
}

void MainWindow::slotBtnSetT1AClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    int configuration = 0;
    configuration += (ui->rBtnAnegEnableT1_1->isChecked() ? 0x1 : 0);
    configuration += (ui->rBtnFeSpeedT1_1->isChecked() ? 0x2 : 0);
    configuration += (ui->rBtnGeSpeedT1_1->isChecked() ? 0x4 : 0);
    configuration += (ui->rBtnMasterModeT1_1->isChecked() ? 0x8 : 0);

    QByteArray content;
    int initByte = 0;
    content.clear();
    content.append(initByte);
    content.append(configuration);

    send_Cmd(0xA2, content);
}

void MainWindow::slotBtnSetT1BClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    int configuration = 0;
    configuration += (ui->rBtnAnegEnableT1_2->isChecked() ? 0x1 : 0);
    configuration += (ui->rBtnFeSpeedT1_2->isChecked() ? 0x2 : 0);
    configuration += (ui->rBtnGeSpeedT1_2->isChecked() ? 0x4 : 0);
    configuration += (ui->rBtnMasterModeT1_2->isChecked() ? 0x8 : 0);

    QByteArray content;
    int initByte = 1;
    content.clear();
    content.append(initByte);
    content.append(configuration);

    send_Cmd(0xA2, content);
}

void MainWindow::slotBtnSetRJ45AClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    int configuration = 0;
    configuration += (ui->rBtnAnegEnableRJ45_1->isChecked() ? 0x1 : 0);
    configuration += (ui->rBtnFeSpeedRJ45_1->isChecked() ? 0x2 : 0);
    configuration += (ui->rBtnGeSpeedRJ45_1->isChecked() ? 0x4 : 0);
    configuration += (ui->rBtnFullDuplexRJ45_1->isChecked() ? 0x10 : 0);

    QByteArray content;
    int initByte = 2;
    content.clear();
    content.append(initByte);
    content.append(configuration);

    send_Cmd(0xA2, content);

}

void MainWindow::slotBtnSetRJ45BClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    int configuration = 0;
    configuration += (ui->rBtnAnegEnableRJ45_2->isChecked() ? 0x1 : 0);
    configuration += (ui->rBtnFeSpeedRJ45_2->isChecked() ? 0x2 : 0);
    configuration += (ui->rBtnGeSpeedRJ45_2->isChecked() ? 0x4 : 0);
    configuration += (ui->rBtnFullDuplexRJ45_2->isChecked() ? 0x10 : 0);

    QByteArray content;
    int initByte = 3;
    content.clear();
    content.append(initByte);
    content.append(configuration);

    send_Cmd(0xA2, content);
}

void MainWindow::slotBtnStatusFreshClicked()
{
    if(isAutoRefresh)
    {
        ui->BtnStatusFresh->setText("自动刷新");
        emit SignalCloseAutoRefreshThread();
        isAutoRefresh = false;
    }
    else
    {
        ui->BtnStatusFresh->setText("取消刷新");

        emit SignalStartAutoRefreshThread();

        isAutoRefresh = true;
    }
}

void MainWindow::slotAutoRefreshConfigData()
{
    if(!isSerialOpen)
    {
        statusLabel->setText("串口未打开");
        return;
    }

    send_Cmd(0x71, QByteArray());
}

void MainWindow::slotDebugWindow()
{
    if(isShowDebugWindow)
    {
        isShowDebugWindow = false;
        debugDialog->show();

        connect(debugDialog, SIGNAL(signalShowDebug()), this, SLOT(slotDebugDialogShow()));
    }
    else
    {
        isShowDebugWindow = true;
        ui->groupBoxSerialReceive->setEnabled(false);
        ui->groupBoxSerialSend->setEnabled(false);
        ui->groupBoxMdioInterface->setEnabled(false);
        ui->groupBoxFpgaInterface->setEnabled(false);
    }
}

void MainWindow::slotDebugDialogShow()
{
    ui->groupBoxSerialReceive->setEnabled(true);
    ui->groupBoxSerialSend->setEnabled(true);
    ui->groupBoxMdioInterface->setEnabled(true);
    ui->groupBoxFpgaInterface->setEnabled(true);
}

void MainWindow::slotSynConfigActionClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    send_Cmd(0xA1, QByteArray());
}

void MainWindow::slotDataResetActionClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    int ret = QMessageBox::information(this, "恢复出厂设置",
                             "设备即将恢复出厂设置，请确认",
                             QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {
        send_Cmd(0xA3, QByteArray());
    }
}

void MainWindow::slotSendXmodemActionClicked()
{
    if(!isSerialOpen){
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    if(!isSendXModem)
    {
        QString filepath;
        //获取整个文件名
        filepath = QFileDialog::getOpenFileName(this,tr("选择文件"),"/",tr("(*)"));

        mySendXModemThread = new XModemThread();
        mySendXModemThread->init_xmodem(mySerialPort, pProgressBar, filepath);

        sendXmodemAction->setText("取消发送");

        setMenuWidgetFocus(false);

        connect(mySendXModemThread, SIGNAL(SignalSendXModemEnd()), this, SLOT(slotSendXModemEnd()));
        connect(this, SIGNAL(SignalStartSendXModemThread()), mySendXModemThread, SLOT(slotStartThread()));
        connect(this, SIGNAL(SignalCloseSendXModemThread()), mySendXModemThread, SLOT(slotStopThread()));

        emit SignalStartSendXModemThread();
    }
    else
    {
        sendXmodemAction->setText("发送XModem");
        setMenuWidgetFocus(true);
        emit SignalCloseSendXModemThread();
    }

}

void MainWindow::slotSendXModemEnd()
{
    sendXmodemAction->setText("发送XModem");
    setMenuWidgetFocus(true);
    QMessageBox::information(this, "提示", "发送XModem结束");
}

void MainWindow::slotResetBoardActionClicked()
{
    if(!isSerialOpen) {
        statusLabel->setText("请先打开串口");
        QMessageBox::information(this, "提示", "请先打开串口！");
        return;
    }

    QByteArray content;
    content.resize(1);
    content[1] = 5;

    send_Cmd(0x66, content);
}

void MainWindow::slotRBtnT1AAnegGroupChanged(bool status)
{
    if(ui->rBtnAnegEnableT1_1->isChecked()) {
        ui->rBtnMasterModeT1_1->setText("Force Master");
        ui->rBtnSlaverModeT1_1->setText("Auto");
    }
    else {
        ui->rBtnMasterModeT1_1->setText("Force Master");
        ui->rBtnSlaverModeT1_1->setText("Force Slaver");
    }
}

void MainWindow::slotRBtnT1BAnegGroupChanged(bool status)
{
    if(ui->rBtnAnegEnableT1_2->isChecked()) {
        ui->rBtnMasterModeT1_2->setText("Force Master");
        ui->rBtnSlaverModeT1_2->setText("Auto");
    }
    else {
        ui->rBtnMasterModeT1_2->setText("Force Master");
        ui->rBtnSlaverModeT1_2->setText("Force Slaver");
    }
}

void MainWindow::slotRBtnRJ45AAnegGroupChanged(bool status)
{
    if(ui->rBtnAnegDisableRJ45_1->isChecked()) {
        ui->rBtnFeSpeedRJ45_1->setEnabled(false);
        ui->rBtnGeSpeedRJ45_1->setEnabled(false);
        ui->rBtnFullDuplexRJ45_1->setEnabled(false);
        ui->rBtnHalfDuplexRJ45_1->setEnabled(false);
    }
    else {
        ui->rBtnFeSpeedRJ45_1->setEnabled(true);
        ui->rBtnGeSpeedRJ45_1->setEnabled(true);
        ui->rBtnFullDuplexRJ45_1->setEnabled(true);
        ui->rBtnHalfDuplexRJ45_1->setEnabled(true);
    }
}

void MainWindow::slotRBtnRJ45BAnegGroupChanged(bool status)
{
    if(ui->rBtnAnegDisableRJ45_2->isChecked()) {
        ui->rBtnFeSpeedRJ45_2->setEnabled(false);
        ui->rBtnGeSpeedRJ45_2->setEnabled(false);
        ui->rBtnFullDuplexRJ45_2->setEnabled(false);
        ui->rBtnHalfDuplexRJ45_2->setEnabled(false);
    }
    else {
        ui->rBtnFeSpeedRJ45_2->setEnabled(true);
        ui->rBtnGeSpeedRJ45_2->setEnabled(true);
        ui->rBtnFullDuplexRJ45_2->setEnabled(true);
        ui->rBtnHalfDuplexRJ45_2->setEnabled(true);
    }
}


