#ifndef OMG_H
#define OMG_H

#include"constants.h"
#include<QString>
#include<QTimer>
#include<QPainter>
#include<QGraphicsItem>

class OMG : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
private:
    QTimer time;
    int hitTime;
    int count;

public:
    OMG(qreal,qreal,_Direction,int =0);
    void changePic();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void setPicName(QString a){picName = a;}
public slots:
    void trigger();
signals:
    void boom(qreal,qreal,_Direction,int = 0);
    void removeOMG(QGraphicsItem *);

protected:
    void advance(int);
    void handleCollisions();

    void moveLeft(){setPos(this->x()-Size/2,this->y());}
    void moveRight(){setPos(this->x()+Size/2,this->y());}
    void moveUp(){setPos(this->x(),this->y()-Size/2);}
    void moveDown(){setPos(this->x(),this->y()+Size/2);}
    void moveLeftUp(){setPos(this->x()-Size/2,this->y()-Size/2);}
    void moveLeftDown(){setPos(this->x()-Size/2,this->y()+Size/2);}
    void moveRightUp(){setPos(this->x()+Size/2,this->y()-Size/2);}
    void moveRightDown(){setPos(this->x()+Size/2,this->y()+Size/2);}

    _Direction moveDirection;
    QString picName;
    int type;
};

#endif // OMG_H
