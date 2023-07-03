#ifndef MIRRORPORTTABLEWIDGET_H
#define MIRRORPORTTABLEWIDGET_H

#include <QTableWidget>
#include <QObject>

#include <QComboBox>
#include "DataTypeDef.h"

class MirrorPortTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MirrorPortTableWidget(QWidget* parent = nullptr);
    ~MirrorPortTableWidget();

    /**
     * @brief initConnect   初始化信号槽连接
     */
    void initConnect();

    /**
     * @brief appendRow     添加行信息
     * @param data
     */
    void appendRow(const PORT_DATA& data);

    /**
     * @brief getRowData    获取行数据信息
     * @param row           行索引
     * @return
     */
    PORT_DATA getRowData(int row);

signals:
    void currentTextChanged(int row);

private slots:
    void slotCurrentIndexChanged(int row);

private:
    QComboBox* getComboBox(const QStringList& items);

private:
    QStringList mirrorTypeList, mirrorEnableList, monitorDirList;
};

#endif // MIRRORPORTTABLEWIDGET_H
