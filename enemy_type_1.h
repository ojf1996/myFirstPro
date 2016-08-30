#ifndef ENEMY_TYPE_1_H
#define ENEMY_TYPE_1_H

#include"enemy.h"

class Enemy_type_1 : public Enemy
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Enemy_type_1(qreal,qreal);
    void attack();
protected:
    virtual void advance(int);
    virtual void changePicture();
    void handleCollisions();
signals:
    void removeEnemy(QGraphicsItem *);
private:
    int count;//换图
    int speed;//调整刷新频率
    int dir;//调节随机走向
};

#endif // ENEMY_TYPE_1_H
