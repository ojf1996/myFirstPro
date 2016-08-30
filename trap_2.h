 #ifndef TRAP_2_H
#define TRAP_2_H

#include"trap.h"

class Trap_2 : public Trap
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Trap_2(qreal,qreal);
public slots:
    void trigger();
protected:
    void advance(int);
private:
    int dir;
    bool _trigger;
};

#endif // TRAP_2_H
