#include "DebugPassword.h"
#include "ui_DebugPassword.h"

#include <QMessageBox>

DebugPassword::DebugPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugPassword),
    userPwd("Admin")
{
    ui->setupUi(this);
    setWindowTitle("调试");
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->BtnOK, SIGNAL(clicked()), this, SLOT(slotBtnOKClicked()));
    connect(ui->BtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()));
}

DebugPassword::~DebugPassword()
{
    delete ui;
}

void DebugPassword::slotBtnOKClicked()
{
    QString tempPwd = ui->lineEditPwd->text();
    if(tempPwd == userPwd)
    {
        emit signalShowDebug();
        this->hide();
    }
    else{
        QMessageBox::information(this, "提示", "密码错误，请重新输入！");
        return;
    }
}

void DebugPassword::slotBtnCancelClicked()
{
    this->hide();
}
