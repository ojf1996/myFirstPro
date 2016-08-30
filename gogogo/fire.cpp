#include<QPainter>
#include<QThread>
#include<QDebug>
#include "fire.h"
#include"blockitem.h"
#include"enemy.h"
#include"trap.h"
#include"boss.h"

Fire::Fire(qreal x,qreal y,_Direction dir,int a)
    :picName(""),moveDirection(dir),atk(5),num(0),count(1),speed(0)
{
    setPos(x,y);
    setData(G_O_Type,Fire_Type);
}

QRectF Fire::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath Fire::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Fire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!(picName.isEmpty())){
       QPixmap pix(picName);
       painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
    }
}
void Fire::changePicture()
{
    QString _picName="";
    count++;
    if(count >= 18)
        count = 1;
    switch (int(count)) {
    case 1:
        _picName = ":/source/image/fire_1.png";
        setPicName(_picName);
        break;
    case 2:
        _picName = ":/source/image/fire_2.png";
        setPicName(_picName);
        break;
    case 3:
        _picName = ":/source/image/fire_3.png";
        setPicName(_picName);
        break;
    case 4:
        _picName = ":/source/image/fire_4.png";
        setPicName(_picName);
        break;
    case 5:
        _picName = ":/source/image/fire_5.png";
        setPicName(_picName);
        break;
    case 6:
        _picName = ":/source/image/fire_6.png";
        setPicName(_picName);
        break;
    case 7:
        _picName = ":/source/image/fire_7.png";
        setPicName(_picName);
        break;
    case 8:
        _picName = ":/source/image/fire_8.png";
        setPicName(_picName);
        break;
    case 9:
        _picName = ":/source/image/fire_9.png";
        setPicName(_picName);
        break;
    case 10:
        _picName = ":/source/image/fire_10.png";
        setPicName(_picName);
        break;
    case 11:
        _picName = ":/source/image/fire_11.png";
        setPicName(_picName);
        break;
    case 12:
        _picName = ":/source/image/fire_12.png";
        setPicName(_picName);
        break;
    case 13:
        _picName = ":/source/image/fire_13.png";
        setPicName(_picName);
        break;
    case 14:
        _picName = ":/source/image/fire_14.png";
        setPicName(_picName);
        break;
    case 15:
        _picName = ":/source/image/fire_15.png";
        setPicName(_picName);
        break;
    case 16:
        _picName = ":/source/image/fire_16.png";
        setPicName(_picName);
        break;
    case 17:
        _picName = ":/source/image/fire_17.png";
        setPicName(_picName);
        break;
    default:
        break;
    }
}

void Fire::moveLeft()
{
    setPos(this->x() - Size/5,this->y());
}

void Fire::moveUp()
{
    setPos(this->x(),this->y()-Size/5);
}

void Fire::moveDown()
{
    setPos(this->x(),this->y()+Size/5);
}

void Fire::moveRight()
{
    setPos(this->x()+Size/5,this->y());
}

void Fire::moveLeftUp()
{
    setPos(this->x()-Size/5,this->y()-Size/5);
}

void Fire::moveLeftDown()
{
    setPos(this->x()-Size/5,this->y()+Size/5);
}

void Fire::moveRightUp()
{
    setPos(this->x()+Size/5,this->y()-Size/5);
}

void Fire::moveRightDown()
{
    setPos(this->x()+Size/5,this->y()+Size/5);
}

void Fire::advance(int step)
{
    if (!step) {
        return;
    }

    if(speed++%3!=0){
        if(speed > 80)
            speed = 0;
        return;
    }

    changePicture();
    update();
//    if(num == 2){
//        emit removeFire(this);
//    }

    if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+10)
    {
        emit removeFire(this);
        return;
    }
    if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+10)
    {
        emit removeFire(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).y()>SceneLength-10)
    {
        emit removeFire(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-10)
    {
        emit removeFire(this);
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

void Fire::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if( collidingItem){
            if(collidingItem->data(G_O_Type)==Block_Type )
            {
                qDebug()<<"fire byebye";
                emit removeFire(this);
                return;
            }
            if(collidingItem->data(G_O_Type)==Enemy_Type)
             {
                dynamic_cast<Enemy *>(collidingItem)->hpLose(atk);
                dynamic_cast<Enemy *>(collidingItem)->back();
                qDebug()<<"boom";
                emit boom(this->x()-Size/2,this->y()-Size/2,LeftUp,atk);

                emit boom(this->x()+Size/2,this->y()+Size/2,LeftDown,atk);

                emit boom(this->x()+Size/2,this->y()-Size/2,RightUp,atk);

                emit boom(this->x()+Size/2,this->y()+Size/2,RightDown,atk);

                return;
            }
            if(collidingItem->data(G_O_Type) == Trap_Type)
            {
                dynamic_cast<Trap * >(collidingItem)->beAttacked(atk);
                emit boom(this->x(),this->y()-Size/2,moveDirection,atk);
                return;
            }
            if(collidingItem->data(G_O_Type) == Boss_Type){
                dynamic_cast<Boss *>(collidingItem)->hpLose(atk * 10);
                emit removeFire(this);
                return;
            }
        }
    }
}

Fire::~Fire()
{
    qDebug()<<"Fire dismiss";
}
