#include <QPainter>
#include"gamecontroller.h"
#include "enemy.h"

Enemy::Enemy(qreal x,qreal y)
    : hp(100),
      mad(false),
      _attack(false),shoot(false)
{
    setPos(x,y);
    setData(G_O_Type,Enemy_Type);
}

QRectF Enemy::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath Enemy::shape()const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}

bool Enemy::isMad()
{
    return hp<=30;
}

void Enemy::back()
{
    switch (moveDirection) {
    case Left:
        moveRight();moveRight();
        break;
    case Right:
        moveLeft();moveLeft();
        break;
    case Up:
        moveDown(); moveDown();
        break;
    case Down:
        moveUp(); moveUp();
        break;
    default:
        break;
    }
}

void Enemy::moveLeft()
{
    setPos(this->x()-Size/4,this->y());
}

void Enemy::moveRight()
{
    setPos(this->x()+Size/4,this->y());
}
\
void Enemy::moveUp()
{
    setPos(this->x(),this->y()-Size/4);
}

void Enemy::moveDown()
{
    setPos(this->x(),this->y()+Size/4);
}

_Direction Enemy::getMoveDirection()const
{
    return moveDirection;
}

void Enemy::setMoveDirection(_Direction a)
{
    moveDirection = a;
}

void Enemy::setPicName(QString a)
{
    picName = a;
}

QString Enemy::getPicName()const
{
    return picName;
}

int Enemy::getHp()const
{
    return hp;
}

void Enemy::changePicture()
{}

void Enemy::advance(int step)
{}

void Enemy::attack()
{}

void Enemy::handleCollisions()
{}

