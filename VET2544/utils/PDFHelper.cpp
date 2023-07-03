#include "PDFHelper.h"

#include <QFile>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>

#include "ServiceException.h"

PDFHelper *PDFHelper::_instance = 0;
PDFHelper::PDFHelper():
    pPainter(nullptr),
    pWriter(nullptr),
    contentHeight(0),
    contentWidth(0),
    curPage(1)
{}

void PDFHelper::init(const QString &filePath)
{
    this->filePath = filePath;
}

void PDFHelper::initPainter()
{
    contentHeight = 0;
    contentWidth = 0;
    curPage = 1;

    pdfFile = new QFile(filePath);

    if(!pdfFile->open(QIODevice::WriteOnly)){
        QString msg = QString("文件[%1]打开失败：%2").arg(filePath, pdfFile->errorString());
        throw ServiceException(msg);
    }

    pWriter = new QPdfWriter(pdfFile);

    //初始化纸张
    pWriter->setPageSize(QPageSize::A4);
    //设置dpi 每个平方英寸像素为300
    pWriter->setResolution(300);
    pWriter->setPageMargins(QMarginsF(30, 30, 30, 30));

    pPainter = new QPainter(pWriter);

    //初始化字体样式
    font[0] = QFont("宋体", 26, 60);
    font[1] = QFont("宋体", 26, 61);
    font[2] = QFont("宋体", 26, QFont::Normal);
    font[3] = QFont("宋体", 26, QFont::Normal);
    font[4] = QFont("宋体", 26, QFont::Normal);

    font[0].setPixelSize(86);
    font[1].setPixelSize(61);
    font[2].setPixelSize(54);
    font[3].setPixelSize(42);
    font[4].setPixelSize(30);
}

void PDFHelper::insertTitle(const QString &title)
{
    updateContentHeight(contentHeight + 220, pPainter->viewport().height(), curPage);

    //插入文件标题
    pPainter->setFont(font[0]);
    pPainter->drawText(QRect(0, contentHeight, pPainter->viewport().width(), 100), Qt::AlignCenter | Qt::TextWordWrap, title);
    contentHeight += 120;

    pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
    pPainter->drawLine(0, contentHeight, pPainter->viewport().width(), contentHeight);
    pPainter->drawLine(0, contentHeight+18, pPainter->viewport().width(), contentHeight+18);
    contentHeight += 100;

    int nPDFWidth = pPainter->viewport().width();
    int nPDFHeight = pPainter->viewport().height();
    int bottom_gap = font[4].pixelSize();

    //绘制页脚
    pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
    pPainter->drawLine(0, nPDFHeight - bottom_gap - 10, nPDFWidth, nPDFHeight - bottom_gap - 10);

    pPainter->setFont(font[4]);
    pPainter->drawText(QRect(0, nPDFHeight - bottom_gap, nPDFWidth, bottom_gap), Qt::AlignLeft,
        QString("文件名：          %1").arg(filePath.split("/").back()));

    pPainter->drawText(QRect(nPDFWidth - 200, nPDFHeight - bottom_gap, bottom_gap*4, bottom_gap), Qt::AlignRight,
        QString("页码：%1").arg(QString::number(curPage)));
}

void PDFHelper::insertContent(const QString &content)
{
    updateContentHeight(contentHeight + 200, pPainter->viewport().height(), curPage);

    //插入文本内容
    pPainter->setFont(font[1]);
    pPainter->drawText(QRect(0, contentHeight, pPainter->viewport().width(), 80), Qt::AlignLeft | Qt::TextWordWrap, content);
    contentHeight += 100;
}

void PDFHelper::insertQChartView(QChartView *view, const QString& title)
{
    updateContentHeight(contentHeight + 100, pPainter->viewport().height(), curPage);

    if(!title.isEmpty()){
        pPainter->setFont(font[1]);
        pPainter->drawText(QRect(0, contentHeight, pPainter->viewport().width(), 80),
                           Qt::AlignCenter | Qt::TextWordWrap,
                           title);
        contentHeight += 100;
    }

    //设置图片水平边距为150
    int imageBorder = 150;

    QPixmap pixmap = view->grab();
    pixmap.save("test.png");

    float x = (float)(pPainter->viewport().width() - imageBorder*2) / (float)pixmap.width();
    //根据大小比例，来放大缩小图片
    pixmap = pixmap.scaled(pPainter->viewport().width() - imageBorder*2,
                           x * pixmap.height(),
                           Qt::IgnoreAspectRatio);

    updateContentHeight(contentHeight + pixmap.height(), pPainter->viewport().height(), curPage);

    pPainter->drawPixmap(imageBorder, contentHeight, pixmap);

    contentHeight += pixmap.height() + 100;
}

