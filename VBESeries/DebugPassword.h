#ifndef DEBUGPASSWORD_H
#define DEBUGPASSWORD_H

#include <QDialog>

namespace Ui {
class DebugPassword;
}

class DebugPassword : public QDialog
{
    Q_OBJECT

public:
    explicit DebugPassword(QWidget *parent = nullptr);
    ~DebugPassword();

signals:
    void signalShowDebug();

private slots:
    void slotBtnOKClicked();

    void slotBtnCancelClicked();

private:
    Ui::DebugPassword *ui;

    QString userPwd;
};

#endif // DEBUGPASSWORD_H
