#include "trap_2.h"

Trap_2::Trap_2(qreal x,qreal y):Trap(x,y),dir(0),_trigger(false)
{
    setPicName(":/source/image/trap_1_left.png");
    connect(&timer,SIGNAL(timeout()),this,SLOT(trigger()));
    timer.start(800);
}

void Trap_2::trigger()
{
    _trigger = true;
}

void Trap_2::advance(int step)
{
    if(!step)
        return;
    if(getHp()<=0){
        _trigger = false;
        emit trapKilledAt(this->x(),this->y(),Trap_Type);
        emit removeTrap(this);
        return;
    }
    if(_trigger){
        dir++;
        if(dir >= 9)
             dir = 0;
        switch (dir) {
            case 1:
                emit hit(this->x()+Size/2,this->y(),Up,1);
                break;
            case 2:
                emit hit(this->x(),this->y(),LeftUp,1);
                break;
            case 3:
                emit hit(this->x(),this->y(),Left,1);
                break;
            case 4:
                emit hit(this->x(),this->y(),LeftDown,1);
                break;
            case 5:
                emit hit(this->x()+Size/2,this->y(),Down,1);
                break;
            case 6:
                emit hit(this->x(),this->y(),RightDown,1);
                break;
            case 7:
                emit hit(this->x(),this->y(),Right,1);
                break;
            case 8:
                emit hit(this->x(),this->y(),RightUp,1);
                break;
            default:
                break;
        }
        _trigger = false;
    }
}