void PDFHelper::insertTable(int horzBorder, int unitHeight, int lineweight, QTableWidget* table_get, QString tableTitle)
{
    pPainter->setFont(font[2]);
    pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), lineweight));

    const int Width = pPainter->viewport().width() - (horzBorder << 1);
    const int row = table_get->rowCount();
    const int column = table_get->columnCount();
    const int unitWidth = Width / column;
    int x = horzBorder;

    updateContentHeight(contentHeight + unitHeight, pPainter->viewport().height(), curPage);
    if(!tableTitle.isEmpty()){
        font[2].setBold(true);
        pPainter->setFont(font[2]);
        pPainter->drawText(QRect(x, contentHeight, Width, unitHeight), Qt::AlignCenter, QString::fromLocal8Bit("%1").arg(tableTitle));
        pPainter->drawRect(QRect(x, contentHeight, Width, unitHeight));
        contentHeight += unitHeight;
    }

    updateContentHeight(contentHeight + unitHeight, pPainter->viewport().height(), curPage);
    for (int j = 0; j < column; j++)
    {
        pPainter->drawText(QRect(x, contentHeight, unitWidth, unitHeight), Qt::AlignCenter, table_get->horizontalHeaderItem(j)->text());
        pPainter->drawRect(QRect(x, contentHeight, unitWidth, unitHeight));
        x += unitWidth;
    }
    contentHeight += unitHeight;

    for (int i = 0; i < row; i++)
    {
        x = horzBorder;
        updateContentHeight(contentHeight + unitHeight, pPainter->viewport().height(), curPage);

        font[2].setBold(false);
        pPainter->setFont(font[2]);
        for (int j = 0; j < column; j++)
        {
            pPainter->drawText(QRect(x, contentHeight, unitWidth, unitHeight), Qt::AlignCenter, table_get->item(i, j)->text());
            pPainter->drawRect(QRect(x, contentHeight, unitWidth, unitHeight));
            x += unitWidth;
        }
        contentHeight += unitHeight;
    }

    contentHeight += 100;
}

void PDFHelper::insertTable(int horzBorder, int row, int column, int unitHeight, QList<QStringList> &list)
{
    pPainter->setFont(font[2]);
    pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), 1));

    int Width = pPainter->viewport().width() - (horzBorder << 1);
    int unitWidth = Width / column;

    for (int i = 0; i < row; i++)
    {
        updateContentHeight(contentHeight + unitHeight, pPainter->viewport().height(), curPage);
        int x = horzBorder;
        for (int j = 0; j < column; j++)
        {
            pPainter->drawText(QRect(x, contentHeight, unitWidth, unitHeight), Qt::AlignCenter, list[i][j]);
            pPainter->drawRect(QRect(x, contentHeight, unitWidth, unitHeight));
            x += unitWidth;
        }

        contentHeight += unitHeight;
    }
}

void PDFHelper::updateContentHeight(int y_target, int set_limit, int& page_now)
{
    if (y_target > set_limit)
    {
        pWriter->newPage();
        page_now++;

        int nPDFWidth = pPainter->viewport().width();
        int nPDFHeight = pPainter->viewport().height();
        int bottom_gap = font[4].pixelSize();

        //绘制页脚
        pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
        pPainter->drawLine(0, nPDFHeight - bottom_gap - 10, nPDFWidth, nPDFHeight - bottom_gap - 10);

        pPainter->setFont(font[4]);
        pPainter->drawText(QRect(0, nPDFHeight - bottom_gap, nPDFWidth, bottom_gap), Qt::AlignLeft,
            QString("文件名：          %1").arg(filePath.split("/").back()));

        pPainter->drawText(QRect(nPDFWidth - 200, nPDFHeight - bottom_gap, bottom_gap*4, bottom_gap), Qt::AlignRight,
            QString("页码：%1").arg(QString::number(page_now)));

        contentHeight = 0;

        //绘制页眉
        //pPainter->setPen(QPen(QBrush(QColor(0, 0, 0)), 2));
        //pPainter->drawLine(0, contentHeight, nPDFWidth, contentHeight);

        contentHeight += 10;
    }
}

void PDFHelper::save()
{
    delete pPainter;
    delete pWriter;
    pdfFile->close();

    pPainter = NULL;
    pWriter = NULL;
}

