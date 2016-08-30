#include "trap_1.h"

Trap_1::Trap_1(qreal x,qreal y,_Direction dir,_Direction _ty,bool _t)
    :Trap(x,y),
     towards(dir),
     moveDir(_ty),
     moveAble(_t),
     speed(0),
     count(0),
     _trigger(false)
{
    switch (towards){
    case Left:
    case Down:
        Trap::setPicName(":/source/image/trap_1_left.png");
        break;
    case Right:
    case Up:
        Trap::setPicName(":/source/image/trap_1_right.png");
        break;
    default:
        setPicName(":/source/image/trap_1_right.png");
        break;
    }
    timer.start(1000);
    connect(&timer,SIGNAL(timeout()),this,SLOT(trigger()));
}

Trap_1::~Trap_1()
{
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(trigger()));
}

void Trap_1::advance(int step)
{

    if(!step)
        return;

    if(speed++%3!=0)
        return;

    if(getHp() <= 0){
        this->timer.stop();
        emit trapKilledAt(this->x(),this->y(),Trap_Type);
        emit removeTrap(this);
        return;
    }

    count++;
    if(count > 27)
        count =0;
    if(_trigger){
        switch(towards){
        case Up:
            emit hit(this->x()+Size/2,this->y()-Size/2,towards,1);
            break;
        case Left:
            emit hit(this->x()-Size/2,this->y(),towards,1);
            break;
        case Down:
            emit hit(this->x()+Size/2,this->y()+Size/2,towards,1);
            break;
        case Right:
            emit hit(this->x()+Size/2,this->y(),towards,1);
            break;
        default:
            emit hit(this->x(),this->y(),towards,1);
            break;
        }
        _trigger = false;
    }
    switch (moveDir) {
        case Left:
        case Right:
            switch (count) {
            case 0:
            case 1: case 2:case 3:case 4:
            case 5:
            case 6:case 7:case 8:
                if(moveAble)
                    this->setPos(this->x(),this->y()+Size/3);
                break;
            case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:
                break;
        case 18:
        case 19:case 20:case 21:case 22:
        case 23:
        case 24:case 25:case 26:
                if(moveAble)
            this->setPos(this->x(),this->y()-Size/3);
        default:
                 break;
            }
               break;
         case Up:
         case Down:
        switch (count) {
            case 0:trigger();
            case 1: case 2:case 3:case 4:
            case 5:
            case 6:case 7:case 8:
            if(moveAble)
                this->setPos(this->x(),this->y()+Size/3);
                break;
        case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:
            break;
        case 18:trigger();
        case 19:case 20:case 21:case 22:
        case 23:
        case 24:case 25:case 26:
            if(moveAble)
                this->setPos(this->x(),this->y()-Size/3);
            break;
        default:
                 break;
        }
           break;
        default:
            break;
    }
    return;
}

void Trap_1::trigger()
{
    _trigger = true;
}
