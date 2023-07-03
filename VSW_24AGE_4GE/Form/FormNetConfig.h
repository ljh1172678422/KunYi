#ifndef FORMNETCONFIG_H
#define FORMNETCONFIG_H

#include <QWidget>
#include "OnlineTool.h"

namespace Ui {
class FormNetConfig;
}

/**
 * @brief The FormNetConfig class   网络配置界面类
 */
class FormNetConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FormNetConfig(QWidget *parent = nullptr);
    ~FormNetConfig();

    void initWidget();

signals:
    void signalCurrentStatusTips(QString str);

    void signalStartUDPThread();

    void signalStartTCPServerThread();

    void signalStartTCPClientThread();

private slots:
    void slotCboxNetModeCurrentIndexChanged(int index);

    void slotBtnOkClicked();

    void slotBtnCancelClicked();

private:
    Ui::FormNetConfig *ui;

    OnlineTool* onlineTool;
};

#endif // FORMNETCONFIG_H
