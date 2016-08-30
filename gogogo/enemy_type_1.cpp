#include<QDebug>
#include<QTime>
#include "enemy_type_1.h"
#include"hero.h"
#include"gamecontroller.h"

Enemy_type_1::Enemy_type_1(qreal x,qreal y)
    :Enemy(x,y),
      count(0),
      speed(0),
      dir(0)
{}

void Enemy_type_1::changePicture()
{
    QString _picName;
    count++;
    if(count >= 4)
        count = 0;
    switch (getMoveDirection()) {
    case Left:
        switch (int(count))
        {
        case 0:
            _picName = ":/source/image/enemy_type_1_left_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_1_left_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_1_left_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_1_left_2";
            setPicName(_picName);
            break;
        }
        break;
    case Right:
        switch (int(count))
        {
        case 0:
            _picName = ":/source/image/enemy_type_1_right_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_1_right_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_1_right_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_1_right_2";
            setPicName(_picName);
            break;
        }
        break;
    case Up:
        switch (int(count))
        {
        case 0:
            _picName = ":/source/image/enemy_type_1_up_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_1_up_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_1_up_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_1_up_2";
            setPicName(_picName);
            break;
        }
        break;
    case Down:
        switch (int(count))
        {
        case 0:
            _picName = ":/source/image/enemy_type_1_down_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_1_down_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_1_down_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_1_down_2";
            setPicName(_picName);
            break;
        }
        break;
    default:
        _picName = ":/source/image/enemy_type_1_down_2";
        setPicName(_picName);
        break;
    }
}

void Enemy_type_1::advance(int step)
{
    if(!step)
        return;
    if(speed++%3!=0)
        return;

    //血量检测
    if(getHp()<=0)
    {
        emit enemyKillAt(this->x(),this->y(),Enemy_Type);
        emit removeEnemy(this);
        return;
    }

    if(isMad())
    {   //最后的冲刺
        //检查边界
        if(!shoot){
            attack();
            shoot = true;
        }
        if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+Size/2)
        {
            emit enemyKillAt(this->x(),this->y(),Enemy_Type);
            emit removeEnemy(this);
            return;
        }
        if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+Size/2)
        {
            emit enemyKillAt(this->x(),this->y(),Enemy_Type);
            emit removeEnemy(this);
            return;
        }

        if(this->mapToScene(this->x(),this->y()).y()>SceneLength-Size/2)
        {
            emit enemyKillAt(this->x(),this->y(),Enemy_Type);
            emit removeEnemy(this);
            return;
        }

        if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-Size/2)
        {
            emit enemyKillAt(this->x(),this->y(),Enemy_Type);
            emit removeEnemy(this);
            return;
        }
        switch (getMoveDirection())
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
        default:
            break;
        }
        changePicture();
        update();
        //边界检查
        handleCollisions();
        return;
    }
    else
    {
        dir++;
        if(dir >= 60)
            dir = 0;

        switch (dir) {
        case 0:
        case 1:
        case 2:
            setMoveDirection(Up);
            break;
        case 10:
        case 11:
        case 12:
            setMoveDirection(Down);
            break;
        case 18:
        case 19:
        case 20:
            setMoveDirection(Left);
            break;
        case 28:
        case 29:
        case 30:
            setMoveDirection(Right);
            break;
        case 38:
        case 39:
        case 40:
            setMoveDirection(Right);
            break;
        case 48:
        case 49:
        case 50:
            setMoveDirection(Left);
            break;
        default:
            return;
        }
        //边界检查
        if(this->mapToScene(this->x(),this->y()).x()<-SceneWidth+Size/2)
        {
            moveRight();
        }
        if(this->mapToScene(this->x(),this->y()).y()<-SceneLength+Size/2)
        {
            moveLeft();
        }

        if(this->mapToScene(this->x(),this->y()).y()>SceneLength-Size/2)
        {
            moveUp();
        }

        if(this->mapToScene(this->x(),this->y()).x()>SceneWidth-Size/2)
        {
            moveDown();
        }

        switch (getMoveDirection())
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
        default:
            break;
        }
    }
    changePicture();
    update();
    handleCollisions();
}

void Enemy_type_1::attack()
{
    emit hit(this->x(),this->y(),this->getMoveDirection(),1);
}

void Enemy_type_1::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if(collidingItem->data(G_O_Type) == Block_Type)
        {
            switch (this->getMoveDirection()) {
            case Left:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
                setMoveDirection(Right);
                break;
            case Right:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
                setMoveDirection(Left);
                break;
            case Up:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
               setMoveDirection(Down);
                break;
            case Down:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
                setMoveDirection(Up);
            default:
                break;
            }
            return;
        }
    }
}

