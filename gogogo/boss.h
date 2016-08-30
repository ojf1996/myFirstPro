#ifndef BOSS_H
#define BOSS_H

#include"constants.h"
#include <QObject>
#include<QGraphicsItem>
#include<QTimer>
#include<QString>
#include<QSound>

class Boss : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit Boss(qreal,qreal);

    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
    void setHp(int a){hp = a;}
    ~Boss(){
        QSound::play(":/sound/sound/laugh_sound.wav");
    }

public slots:

    void attack_mess();//发出令人混乱的
    void attack_poison();//中毒的
    void attack_stuck();//眩晕的
    void attack_destory();//毁灭一击

    void theRush();

    void resetPos();//归位

    void stopFireEnd();//休息完了

    void callingUnit();//召唤小弟
    void selfHeal();//回血
    void hpLose(int a){hp -=a;}


signals:
    void theEnd();
    void removeBoss(QGraphicsItem *);
    void hit(qreal,qreal,_Direction,int);
    void callingMadDog(qreal,qreal,_Direction);
    void callingMadBird(qreal,qreal,_Direction);
    void callingSupport(qreal,qreal);

protected:
    void changPicName();
    void advance(int phase);

    void handleCollisions();
private:
    QTimer time_rush_begin;
    QTimer time_rush_end;
    QTimer time_attack_1;
    QTimer time_attack_2;
    QTimer time_attack_3;
    QTimer time_attack_4;
    QTimer time_callingUnit;
    QTimer time_relax_end;
    qreal _x;
    qreal _y;
    bool rush;
    int hp;
    int count;
    QString picName;
};

#endif // BOSS_H
