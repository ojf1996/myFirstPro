#ifndef ENEMY_TYPE_2_H
#define ENEMY_TYPE_2_H

#include"enemy.h"

class Enemy_type_2 : public Enemy
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Enemy_type_2(qreal,qreal);
    void attack();
    QPainterPath shape()const;
protected:
    void advance(int step);
    void handleCollisions();
signals:
    void removeEnemy(QGraphicsItem *);
};

#endif // ENEMY_TYPE_2_H
