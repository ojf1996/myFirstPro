#ifndef HURT_H
#define HURT_H

#include"constants.h"
#include<QString>
#include<QGraphicsItem>

class Hurt :public QObject ,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Hurt(qreal,qreal,_Direction,int = 0);
    ~Hurt();
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void setPicName(QString a){picName = a;}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    void removeHurt(QGraphicsItem *);
protected:
    virtual void advance(int);
    _Direction moveDirection;
    virtual void handleCollisions();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveLeftUp();
    void moveLeftDown();
    void moveRightUp();
    void moveRightDown();
    QString picName;
    int _type;
};

#endif // HURT_H
