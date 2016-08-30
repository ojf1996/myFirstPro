#include "boss.h"
#include"hero.h"
#include<QDebug>
#include<QPainter>
#include<QTimer>

Boss::Boss(qreal x,qreal y):_x(x),_y(y),rush(false),hp(6000),count(0),picName("")
{
    setPos(x,y);
    setData(G_O_Type,Boss_Type);
    //*************** 循环计时器 26秒 *****************
    time_relax_end.start(35000);
    //*************** 之后12秒召唤小弟，18秒死亡冲刺 21秒归位
    time_callingUnit.singleShot(21000,this,SLOT(callingUnit()));
    time_rush_begin.singleShot(28000,this,SLOT(theRush()));
    time_rush_end.singleShot(30000,this,SLOT(resetPos()));

    //1秒后一次眩晕攻击，3秒一次毒杀，6秒一次
    time_attack_1.singleShot(1000,this,SLOT(attack_stuck()));
    time_attack_2.singleShot(6000,this,SLOT(attack_poison()));
    time_attack_3.singleShot(11000,this,SLOT(attack_mess()));
    time_attack_4.singleShot(16000,this,SLOT(attack_destory()));

    connect(&time_relax_end,SIGNAL(timeout()),this,SLOT(stopFireEnd()));
}

void Boss::theRush()
{
    rush = true;
}

void Boss::resetPos()
{
    rush = false;
    setPos(_x,_y);
}

void Boss::callingUnit()
{
    emit callingMadDog(this->x() - Size * 6,this->y() + Size , Down);
    emit callingMadDog(this->x() - Size * 4,this->y() + Size , Down);
    emit callingMadDog(this->x() - Size * 2,this->y() + Size , Down);
    emit callingMadDog(this->x()           ,this->y() + Size , Down);
    emit callingMadDog(this->x() + Size * 2,this->y() + Size , Down);
    emit callingMadDog(this->x() + Size * 4,this->y() + Size , Down);
    emit callingMadDog(this->x() + Size * 6,this->y() + Size , Down);

    emit callingMadBird(this->x() + Size * 6,this->y() + Size * 4,Left);
    emit callingMadBird(this->x() - Size * 6,this->y() + Size * 6,Right);
}


void Boss::attack_stuck()
{
    emit hit(this->x() - Size * 5,this->y(), Down,3);
    emit hit(this->x(),this->y(), Down,3);
    emit hit(this->x() + Size * 5,this->y(), Down,3);
}

void Boss::attack_poison()
{
    emit hit(this->x() - Size * 2,this->y(), Down,2);
    emit hit(this->x(),this->y(), Down,2);
    emit hit(this->x() + Size * 2,this->y(), Down,2);
}

void Boss::attack_mess()
{
    emit hit(this->x() - Size * 2,this->y(), Down,4);
    emit hit(this->x(),this->y(), Down,4);
    emit hit(this->x() + Size * 2,this->y(), Down,4);
}

void Boss::attack_destory()
{
    emit hit(this->x() - Size * 2,this->y(), Down,1);
    emit hit(this->x(),this->y(), Down,2);
    emit hit(this->x() + Size * 2,this->y(), Down,2);
}

void Boss::stopFireEnd()
{
    time_callingUnit.singleShot(21000,this,SLOT(callingUnit()));
    time_rush_begin.singleShot(28000,this,SLOT(theRush()));
    time_rush_end.singleShot(30000,this,SLOT(resetPos()));

    //1秒后一次眩晕攻击，3秒一次毒杀，6秒一次
    time_attack_1.singleShot(1000,this,SLOT(attack_stuck()));
    time_attack_2.singleShot(6000,this,SLOT(attack_poison()));
    time_attack_3.singleShot(11000,this,SLOT(attack_mess()));
    time_attack_4.singleShot(16000,this,SLOT(attack_destory()));

    connect(&time_relax_end,SIGNAL(timeout()),this,SLOT(stopFireEnd()));
}

void Boss::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if(collidingItem->data(G_O_Type) == Hero_Type){
            dynamic_cast<Hero * >(collidingItem)->hpLose();
            return;
        }
    }
}

void Boss::advance(int step)
{
    if(!step)
        return;
    if(hp <= 0){
        time_rush_begin.stop();
        time_rush_end.stop();
        time_attack_1.stop();
        time_attack_2.stop();
        time_attack_3.stop();
        time_attack_4.stop();
        time_callingUnit.stop();
        time_relax_end.stop();

        emit theEnd();
        emit removeBoss(this);
        return;
    }

    if(rush)
        setPos(this->x(),this->y()+Size/3);

    changPicName();
    handleCollisions();
}

void Boss::changPicName()
{
    if(count >= 7)
        count = 0;
    count++;
    switch(count){
        case 1:
            picName = ":/source/image/boss_up_1.png";
        break;
        case 2:
            picName = ":/source/image/boss_up_2.png";
        break;
        case 3:
            picName = ":/source/image/boss_up_3.png";
        break;
        case 4:
            picName = ":/source/image/boss_up_4.png";
        break;
        case 5:
            picName = ":/source/image/boss_up_51.png";
        break;
        case 6:
            picName = ":/source/image/boss_up_6.png";
        break;
        case 7:
            picName = ":/source/image/boss_up_7.png";
        break;
        default:
             picName = ":/source/image/boss_up_7.png";
       break;
    }
    update();
}

void Boss::selfHeal()
{
    hp +=10;
}

QRectF Boss::boundingRect()const
{
    return QRectF(-30,-30,60,60);
}

QPainterPath Boss::shape()const
{
   QPainterPath path;
   path.addEllipse(boundingRect());
   return path;
}

void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-30,-30,60,60,pix,0,0,60,60);
}


