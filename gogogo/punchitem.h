#ifndef PUNCHITEM_H
#define PUNCHITEM_H

#include"constants.h"
#include<QGraphicsItem>
class GameController;


class PunchItem : public QObject,public QGraphicsItem
{

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    PunchItem(qreal x,qreal y,_Direction,int = 20);
    ~PunchItem();
    QRectF boundingRect()const;
    QPainterPath shape()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void setDir(Direction);
signals:
    void removePunch(QGraphicsItem *);
protected:
    void advance(int);
private:
    _Direction moveDirection;
    void handleCollisions();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveLeftUp();
    void moveLeftDown();
    void moveRightUp();
    void moveRightDown();

    int atk;
};

#endif // PUNCHITEM_H
