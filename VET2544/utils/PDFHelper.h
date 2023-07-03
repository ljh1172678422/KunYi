#ifndef PDFHELPER_H
#define PDFHELPER_H

#include <QObject>
#include <QFile>
#include <QMutex>
#include <QPdfWriter>
#include <QPainter>
#include <QChartView>
#include <QTableWidget>

class PDFHelper : public QObject
{
    Q_OBJECT
public:
    explicit PDFHelper();
    static PDFHelper* _instance;

public:
    static PDFHelper *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new PDFHelper;
            }
        }
        return _instance;
    }

public:
    /**
     * @brief init              初始化
     * @param filePath          PDF文件路径
     */
    void init(const QString& filePath);

    /**
     * @brief initPainter       初始化画笔
     */
    void initPainter();

    /**
     * @brief insertTitle       插入文件大标题
     * @param title             大标题
     */
    void insertTitle(const QString& title);

    /**
     * @brief insertContent     插入文本内容
     * @param content           文本内容
     */
    void insertContent(const QString& content);

    /**
     * @brief insertQChartView  插入图表
     * @param view              图表对象
     * @param title             图像标题
     */
    void insertQChartView(QChartView *view, const QString &title);

    /**
     * @brief insertTable   根据TableWidget插入表格
     * @param horzBorder    水平外边距,写0表示没有边距
     * @param unitHeight    单元高度
     * @param lineweight    表格线粗
     * @param table_get     要写入的表格
     * @param tableTitle    表格标题
     */
    void insertTable(int horzBorder,
                    int unitHeight,
                    int lineweight,
                    QTableWidget *table_get,
                    QString tableTitle);

    /**
     * @brief insertTable   自定义插入表格
     * @param horzBorder    水平外边距，写0表示没有边距
     * @param row           行数
     * @param column        列数
     * @param unitHeight    单元高度
     * @param list          要写入的表格内容
     */
    void insertTable(int horzBorder,
                     int row,
                     int column,
                     int unitHeight,
                     QList<QStringList>& list);

    void save();

    /**
     * @brief updateContentHeight  判断contentHeight是否超出界限
     * @param y_target          目标高度
     * @param set_limit         高度限制
     * @param page_now          当前页码
     */
    void updateContentHeight(int y_target,
                           int set_limit,
                           int &page_now);
private:
    QFile* pdfFile;
    QPainter* pPainter;
    QPdfWriter* pWriter;

    QString filePath;

    QFont font[5];

    int contentHeight;
    int contentWidth;

    int curPage;
};

#endif // PDFHELPER_H
