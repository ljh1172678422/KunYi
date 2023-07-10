#include "CustomToolButton.h"

CustomToolButton::CustomToolButton(QWidget *parent)
    : QToolButton(parent),
      toolButtonId(-1),
      tBtnLinkStatus(false)
{

    connect(this, SIGNAL(clicked()), this, SLOT(slotToolButtonClicked()));
}

CustomToolButton::~CustomToolButton()
{}

int CustomToolButton::getToolButtonId() const
{
    return toolButtonId;
}

void CustomToolButton::setToolButtonId(int newToolButtonId)
{
    toolButtonId = newToolButtonId;
}

void CustomToolButton::setLinkStatus(bool status)
{
    if(status){
        setOnline();
        tBtnLinkStatus = true;
    }
    else{
        setOffline();
        tBtnLinkStatus = false;
    }
}

bool CustomToolButton::getLinkStatus()
{
    return tBtnLinkStatus;
}

void CustomToolButton::slotToolButtonClicked()
{
    emit currentPortButton(toolButtonId);
}

void CustomToolButton::setOffline()
{
    this->setIcon(QIcon(":/icons/Offline.png"));
}

void CustomToolButton::setOnline()
{
    this->setIcon(QIcon(":/icons/Online.png"));
}
