#include "startbtn.h"
#include "define.h"
#include <QPainter>
#include <QMouseEvent>

StartBtn::StartBtn(QGraphicsItem *parent)
{
}

QRectF StartBtn::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth/2, 0 - penWidth/2,
                  170 + penWidth/2, 85 + penWidth/2);
}

void StartBtn::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap pixmap;
    pixmap.load(":/Images/Buttons.png");
    painter->drawPixmap(30,0,170,120,pixmap,0,1,170,85);//目标 ，源//（x,y,）
    pixmap.load(":/Images/Buttons1.png");
    painter->drawPixmap(240,0,340,170,pixmap,0,1,340,120);
}


