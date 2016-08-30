#include "enemy_type_3.h"
#include"hero.h"

Enemy_type_3::Enemy_type_3(qreal x,qreal y):Enemy(x,y),count(0),dir(0)
{
    changePicture();
}

void Enemy_type_3::changePicture()
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
            _picName = ":/source/image/enemy_type_3_left_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_3_left_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_3_left_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_3_left_2";
            setPicName(_picName);
            break;
        }
        break;
    case Right:
        switch (int(count))
        {
        case 0:
            _picName = ":/source/image/enemy_type_3_right_1";
            setPicName(_picName);
            break;
        case 1:
            _picName = ":/source/image/enemy_type_3_right_2";
            setPicName(_picName);
            break;
        case 2:
            _picName = ":/source/image/enemy_type_3_right_3";
            setPicName(_picName);
            break;
        case 3:
            _picName = ":/source/image/enemy_type_3_right_2";
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

void Enemy_type_3::attack()
{
    emit hit(this->x(),this->y(),getMoveDirection(),3);
}

void Enemy_type_3::advance(int step)
{
    if(!step)
        return;

    if(speed++%3!=0)
        return;
    if(getHp()<=0){
        emit enemyKillAt(this->x(),this->y(),Enemy_Type);
        emit removeEnemy(this);
        return;
    }

    changePicture();
    update();

    if(isMad()){
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
        //边界检查
        handleCollisions();
        return;
    }
    else{
        dir++;
        if(dir >= 40)
            dir = 0;
        switch (dir) {
        case 0:
            setMoveDirection(Left);
            break;
        case 1:
            attack();
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        case 14:
            setMoveDirection(Right);
            break;
        case 15:
        case 16:
            break;
        case 17:
            attack();
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
            break;

        case 30:
            setMoveDirection(Left);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:

            break;
        default:
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
    }
    handleCollisions();
}

void Enemy_type_3::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions){
        if(collidingItem->data(G_O_Type)==Hero_Type){
           dynamic_cast<Hero *>(collidingItem)->Killing();
           return;
        }
        if(collidingItem->data(G_O_Type) == Block_Type)
        {
            switch (this->getMoveDirection()) {
            case Left:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
                moveRight();
                break;
            case Right:
                if(isMad()){
                    emit enemyKillAt(this->x(),this->y(),Enemy_Type);
                    emit removeEnemy(this);
                    return;
                }
                moveLeft();
                break;
            default:
                break;
            }
            return;
        }
    }
}

