#ifndef TRAP_1_H
#define TRAP_1_H

#include <QObject>
#include<QTimer>
#include"trap.h"
#include"constants.h"

class Trap_1 :public Trap
{   
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Trap_1(qreal,qreal,_Direction dir = Left,_Direction = Left,bool =false);
    ~Trap_1();
public slots:
    void trigger();
protected:
    void advance(int);
private:
    _Direction towards;
    _Direction moveDir;
    int type;
    bool moveAble;
    int speed;
    int count;
    bool _trigger;
};

#endif // TRAP_1_H
