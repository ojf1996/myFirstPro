#include <QPainter>
#include<QDebug>
#include "gamecontroller.h"
#include "punchitem.h"
#include"enemy_type_1.h"
#include"trap.h"
#include"boss.h"

PunchItem::PunchItem(qreal x,qreal y,_Direction dir,int a)
    :moveDirection(dir),atk(a)
{
    setPos(x,y);
    setData(G_O_Type,Punch_Type);
}

QRectF PunchItem::boundingRect()const
{
    return QRectF(-10,-10,20,20);
}

QPainterPath PunchItem::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void PunchItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   QString picName = ":/source/image/punch_left.png";
   switch (moveDirection) {
   case Left:
   case LeftUp:
   case LeftDown:
       picName = ":/source/image/punch_left.png";
       break;
   case Right:
   case RightUp:
   case RightDown:
       picName = ":/source/image/punch_right.png";
       break;
   case Down:
       picName = ":/source/image/punch_down.png";
       break;
   case Up:
       picName = ":/source/image/punch_up.png";
       break;
   default:
       picName = ":/source/image/punch_left.png";
       break;
   }
   QPixmap pic(picName);
   painter->drawPixmap(-10,-10,20,20,pic,0,0,20,20);
}

void PunchItem::moveDown()
{
     setPos(this->x(),this->y()+Size/3);
}

void PunchItem::moveUp()
{
     setPos(this->x(),this->y()-Size/3);
}

void PunchItem::moveLeft()
{
     setPos(this->x()-Size/3,this->y());
}

void PunchItem::moveRight()
{
     setPos(this->x()+Size/3,this->y());
}


void PunchItem::advance(int step)
{
    if (!step) {
        return;
    }
    if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+10)
    {
        emit removePunch(this);
        return;
    }
    if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+10)
    {
        emit removePunch(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).y()>SceneLength-10)
    {
        emit removePunch(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-10)
    {
        emit removePunch(this);
        return;
    }

    switch (moveDirection)
    {
        case Left:
            moveLeft();
            break;
        case Right:
            moveRight();
            break;
        case Up:
            moveUp();
            break;
        case Down:
            moveDown();
            break;
    case LeftUp:
        moveLeftUp();
        break;
    case LeftDown:
        moveLeftDown();
        break;
    case RightDown:
        moveRightDown();
        break;
    case RightUp:
        moveRightUp();
        break;
        default:
            break;
    }

    handleCollisions();
}

void PunchItem::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if( collidingItem){
            if(collidingItem->data(G_O_Type)==Block_Type )
            {
                qDebug()<<"punch byebye";
                emit removePunch(this);
                return;
            }
            if(collidingItem->data(G_O_Type)==Enemy_Type)
             {
                dynamic_cast<Enemy *>(collidingItem)->hpLose(atk);
                dynamic_cast<Enemy *>(collidingItem)->back();
                qDebug()<<"hit";
                emit removePunch(this);
                return;
            }
            if(collidingItem->data(G_O_Type) == Hurt_Type || collidingItem->data(G_O_Type) == OMG_Type)
            {
                emit removePunch(this);
                return;
            }
            if(collidingItem->data(G_O_Type) == Trap_Type)
            {
                dynamic_cast<Trap * >(collidingItem)->beAttacked(atk);
                emit removePunch(this);
                return;
            }
            if(collidingItem->data(G_O_Type) == Boss_Type){
                dynamic_cast<Boss*>(collidingItem)->hpLose(atk);
                emit removePunch(this);
                return;
            }
        }
    }
}


void PunchItem::moveLeftUp()
{
    setPos(this->x()-Size/3,this->y()-Size/3);
}

void PunchItem::moveLeftDown()
{
    setPos(this->x()-Size/3,this->y()+Size/3);
}

void PunchItem::moveRightDown()
{
    setPos(this->x()+Size/3,this->y()+Size/3);
}

void PunchItem::moveRightUp()
{
    setPos(this->x()+Size/3,this->y()-Size/3);
}

PunchItem::~PunchItem()
{
    qDebug()<<"punch dismiss";
}
