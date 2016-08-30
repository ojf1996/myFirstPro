#ifndef ENEMY_H
#define ENEMY_H

#include"constants.h"
#include <QGraphicsItem>
#include <QRectF>
#include<QString>

class Enemy :public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Enemy(qreal,qreal);//构造函数
    //碰撞检测以及绘图的基准位置和边界
    virtual QRectF boundingRect()const;
    virtual QPainterPath shape()const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //敌人的动作
    void hpLose(int a){
        this->hp -= a;
    }

    int getHp()const;
    void setHp(int a){if(a >=0) hp = a;}

    bool isMad();//怒气状态
    void setMad(){mad = true;}

    void back();//被击退
    _Direction getMoveDirection()const;//方向
    void setMoveDirection(_Direction);

    virtual void attack();//进攻
protected:

    void setPicName(QString);//图片路径
    QString getPicName()const;
    virtual void changePicture();//绘图
    virtual void advance(int step);
    //移动函数
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    //碰撞检测
    virtual void handleCollisions();
    bool shoot;
signals:
    void enemyKillAt(qreal,qreal,MyType);
    void hit(qreal,qreal,_Direction,int);
private:
    _Direction moveDirection;
    QString picName;
    int hp;
    bool mad;
    bool _attack;
};

#endif // ENEMY_H
