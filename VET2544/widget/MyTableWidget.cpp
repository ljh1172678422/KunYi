#include "MyTableWidget.h"

#include <QMenu>
#include <QAction>
#include <QComboBox>
#include <QContextMenuEvent>

MyTableWidget::MyTableWidget(QWidget *parent)
    : QTableWidget(parent)
{}

MyTableWidget::~MyTableWidget()
{}

QList<QStringList> MyTableWidget::getItemList()
{
    QList<QStringList> result;
    result.clear();

    int rowCount = this->rowCount();
    int colCount = this->columnCount();

    for(int row = 0; row < rowCount; row++){
        QStringList data;
        data.clear();

        for(int col = 0; col < colCount; col ++){
            if(col == 1 || col == colCount - 1){
                QComboBox* comboBox = (QComboBox*)this->cellWidget(row, col);
                data.append(QString::number(comboBox->currentIndex()));
            }
            else{
                data.append(this->item(row, col)->text());
            }
        }

        result.append(data);
    }

    return result;
}

void MyTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    if(this->rowCount() != 0){
        QAction *deleteAction = menu.addAction(tr("删除当前行"));
        deleteAction->setToolTip("未选中则删除最后一行");
        QAction *addBeforeAction = menu.addAction(tr("在行前添加"));
        QAction *addAfterAction = menu.addAction(tr("在行后添加"));
        connect(addBeforeAction, &QAction::triggered, this, &MyTableWidget::addBeforeRow);
        connect(addAfterAction, &QAction::triggered, this, &MyTableWidget::addAfterRow);
        connect(deleteAction, &QAction::triggered, this, &MyTableWidget::deleteSelectedRows);
    }
    else{
        QAction *addAfterAction = menu.addAction(tr("添加"));
        connect(addAfterAction, &QAction::triggered, this, &MyTableWidget::addAfterRow);
    }

    menu.exec(event->globalPos());
}

void MyTableWidget::deleteSelectedRows()
{
    int row = this->currentRow();

    this->removeRow(row);
}

void MyTableWidget::addBeforeRow()
{
    int row = this->currentRow();

    this->insertRow(row);

    int colCount = this->columnCount();
    for(int i = 0; i < colCount; i ++){
        this->setItem(row, i, new QTableWidgetItem(""));
        this->item(row, i)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    this->setCurrentItem(this->item(row, 0));
}

void MyTableWidget::addAfterRow()
{
    int row = this->currentRow() + 1;

    this->insertRow(row);
    int colCount = this->columnCount();
    for(int i = 0; i < colCount; i ++){
        if(i == 1){
            QStringList items = {"定时模式", "定量模式"};
            QComboBox* comboBox = new QComboBox();
            comboBox->addItems(items);
            this->setCellWidget(row, i, comboBox);
        }
        else if(i == colCount - 1){
            QStringList items = {"10M", "100M", "1000M"};
            QComboBox* comboBox = new QComboBox();
            comboBox->addItems(items);
            this->setCellWidget(row, i, comboBox);
        }
        else{
            this->setItem(row, i, new QTableWidgetItem(""));
            this->item(row, i)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    this->setCurrentItem(this->item(row, 0));
}
