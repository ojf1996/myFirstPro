#include "jumpitem.h"
#include<QDebug>
#include<QPainter>

JumpItem::JumpItem(qreal x, qreal y,int _next)
    :next(_next)
{
    setPos(x,y);
    setData(G_O_Type,Jumping_Type);
}

QRectF JumpItem::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath JumpItem::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void JumpItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(":/source/image/unknown.png");
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}


void JumpItem::trigger()
{
    qDebug()<<"trigger";
    emit getNextMap(next);
}
