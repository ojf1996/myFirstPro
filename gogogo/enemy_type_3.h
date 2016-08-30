#ifndef ENEMY_TYPE_3_H
#define ENEMY_TYPE_3_H

#include"enemy.h"

class Enemy_type_3 : public Enemy
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Enemy_type_3(qreal,qreal);
    void attack();
protected:
    void advance(int);
    void handleCollisions();
    void changePicture();
signals:
    void removeEnemy(QGraphicsItem *);

private:
    int count;//换图
    int speed;//调整刷新频率
    int dir;//调节随机走向
};

#endif // ENEMY_TYPE_3_H
