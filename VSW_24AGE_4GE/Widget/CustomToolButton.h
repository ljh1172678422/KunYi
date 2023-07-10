#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QToolButton>
#include <QObject>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    CustomToolButton(QWidget* parent = nullptr);
    ~CustomToolButton();

    int getToolButtonId() const;
    void setToolButtonId(int newToolButtonId);

    void setLinkStatus(bool status);

    bool getLinkStatus();

signals:
    void currentPortButton(int);

private slots:
    void slotToolButtonClicked();

private:
    void setOffline();

    void setOnline();

private:
    int toolButtonId;
    bool tBtnLinkStatus;
};

#endif // CUSTOMTOOLBUTTON_H
