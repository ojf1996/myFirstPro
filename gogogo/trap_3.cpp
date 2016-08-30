#include "trap_3.h"
#include"hero.h"

Trap_3::Trap_3(qreal x,qreal y):Trap(x,y),dir(Up),_trigger(false)
{
    setPicName(":/source/image/rock.png");
}

void Trap_3::trigger()
{
    _trigger = true;
}

void Trap_3::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if(collidingItem->data(G_O_Type) == Hero_Type){
            dir = dynamic_cast<Hero *>(collidingItem)->getMoveDirection();
            trigger();
            return;
        }
    }
}

QPainterPath Trap_3::shape()const
{
    QPainterPath path;
    path.addRect(QRectF(-Size * 2,-Size * 2,Size*4,Size*4));
    return path;
}

void Trap_3::advance(int step)
{
    if(!step)
        return;
    if(_trigger)
    {
        switch (dir) {
        case Up:
            emit hit(this->x()-Size*2,this->y()+Size*3/2,Right,2);
            emit hit(this->x()-Size*2,this->y()+Size,Right,1);
            emit hit(this->x()-Size*2,this->y(),Right,1);
            emit hit(this->x()-Size*2,this->y()-Size/2,Right,3);
            emit hit(this->x()-Size*2,this->y()-Size,Right,1);
            emit hit(this->x(),this->y()-Size,Down,1);
            _trigger = false;
            emit removeTrap(this);
            break;
        case Left:
            emit hit(this->x()-Size*2,this->y()-Size*2,Down,2);
            emit hit(this->x()-Size,this->y()-Size*2,Down,1);
            emit hit(this->x(),this->y()-Size*2,Down,1);
            emit hit(this->x()+Size,this->y()-Size*2,Down,3);
            emit hit(this->x()+Size*3/2,this->y()-Size*2,Down,1);
            _trigger = false;
            emit removeTrap(this);
            break;
        case Right:
            emit hit(this->x()+Size*2,this->y()+Size*2,Up,2);
            emit hit(this->x()+Size,this->y()+Size*2,Up,1);
            emit hit(this->x(),this->y()+Size*2,Up,1);
            emit hit(this->x()-Size/2,this->y()+Size*2,Up,3);
            emit hit(this->x()-Size,this->y()+Size*2,Up,1);
            _trigger = false;
            emit removeTrap(this);
            break;
        case Down:
            emit hit(this->x()+Size*2,this->y()-Size,Left,2);
            emit hit(this->x()+Size*2,this->y()-Size*3/2,Left,1);
            emit hit(this->x()+Size*2,this->y(),Left,1);
            emit hit(this->x()+Size*2,this->y()+Size/2,Left,3);
            emit hit(this->x()+Size*2,this->y()+Size,Left,1);
            _trigger = false;
            emit removeTrap(this);
            break;
        default:
            break;
        }
    }
}
