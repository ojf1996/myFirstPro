#ifndef STUFFITEM_H
#define STUFFITEM_H

#include"constants.h"
#include<QGraphicsItem>
#include<QPainter>

class StuffItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:

    StuffItem(qreal x, qreal y1,int = 1);

public slots:

    void trigger(){
        emit getStuff(whatIsThis);
        emit removeStuff(this);
    }
protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect()const;

    QPainterPath shape()const;

signals:
    void getStuff(int);
    void removeStuff(QGraphicsItem * );

private:
    int whatIsThis;
};

#endif // STUFFITEM_H
