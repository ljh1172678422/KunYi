#ifndef MULTICOMBOBOX_H
#define MULTICOMBOBOX_H

#include "MenuItem.h"
#include <QComboBox>
#include <QWidget>
#include <QListView>
#include <QStandardItemModel>

/**
 * @brief The MultiComboBox class   自定义ComboBox工具类
 */
class MultiComboBox : public QComboBox
{
    Q_OBJECT
public:
    MultiComboBox(QWidget* parent = nullptr);
    ~MultiComboBox();

    /**
     * @brief addItems  批量添加Item
     * @param menus     iTem列表
     */
    void addItems(QList<MenuItem*> menus);

    /**
     * @brief removeItem    移除Item
     * @param row           行数
     */
    void removeItem(int row);

    /**
     * @brief clear 清空
     */
    void clear();

    /**
     * @brief getItemsList  获取选中的字符串
     * @return              返回选中的字符串
     */
    QStringList getItemsList();

    /**
     * @brief getItemIds    获取选中项的id集合
     * @return              返回选中项的id集合
     */
    QList<int> getItemIds();

    /**
     * @brief setAllItemCheckedState    设置全部item的选中状态
     * @param checkState                状态
     */
    void setAllItemCheckedState(Qt::CheckState checkState);

signals:
    /**
     * @brief signalActivated   选中item时，发送信号
     * @param row               行数
     */
    void signalActivated(int row);

protected:
    /**
     * @brief hidePopup 目标：通过判断鼠标是否还在ComboBox 下拉框区域来判断，是否隐藏下拉框
     */
    void hidePopup() Q_DECL_OVERRIDE;

    /**
     * @brief eventFilter
     * @param watched
     * @param event
     * @return
     */
    bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

private:
    QList<MenuItem> menus;
    QLineEdit* pLineEdit;
    QListView* pListView;
    QStandardItemModel *itemModel;

private:
    //更新选中字符串
    void updateText();

    void wheelEvent(QWheelEvent* event);

public slots:
    /**
     * @brief slotActivated 响应单击 item
     * @param row           行数
     */
    void slotActivated(int row);
};

#endif // MULTICOMBOBOX_H
