#include "MirrorPortTableWidget.h"

MirrorPortTableWidget::MirrorPortTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    mirrorTypeList << "Mirror Port" << "Monitor Port" << "None";
    mirrorEnableList << "Disable" << "Enable";
    monitorDirList << "Inbound" << "Outbound" << "Both";
}

MirrorPortTableWidget::~MirrorPortTableWidget()
{}

void MirrorPortTableWidget::initConnect()
{
    auto rowCount = this->rowCount();
    for(int row = 0; row < rowCount; row ++) {
        connect((QComboBox*)(this->cellWidget(row, 1)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
        connect((QComboBox*)(this->cellWidget(row, 2)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
        connect((QComboBox*)(this->cellWidget(row, 3)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
    }
}

void MirrorPortTableWidget::appendRow(const PORT_DATA &data)
{
    auto row = this->rowCount();
    this->insertRow(row);

    this->setItem(row, 0, new QTableWidgetItem(data.portName));
    this->item(row, 0)->setTextAlignment(Qt::AlignCenter);

    auto typeCBox = getComboBox(mirrorTypeList);
//    typeCBox->setEnabled(false);
    typeCBox->setCurrentText(data.portStatus);
    this->setCellWidget(row, 1, typeCBox);

    auto enableCBox = getComboBox(mirrorEnableList);
//    enableCBox->setEnabled(false);
    enableCBox->setCurrentText(data.portStatus);
    this->setCellWidget(row, 2, enableCBox);

    auto dirCBox = getComboBox(monitorDirList);
    //typeCBox->setEnabled(false);
    dirCBox->setCurrentText(data.portType);
    this->setCellWidget(row, 3, dirCBox);
}

PORT_DATA MirrorPortTableWidget::getRowData(int row)
{
    PORT_DATA data;
    data.portName = this->item(row, 0)->text();
    data.mirrorPortType = ((QComboBox*)this->cellWidget(row, 1))->currentIndex();
    data.mirrorPortEnable = ((QComboBox*)this->cellWidget(row, 2))->currentIndex();
    data.mirrorPortMonitorDir = ((QComboBox*)this->cellWidget(row, 3))->currentIndex();

    return data;
}

void MirrorPortTableWidget::slotCurrentIndexChanged(int row)
{
    row = this->currentRow();

    emit currentTextChanged(row);
}

QComboBox *MirrorPortTableWidget::getComboBox(const QStringList &items)
{
    QComboBox* comboBox = new QComboBox();
    comboBox->addItems(items);

    return comboBox;
}
