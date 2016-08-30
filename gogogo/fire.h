#ifndef FIRE_H
#define FIRE_H

#include <QObject>
#include<QString>
#include<QGraphicsItem>
#include"constants.h"

class Fire : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Fire(qreal x, qreal y,_Direction,int = 40);
    ~Fire();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void setPicName(QString a){
        if(!(a.isEmpty())){
            picName = a;
        }
    }

protected:
    virtual void advance(int);
    virtual void changePicture();
    void handleCollisions();

signals:
    void removeFire(QGraphicsItem *);
    void boom(qreal,qreal,_Direction,int);

private:
    QString picName;
    _Direction moveDirection;//方向
    int atk;//攻击力
    int num;//黏上boss
    int count;//换图
    int speed;


    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveLeftUp();
    void moveLeftDown();
    void moveRightUp();
    void moveRightDown();
};

#endif // FIRE_H
