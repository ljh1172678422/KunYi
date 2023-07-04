#include "MyTableWidget.h"

MyTableWidget::MyTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    statusList << "Enable" << "Disable";
    typeList << "Access" << "Trunk" << "Hybrid";
    speedList  << "1000M" << "100M" << "10M"
/*              << "Auto" << "Auto 10M" << "Auto 100M" << "Auto 1000M"
              << "Auto 10M 100M" << "Auto 10M 1000M" << "Auto 100M 1000M"*/;
    duplexList /*<< "Auto"*/ << "Full" << "Half";
}

MyTableWidget::~MyTableWidget()
{}

void MyTableWidget::initConnect()
{
    auto rowCount = this->rowCount();
    for(int row = 0; row < rowCount; row ++) {
        connect((QComboBox*)(this->cellWidget(row, 2)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
        connect((QComboBox*)(this->cellWidget(row, 3)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
        connect((QComboBox*)(this->cellWidget(row, 4)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
        connect((QComboBox*)(this->cellWidget(row, 6)), SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
    }
}

void MyTableWidget::appendRow(const PORT_DATA &data)
{
    auto row = this->rowCount();
    this->insertRow(row);

    this->setItem(row, 0, new QTableWidgetItem(data.portName));
    this->item(row, 0)->setTextAlignment(Qt::AlignCenter);

    this->setItem(row, 1, new QTableWidgetItem(QString::number(data.chipID)));
    this->item(row, 1)->setTextAlignment(Qt::AlignCenter);

    auto statusCBox = getComboBox(statusList);
    statusCBox->setEnabled(false);
    statusCBox->setCurrentText(data.portStatus);
    this->setCellWidget(row, 2, statusCBox);

    auto typeCBox = getComboBox(typeList);
    //typeCBox->setEnabled(false);
    typeCBox->setCurrentText(data.portType);
    this->setCellWidget(row, 3, typeCBox);

    auto speedCBox = getComboBox(speedList);
    speedCBox->setCurrentText(data.portSpeed);
    this->setCellWidget(row, 4, speedCBox);

    this->setItem(row, 5, new QTableWidgetItem(QString::number(data.portVlanGroup)));
    this->item(row, 5)->setTextAlignment(Qt::AlignCenter);

    auto duplexCBox = getComboBox(duplexList);
    duplexCBox->setEnabled(false);
    duplexCBox->setCurrentText(data.portDuplex);
    this->setCellWidget(row, 6, duplexCBox);

    this->setItem(row, 7, new QTableWidgetItem(QString::number(data.PVID)));
    this->item(row, 7)->setTextAlignment(Qt::AlignCenter);
}

PORT_DATA MyTableWidget::getRowData(int row)
{
    PORT_DATA data;
    data.portName = this->item(row, 0)->text();
    data.portStatus = ((QComboBox*)this->cellWidget(row, 1))->currentText();
    data.portType = ((QComboBox*)this->cellWidget(row, 2))->currentText();
    data.portSpeed = ((QComboBox*)this->cellWidget(row, 3))->currentText();
    data.portVlanGroup = this->item(row, 4)->text().toInt();
    data.portDuplex = ((QComboBox*)this->cellWidget(row, 5))->currentText();
    data.PVID = this->item(row, 6)->text().toInt();

    return data;
}

void MyTableWidget::slotCurrentIndexChanged(int row)
{
    row = this->currentRow();

    emit currentTextChanged(row);
}

QComboBox *MyTableWidget::getComboBox(const QStringList &items)
{
    QComboBox* comboBox = new QComboBox();
    comboBox->addItems(items);

    return comboBox;
}
