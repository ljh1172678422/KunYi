#include "FormSerialPortConfig.h"
#include "ui_FormSerialPortConfig.h"

#include <QSerialPortInfo>
#include "SerialPortThread.h"

FormSerialPortConfig::FormSerialPortConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSerialPortConfig)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->setFixedSize(this->width(),this->height());

    initWidget();
}

FormSerialPortConfig::~FormSerialPortConfig()
{
    delete ui;
}

void FormSerialPortConfig::initWidget()
{
    auto serialList = QSerialPortInfo::availablePorts();

    for(int i = 0; i < serialList.size(); i ++) {
        auto portInfo = serialList[i];
        ui->cBoxSerialPort->addItem(QString("%1:%2").arg(portInfo.portName(), portInfo.description()));
    }

    connect(ui->BtnOK, SIGNAL(clicked()), this, SLOT(slotBtnOkClicked()));
    connect(ui->BtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));

    connect(this, SIGNAL(signalSerialPortStart()), SerialPortThread::instance(), SLOT(slotStartThread()));
    connect(SerialPortThread::instance(), SIGNAL(signalSerialPortThreadSuccess()), this, SLOT(slotBtnCancelClicked()));
}

QSerialPort::Parity FormSerialPortConfig::getParity(int parity)
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

QSerialPort::BaudRate FormSerialPortConfig::getBaudRate(int baudRate)
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

QSerialPort::DataBits FormSerialPortConfig::getDataBits(int dataBits)
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

QSerialPort::StopBits FormSerialPortConfig::getStopBits(int stopBits)
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

void FormSerialPortConfig::slotBtnOkClicked()
{
    auto serialName = ui->cBoxSerialPort->currentText();
    auto baudRate = getBaudRate(ui->cBoxBaud->currentIndex());
    auto dataBits = getDataBits(ui->cBoxDataBits->currentIndex());
    auto stopBits = getStopBits(ui->cBoxStopBits->currentIndex());
    auto parity = getParity(ui->cBoxCheckBits->currentIndex());

    SerialPortThread::instance()->initSerialPort(serialName, baudRate, dataBits, stopBits, parity);

    emit signalSerialPortStart();
}

void FormSerialPortConfig::slotBtnCancelClicked()
{
    this->close();
}
