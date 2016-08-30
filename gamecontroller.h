#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include"constants.h"
#include"hero.h"

class QGraphicsScene;
class QKeyEvent;
class QGraphicsItem;
class PunchItem;
class Map;
class JumpItem;
class Hurt;
class StuffItem;

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    Hero * getHero()const{
        return hero;
    }

signals:
    void gameOver();
    void bye();
    void tab();
    void getStuff(int);
    void getFuel(int);

public slots:
    //***************** 暂停等 *************
    void pause();
    void resume();
    void deleteItem(QGraphicsItem *);
    void initMap();
    void restart();
    void virtory();
    //**************** 技能 *******************
    void fuelAutoUp(){
        if(fuel +5 <= 100)
            fuel += 5;
        else
            fuel = 100;
        emit getFuel(fuel);
        hero->heal(3);
    }

    void fuelUp(int a){
        if(fuel + a >= 100)
            fuel = 100;
        else
            fuel += a;
        emit getFuel(fuel);
    }

    void newPunch(_Direction);//一拳
    void bigOne();//四拳
    void tora_tora_tora();
    void tora(qreal,qreal,_Direction,int = 25);//虎虎虎

    //**************** 危险 *******************
    void newHurt(qreal,qreal,_Direction,int = 0);
    void heroIsDead();
    void newOMG(qreal,qreal,_Direction,int);
    void settingMadDog(qreal,qreal,_Direction);
    void settingMadBird(qreal,qreal,_Direction);
    //**************** 消灭敌人 ******************
    void enemyKill(qreal,qreal,MyType);
    //**************** 物品掉落 *******************
    void stuffDrop(qreal,qreal,int);
    void stuffPickUp(int);
protected:
     bool eventFilter(QObject *object, QEvent *event);
private:
    void handleKeyPressed(QKeyEvent *event);
    void handleKeyReleased(QKeyEvent *event);
    int fuel;
    QTimer timer;
    QTimer _timer;
    QGraphicsScene &scene;

    Hero * hero;
    Map * map;
};

#endif // GAMECONTROLLER_H
