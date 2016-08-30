#ifndef TRAP_3_H
#define TRAP_3_H

#include"trap.h"

class Trap_3 : public Trap
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Trap_3(qreal,qreal);
    QPainterPath shape()const;
    void trigger();
protected:
    void advance(int);
    void handleCollisions();
private:
    _Direction dir;
    bool _trigger;
};

#endif // TRAP_3_H
