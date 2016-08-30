#include "enemy_type_2.h"

Enemy_type_2::Enemy_type_2(qreal x, qreal y):Enemy(x,y)
{
    setPicName(":/source/image/enemy_type_1_left_2.png");
}


QPainterPath Enemy_type_2::shape()const
{
    QPainterPath path;
    path.addRect(QRectF(-Size *2,-Size * 2,Size * 4 ,Size *4));
    return path;
}

void Enemy_type_2::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if(collidingItem->data(G_O_Type) == Hero_Type){
            if(!shoot){
                attack();
                shoot = true;
            }
            return;
        }
    }
}

void Enemy_type_2::advance(int step)
{
    if(!step)
        return;
    if(getHp()<=0)
    {
        emit enemyKillAt(this->x(),this->y(),Enemy_Type);
        emit removeEnemy(this);
        return;
    }
    handleCollisions();
}

void Enemy_type_2::attack()
{
    emit hit(this->x()-Size/2,this->y(),Left,2);
    emit hit(this->x()-Size/2,this->y()-Size/2,LeftUp,2);
    emit hit(this->x()-Size/2,this->y()+Size/2,LeftDown,2);
    emit hit(this->x(),this->y()-Size/2,Up,2);
    emit hit(this->x()+Size/2,this->y()-Size/2,RightUp,2);
    emit hit(this->x()+Size/2,this->y(),Right,2);
    emit hit(this->x()+Size/2,this->y()+Size/2,RightDown,2);
    emit hit(this->x(),this->y()+Size/2,Down,2);
}
