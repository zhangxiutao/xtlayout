#include "lrectangle.h"
#include "navigationtool.h"
#include "xtliterals.h"
#include <QPainter>

LRectangle::LRectangle(NavigationTool* pNavTool):x1(0), y1(0), x2(0), y2(0), mRect(nullptr), LShape(pNavTool)
{

}

LRectangle::LRectangle(xtdb::XtRectangle* pRect, NavigationTool* pNavTool):mRect(pRect), LShape(pNavTool)
{
}

LRectangle::~LRectangle()
{
    if (mRect)
    {
        mRect->destroy();
    }
}

void LRectangle::storeToDB(xtdb::XtBlock* pBlock)
{
    mRect = xtdb::XtRectangle::create(pBlock);
    mRect->setX1(x1);
    mRect->setY1(y1);
    mRect->setX2(x2);
    mRect->setY2(y2);
    mRect->setExtendedObj(XTLAYOUT, this);
}

QRect LRectangle::getZone()
{
    return QRect(QPoint(x1, y1),
                 QPoint(x2, y2));
}

QPoint LRectangle::getFirstPoint()
{
    return QPoint(x1, y1);
}

QPoint LRectangle::getSecondPoint()
{
    return QPoint(x2, y2);
}

void LRectangle::setFirstPoint(const QPoint& pPoint)
{
    x1 = pPoint.x();
    y1 = pPoint.y();
}

void LRectangle::setSecondPoint(const QPoint& pPoint)
{
    x2 = pPoint.x();
    y2 = pPoint.y();
}

void LRectangle::draw(QPainter* pPainter)
{
    if (isSelected()) {
        pPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
        pPainter->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
    }
    pPainter->drawRect(mNavTool->worldCS2ViewportCS(getZone()));
}
