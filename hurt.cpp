#include "hurt.h"
#include"hero.h"
#include<QPainter>

Hurt::Hurt(qreal x,qreal y,_Direction dir,int _t)
    : moveDirection(dir),picName(":/source/image/hurt.png"),
      _type(_t)
{
    setPos(x,y);
    setData(G_O_Type,Hurt_Type);
}

QRectF Hurt::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath Hurt::shape()const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Hurt::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}

void Hurt::moveDown()
{
     setPos(this->x(),this->y()+Size/5);
}

void Hurt::moveUp()
{
     setPos(this->x(),this->y()-Size/5);
}

void Hurt::moveLeft()
{
     setPos(this->x()-Size/5,this->y());
}

void Hurt::moveRight()
{
     setPos(this->x()+Size/5,this->y());
}

void Hurt::moveLeftUp()
{
    setPos(this->x()-Size/5,this->y()-Size/5);
}

void Hurt::moveLeftDown()
{
    setPos(this->x()-Size/5,this->y()+Size/5);
}

void Hurt::moveRightDown()
{
    setPos(this->x()+Size/5,this->y()+Size/5);
}

void Hurt::moveRightUp()
{
    setPos(this->x()+Size/5,this->y()-Size/5);
}

void Hurt::advance(int step)
{
    if (!step) {
        return;
    }
    if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+10)
    {
        emit removeHurt(this);
        return;
    }
    if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+10)
    {
        emit removeHurt(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).y()>SceneLength-10)
    {
        emit removeHurt(this);
        return;
    }

    if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-10)
    {
        emit removeHurt(this);
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

void Hurt::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if(collidingItem->data(G_O_Type)==Block_Type )
        {
            emit removeHurt(this);
            return;
        }
        if(collidingItem->data(G_O_Type) == Hero_Type){
            switch (_type) {
            case 0:
                dynamic_cast<Hero *>(collidingItem)->Killing();
                emit removeHurt(this);
                return;
            case 1:
                dynamic_cast<Hero *>(collidingItem)->hpLose();
                emit removeHurt(this);
                return;
            case 2:
                dynamic_cast<Hero *>(collidingItem)->poisoned();
                emit removeHurt(this);
                return;
            case 3:
                dynamic_cast<Hero *>(collidingItem)->stuck();
                emit removeHurt(this);
                return;
            case 4:
                dynamic_cast<Hero *>(collidingItem)->mess();
                emit removeHurt(this);
                return;
            default:
                break;
            }

        }
        if(collidingItem->data(G_O_Type) == Punch_Type || collidingItem->data(G_O_Type) == Fire_Type){
            emit removeHurt(this);
            return;
        }
    }
}

Hurt::~Hurt()
{
    qDebug()<<"hurt dismiss";
}
