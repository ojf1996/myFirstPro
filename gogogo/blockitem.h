#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include"constants.h"
#include <QGraphicsItem>
#include <QRectF>
#include<QString>

 class BlockItem : public QGraphicsItem
{
public:
    BlockItem(qreal,qreal,Dimao = Tree);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QString picName;
};

#endif // BLOCKITEM_H
