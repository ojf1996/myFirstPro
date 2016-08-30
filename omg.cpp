#include "omg.h"
#include"hero.h"

OMG::OMG(qreal x,qreal y,_Direction dir,int _t):moveDirection(dir),picName(""),type(_t),hitTime(0),count(0)
{
    setPos(x,y);
    setData(G_O_Type,OMG_Type);
    time.singleShot(500,this,SLOT(trigger()));
    changePic();
}

void OMG::changePic()
{
    if(count >= 9 )
        count = 0;
    count++;
    switch(count){
        case 1:
            setPicName(":/source/image/omg_1.png");
        break;
        case 2:
            setPicName(":/source/image/omg_2.png");
        break;
        case 3:
            setPicName(":/source/image/omg_3.png");
        break;
        case 4:
            setPicName(":/source/image/omg_4.png");
        break;
        case 5:
            setPicName(":/source/image/omg_5.png");
        break;
        case 6:
            setPicName(":/source/image/omg_6.png");
        break;
        case 7:
            setPicName(":/source/image/omg_7.png");
        break;
        case 8:
            setPicName(":/source/image/omg_8.png");
        break;
        default:
            break;
    }
    update();
}

QRectF OMG::boundingRect()const
{
    return QRectF(-75,-75,150,150);
}

QPainterPath OMG::shape()const
{
    QPainterPath path;
    path.addEllipse(QRectF(-70,-50,140,100));
    return path;
}

void OMG::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-75,-75,150,150,pix,0,0,150,150);
}

void OMG::trigger()
{
    emit boom(this->x(),this->y(),Up,type);
    emit boom(this->x(),this->y(),Left,type);
    emit boom(this->x(),this->y(),LeftUp,type);
    emit boom(this->x(),this->y(),LeftDown,type);
    emit boom(this->x(),this->y(),Right,type);
    emit boom(this->x(),this->y(),RightUp,type);
    emit boom(this->x(),this->y(),RightDown,type);
    emit boom(this->x(),this->y(),Down,type);
    return;
}

void OMG::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if(collidingItem->data(G_O_Type) == Hero_Type){
            dynamic_cast<Hero *>(collidingItem)->hpLose();
            return;
        }
        if(collidingItem->data(G_O_Type) == Block_Type)
        {
            time.stop();
            disconnect(&time,SIGNAL(timeout()),this,SLOT(trigger()));
            emit removeOMG(this);
            return;
        }
    }
}

void OMG::advance(int step)
{
    if(!step)
        return;

    changePic();
    update();

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

    if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+10)
    {
        disconnect(&time,SIGNAL(timeout()),this,SLOT(trigger()));
        emit removeOMG(this);
        return;
    }
    if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+10)
    {
        disconnect(&time,SIGNAL(timeout()),this,SLOT(trigger()));
        emit removeOMG(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).y()>SceneLength-10)
    {
        disconnect(&time,SIGNAL(timeout()),this,SLOT(trigger()));
        emit removeOMG(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-10)
    {
        disconnect(&time,SIGNAL(timeout()),this,SLOT(trigger()));
        emit removeOMG(this);
        return;
    }

    handleCollisions();
}

