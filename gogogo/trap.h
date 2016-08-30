#ifndef TRAP_H
#define TRAP_H

#include"constants.h"
#include<QString>
#include<QTimer>
#include<QGraphicsItem>

class Trap :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Trap(qreal,qreal);
    ~Trap();
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPicName(QString a){picName = a;}
    //********** get set函数 ***********************//
    int getHp()const{return hp;}
    void setHp(int a){if(a>0) hp =a;}
protected:
    virtual void advance(int phase);
    QTimer timer;
private:
    QString picName;
    int hp;
public slots:
    virtual void trigger();//触发陷阱
    void beAttacked(int a){if(a>=0) hp-=a;}//扣血
signals:
    void trapKilledAt(qreal,qreal,MyType);
    void removeTrap(QGraphicsItem *);
    void hit(qreal,qreal,_Direction,int);
};

#endif // TRAP_H
