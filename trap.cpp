#include<QPainter>
#include "trap.h"

Trap::Trap(qreal x,qreal y)
    :picName(":/source/image/unknown.png"),
      hp(100)
{
    setPos(x,y);
    setData(G_O_Type,Trap_Type);
}

QRectF Trap::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath Trap::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Trap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}

void Trap::trigger()
{}

void Trap::advance(int phase)
{}

Trap::~Trap()
{
    timer.stop();
}
