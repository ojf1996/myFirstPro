#include <QPainter>
#include<QDebug>
#include "gamecontroller.h"
#include "hero.h"
#include"enemy_type_1.h"
#include"jumpitem.h"
#include"trap.h"
#include"stuffitem.h"


Hero::Hero() :
    count(0),speed(0),_punch(false),moving(true),moveDirection(Down),
    level(1),currentExp(0),xp(100),hp(100),hpMax(100),atk(10),
    isPoisoned(false),isStuck(false),isMess(false)
{
    setData(G_O_Type,Hero_Type);
    picName = ":/source/image/move_down_2.png";
    connect(this,SIGNAL(isUnusal(int)),&time,SLOT(start(int)));
    connect(&time,SIGNAL(timeout()),this,SLOT(purify()));
    emit getHp(hp);
    emit getHpMax(hpMax);
    emit getCXp(currentExp);
    emit getExpMax(xp);
    emit getAtk(atk);
}

QRectF Hero::boundingRect() const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

void Hero::changePicture()
{
    count++;
    if(count >= 7)
        count = 0;
    if(!_punch){
    switch (moveDirection)
    {
    case Left:
        switch (int(count%4))
        {
        case 0:
            picName = ":/source/image/move_left_1";
            break;
        case 1:
            picName = ":/source/image/move_left_2";
            break;
        case 2:
            picName = ":/source/image/move_left_3";
            break;
        case 3:
            picName = ":/source/image/move_left_2";
            break;
        }
        break;
    case Right:
        switch (int(count%4))
        {
        case 0:
            picName = ":/source/image/move_right_1";
            break;
        case 1:
            picName = ":/source/image/move_right_2";
            break;
        case 2:
            picName = ":/source/image/move_right_3";
            break;
        case 3:
            picName = ":/source/image/move_right_2";
            break;
        }
        break;
    case Down:
        switch (int(count%4))
        {
        case 0:
            picName = ":/source/image/move_down_1";
            break;
        case 1:
            picName = ":/source/image/move_down_2";
            break;
        case 2:
            picName = ":/source/image/move_down_3";
            break;
        case 3:
            picName = ":/source/image/move_down_2";
            break;
        }
        break;
    case Up:
        switch (int(count%4))
        {
        case 0:
            picName = ":/source/image/move_up_1";
            break;
        case 1:
            picName = ":/source/image/move_up_2";
            break;
        case 2:
            picName = ":/source/image/move_up_3";
            break;
        case 3:
            picName = ":/source/image/move_up_2";
            break;
        }
        break;
    default:
        picName = ":/source/image/move_up_2";
        break;
    }
    }
    else
    {
        switch (moveDirection) {
        case Left:
            switch (int(count))
            {
            case 0:
                picName = ":/source/image/punch_left_1";
                break;
            case 1:
                picName = ":/source/image/punch_left_2";
                break;
            case 2:
                picName = ":/source/image/punch_left_3";
                break;
            case 3:
                picName = ":/source/image/punch_left_4";
                break;
            case 4:
                picName = ":/source/image/punch_left_5";
                break;
            case 5:
                picName = ":/source/image/punch_left_6";
                break;
            case 6:
                picName = ":/source/image/punch_left_7";
                break;
            }
            break;
        case Right:
            switch (int(count))
            {
            case 0:
                picName = ":/source/image/punch_right_1";
                break;
            case 1:
                picName = ":/source/image/punch_right_2";
                break;
            case 2:
                picName = ":/source/image/punch_right_3";
                break;
            case 3:
                picName = ":/source/image/punch_right_4";
                break;
            case 4:
                picName = ":/source/image/punch_right_5";
                break;
            case 5:
                picName = ":/source/image/punch_right_6";
                break;
            case 6:
                picName = ":/source/image/punch_right_7";
                break;
            }
            break;
        case Up:
            switch (int(count))
            {
            case 0:
                picName = ":/source/image/punch_up_1";
                break;
            case 1:
                picName = ":/source/image/punch_up_2";
                break;
            case 2:
                picName = ":/source/image/punch_up_3";
                break;
            case 3:
                picName = ":/source/image/punch_up_4";
                break;
            case 4:
                picName = ":/source/image/punch_up_5";
                break;
            case 5:
                picName = ":/source/image/punch_up_6";
                break;
            case 6:
                picName = ":/source/image/punch_up_7";
                break;
            }
            break;
        case Down:
            switch (int(count))
            {
            case 0:
                picName = ":/source/image/punch_down_1";
                break;
            case 1:
                picName = ":/source/image/punch_down_2";
                break;
            case 2:
                picName = ":/source/image/punch_down_3";
                break;
            case 3:
                picName = ":/source/image/punch_down_4";
                break;
            case 4:
                picName = ":/source/image/punch_down_5";
                break;
            case 5:
                picName = ":/source/image/punch_down_6";
                break;
            case 6:
                picName = ":/source/image/punch_down_7";
                break;
            }
            break;
        default:
            break;
        }
    }
}


