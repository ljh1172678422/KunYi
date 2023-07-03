#ifndef MENUITEM_H
#define MENUITEM_H

#include <QObject>

/**
 * @brief The MenuItem class    菜单item工具类
 */
class MenuItem
{
public:
    MenuItem(int menuId, const QString& menuName, bool isChecked = false);
    MenuItem();

    //拷贝构造函数，在遍历类集合时，需要使用
    MenuItem(const MenuItem& menuItem);

    int getMenuId() const;
    void setMenuId(int newMenuId);

    QString getMenuName() const;
    void setMenuName(const QString &newMenuName);

    bool getIsChecked() const;
    void setIsChecked(bool newIsChecked);

private:
    int menuId;
    QString menuName;
    bool isChecked;
};

#endif // MENUITEM_H
