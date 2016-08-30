#include"stuffitem.h"

StuffItem::StuffItem(qreal x,qreal y,int a)
{
    if(a>0&&a<23)
        whatIsThis = a;
    else
        whatIsThis = 1;
    setPos(x,y);
    setData(G_O_Type,Stuff_Type);
}

void StuffItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(":/source/image/stuff.png");
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}

QRectF StuffItem::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath StuffItem::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
