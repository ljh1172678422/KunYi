#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QObject>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MyTableWidget(QWidget* parent = nullptr);
    ~MyTableWidget();

    QList<QStringList> getItemList();

private:
    void contextMenuEvent(QContextMenuEvent* event);

private slots:
    void deleteSelectedRows();

    void addBeforeRow();

    void addAfterRow();
};

#endif // MYTABLEWIDGET_H
