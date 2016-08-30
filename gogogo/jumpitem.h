#ifndef JUMPITEM_H
#define JUMPITEM_H

#include"constants.h"
#include<QGraphicsItem>

class JumpItem : public QObject,public QGraphicsItem
{
     Q_OBJECT
     Q_INTERFACES(QGraphicsItem)

public:
    JumpItem(qreal,qreal,int);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void trigger();
signals:
    void getNextMap(int);
private:
    int next;
};

#endif // JUMPITEM_H
