#include "FormNetConfig.h"
#include "ServiceException.h"
#include "ui_FormNetConfig.h"

#include "UdpThread.h"
#include "TcpServerThread.h"
#include "TcpClientThread.h"

#include <QMessageBox>

FormNetConfig::FormNetConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNetConfig)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog);
    this->setFixedSize(this->width(), this->height());

    ui->BtnOk->setShortcut(Qt::Key_Enter);
    ui->BtnOk->setShortcut(Qt::Key_Return);

    ui->BtnCancel->setShortcut(Qt::Key_Escape);

    onlineTool = new OnlineTool();

    initWidget();
}

FormNetConfig::~FormNetConfig()
{
    delete ui;
}

void FormNetConfig::initWidget()
{
    ui->cBoxNetMode->setCurrentIndex(3);
    slotCboxNetModeCurrentIndexChanged(3);
    connect(ui->cBoxNetMode, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCboxNetModeCurrentIndexChanged(int)));
    connect(ui->BtnOk, SIGNAL(clicked()), this, SLOT(slotBtnOkClicked()));
    connect(ui->BtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));

    connect(this, SIGNAL(signalStartUDPThread()), UdpThread::instance(), SLOT(slotStartThread()));
    connect(this, SIGNAL(signalStartTCPServerThread()), TcpServerThread::instance(), SLOT(slotStartThread()));
    connect(this, SIGNAL(signalStartTCPClientThread()), TcpClientThread::instance(), SLOT(slotStartThread()));
}

void FormNetConfig::slotCboxNetModeCurrentIndexChanged(int index)
{
    switch (index) {
    case 0: {
        ui->labelhostName->setVisible(false);
        ui->lineEditHostName->setVisible(false);
        ui->labelPort->setText("监听端口：");
        break;
    }
    case 1: {
        ui->labelhostName->setVisible(true);
        ui->lineEditHostName->setVisible(true);
        ui->labelPort->setText("目的端口：");
        break;
    }
    case 2: {
        ui->labelhostName->setVisible(false);
        ui->lineEditHostName->setVisible(false);
        ui->labelPort->setText("监听端口：");
        break;
    }
    case 3: {
        ui->labelhostName->setVisible(true);
        ui->lineEditHostName->setVisible(true);
        ui->labelPort->setText("目的端口：");
        break;
    }
    default:
        break;
    }
}

void FormNetConfig::slotBtnOkClicked()
{
    switch (ui->cBoxNetMode->currentIndex()) {
    case 0: {
        try {
            UdpThread::instance()->setListenPort(ui->lineEditPort->text().toInt());
        } catch (ServiceException& e) {
            QMessageBox::information(this, "提示", e.getMessage());
            return;
        }

        emit signalCurrentStatusTips(QString("当前监听端口为：[%1]").arg(ui->lineEditPort->text()));
        emit signalStartUDPThread();
        break;
    }
    case 1: {
        UdpThread::instance()->setTargetInfo(ui->lineEditHostName->text(), ui->lineEditPort->text().toInt());
        if(!onlineTool->IsOnline(ui->lineEditHostName->text(), 1000)) {
            QMessageBox::information(this, "提示", QString("[%1：%2]连接失败!").arg(ui->lineEditHostName->text(), ui->lineEditPort->text()));
            return;
        }

        emit signalCurrentStatusTips(QString("目标地址端口为：[%1：%2]").arg(ui->lineEditHostName->text(), ui->lineEditPort->text()));
        emit signalStartUDPThread();
        break;
    }
    case 2: {
        TcpServerThread::instance()->initNetConnect(ui->lineEditPort->text().toInt());
        emit signalCurrentStatusTips(QString("当前监听端口为：[%1]").arg(ui->lineEditPort->text()));
        emit signalStartTCPServerThread();
        break;
    }
    case 3: {
        try {
            TcpClientThread::instance()->initNetConnection(ui->lineEditHostName->text(), ui->lineEditPort->text().toInt());
            if(!onlineTool->IsOnline(ui->lineEditHostName->text(), 1000)) {
                QMessageBox::information(this, "提示", QString("[%1：%2]连接失败!").arg(ui->lineEditHostName->text(), ui->lineEditPort->text()));
                return;
            }
        } catch (ServiceException& e) {
            QMessageBox::information(this, "提示", e.getMessage());
            return;
        }

        emit signalCurrentStatusTips(QString("目标地址端口为：[%1：%2]").arg(ui->lineEditHostName->text(), ui->lineEditPort->text()));
        emit signalStartTCPClientThread();
        break;
    }
    default:
        break;
    }    

    this->close();
}

void FormNetConfig::slotBtnCancelClicked()
{
    this->close();
}
