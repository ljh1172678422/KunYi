#include "MultiComboBox.h"

#include <QLineEdit>
#include <QMouseEvent>

MultiComboBox::MultiComboBox(QWidget *parent)
    :QComboBox(parent)
{
    //为ComboBox 设置编辑框
    pLineEdit = new QLineEdit(this);
    pLineEdit->setReadOnly(true);
    this->setLineEdit(pLineEdit);

    //设置ComboBox 下拉界面
    pListView = new QListView(this);
    pListView->installEventFilter(this);
    this->setView(pListView);

    //设置ComboBox 数据模型
    itemModel = new QStandardItemModel(this);
    this->setModel(itemModel);

    connect(this, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
}

MultiComboBox::~MultiComboBox()
{}

void MultiComboBox::addItems(QList<MenuItem *> menus)
{
    QStandardItem *newItem;
    for(MenuItem* menuItem : menus){
        newItem = new QStandardItem(menuItem->getMenuName());

        //不加这一段代码，不出现单选框
        newItem->setCheckState(Qt::Checked);
        newItem->setCheckState(menuItem->getIsChecked() ? Qt::Checked : Qt::Unchecked);
        newItem->setData(menuItem->getMenuId());
        itemModel->appendRow(newItem);
    }

    updateText();
}

void MultiComboBox::removeItem(int row)
{
    itemModel->removeRow(row);
    updateText();
}

void MultiComboBox::clear()
{
    itemModel->clear();
    updateText();
}

QStringList MultiComboBox::getItemsList()
{
    QStringList result;
    QString text = pLineEdit->text();
    if(!text.isEmpty()){
        result = text.split(";");
    }

    return result;
}

QList<int> MultiComboBox::getItemIds()
{
    QList<int> result;
    for(int i = 0; i < itemModel->rowCount(); i ++){
        QStandardItem *item = itemModel->item(i);
        if(item->checkState() == Qt::Checked){
            result << item->data().toInt();
        }
    }

    return result;
}

void MultiComboBox::setAllItemCheckedState(Qt::CheckState checkState)
{
    for(int i = 0; i < itemModel->rowCount(); i ++){
        QStandardItem* item = itemModel->item(i);
        item->setCheckState(checkState);
    }
}

void MultiComboBox::hidePopup()
{
    int width = this->view()->width();
    int height = this->view()->height();
    int x = QCursor::pos().x() - mapToGlobal(geometry().topLeft()).x() + geometry().x();
    int y = QCursor::pos().y() - mapToGlobal(geometry().topLeft()).y() + geometry().y();

    QRect rectView(0, this->height(), width, height);
    if(!rectView.contains(x, y)){
        QComboBox::hidePopup();
    }
}

bool MultiComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QListView *listView = qobject_cast<QListView*>(watched);
            if (nullptr != listView) {
                int row = listView->currentIndex().row();
                if (row != -1) {
                    slotActivated(row);
                }
            }
            return true;
        }
    }
    return QComboBox::eventFilter(watched, event);
}

void MultiComboBox::updateText()
{
    QStringList strs;
    for(int i = 1; i < itemModel->rowCount(); i ++){
        QStandardItem *item = itemModel->item(i);
        if (item->checkState() == Qt::Checked) {
            strs << item->text();
        }
    }

    pLineEdit->setText(strs.join(";"));
    pLineEdit->setToolTip(strs.join("\n"));
    pLineEdit->setCursorPosition(0);
}

void MultiComboBox::wheelEvent(QWheelEvent *event)
{
    if(event != NULL){
        return;
    }
}

void MultiComboBox::slotActivated(int row)
{
    if(row == 0){
        setAllItemCheckedState(itemModel->item(row)->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
    }
    else{
        QStandardItem* item = itemModel->item(row);
        Qt::CheckState checkState = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(checkState);
    }
    updateText();
}