void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPixmap pix(picName);
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}

void Hero::setMoveDirection(_Direction direction)
{
    moveDirection = direction;
}

void Hero::advance(int step)
{
    if (!step) {
        return;
    }

    if(speed++%3!=0)
        return;


    if(isPoisoned && hp - 5 > 0 ){
        hp -=0.5;
        emit getHp(hp);
        emit getHpMax(hpMax);
    }

    if(hp<=0){
        QSound::play(":/sound/sound/ko_sound.wav");
        emit IamDead();
        return;
    }

    if (!moving || isStuck)
    {
        return;
    }

    //边界检测
    if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+Size/2)
    {
        moveRight();
        return;
    }
    if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+Size/2)
    {
        moveDown();
        return;
    }

    if(this->mapToScene(this->x(),this->y()).y()>SceneLength-Size/2)
    {
        moveUp();
        return;
    }

    if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-Size/2)
    {
        moveLeft();
        return;
    }
    //实时移动，出拳
        switch (moveDirection)
        {
            case Left:
                if(!isMess){ break;}
                else{setMoveDirection(Right);break;}
            case Right:
                if(!isMess){break;}
                else{setMoveDirection(Left);break;}
            case Up:
                if(!isMess){break;}
                else{setMoveDirection(Down);break;}
            case Down:
                if(!isMess){ break;}
                else{setMoveDirection(Up);break;}
            default:
                break;
        }
        changePicture();
        update();

    handleCollisions();
}

void Hero::flash()
{
    switch (moveDirection)
    {
        case Left:
            setPos(this->x()-Size*5/2.0,this->y());
            break;
        case Right:
            setPos(this->x()+Size*5/2.0,this->y());
            break;
        case Up:
            setPos(this->x(),this->y()-Size*5/2.0);
            break;
        case Down:
            setPos(this->x(),this->y()+Size*5/2.0);
            break;
        default:
            break;
    }
}

void Hero::moveLeft()
{
    setPos(this->x()-Size/2,this->y());
}

void Hero::moveRight()
{
    setPos(this->x()+Size/2,this->y());
}
\
void Hero::moveUp()
{
    setPos(this->x(),this->y()-Size/2);
}

void Hero::moveDown()
{
    setPos(this->x(),this->y()+Size/2);
}

QPainterPath Hero::shape()
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

_Direction Hero::getMoveDirection()const
{
    return moveDirection;
}

void Hero::noPunch()
{
    _punch = false;
}

void Hero::punch()
{
    _punch = true;
}

void Hero::stopMoveing()
{
    moving = false;
}

void Hero::move()
{
    moving = true;
}

void Hero::handleCollisions()
{
     QList<QGraphicsItem *> collisions = collidingItems();
     foreach (QGraphicsItem *collidingItem, collisions) {
         if(collidingItem->data(G_O_Type) == Block_Type)
         {
             this->Killing();
             return;
         }
         if(collidingItem->data(G_O_Type) == Enemy_Type && _punch)
         {
             dynamic_cast<Enemy *>(collidingItem)->hpLose(atk);
             return;
         }
         if(collidingItem->data(G_O_Type) == Trap_Type )
         {
             dynamic_cast<Trap *>(collidingItem)->trigger();
             return;
         }
         if(collidingItem->data(G_O_Type) == Jumping_Type)
         {
             dynamic_cast<JumpItem*>(collidingItem)->trigger();
             return;
         }
         if(collidingItem->data(G_O_Type) == Stuff_Type)
         {
             dynamic_cast<StuffItem *>(collidingItem)->trigger();
             return;
         }
     }
}
