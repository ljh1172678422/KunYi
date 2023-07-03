#ifndef FORMSERIALPORTCONFIG_H
#define FORMSERIALPORTCONFIG_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class FormSerialPortConfig;
}

/**
 * @brief The FormSerialPortConfig class    串口通讯配置界面类
 */
class FormSerialPortConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormSerialPortConfig(QWidget *parent = nullptr);
    ~FormSerialPortConfig();

signals:
    void signalSerialPortStart();

private:
    void initWidget();

    QSerialPort::Parity getParity(int parity);

    QSerialPort::BaudRate getBaudRate(int baudRate);

    QSerialPort::DataBits getDataBits(int dataBits);

    QSerialPort::StopBits getStopBits(int stopBits);

private slots:
    void slotBtnOkClicked();

    void slotBtnCancelClicked();

private:
    Ui::FormSerialPortConfig *ui;
};

#endif // FORMSERIALPORTCONFIG_H
