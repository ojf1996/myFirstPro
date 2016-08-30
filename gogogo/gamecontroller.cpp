#include <QEvent>
#include<QSound>
#include<QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include<QFile>
#include<QTime>

#include "enemy.h"
#include"constants.h"
#include "punchitem.h"
#include "hurt.h"
#include "gamecontroller.h"
#include "jumpitem.h"
#include "blockitem.h"
#include "enemy_type_1.h"
#include"enemy_type_2.h"
#include"enemy_type_3.h"
#include "map.h"
#include "trap.h"
#include"trap_1.h"
#include"trap_2.h"
#include"trap_3.h"
#include"stuffitem.h"
#include"fire.h"
#include"omg.h"
#include"boss.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    fuel(100),
    scene(scene),     
    hero(new Hero()),
    map(new Map(this))
{
    timer.start( 1000/33 );
    _timer.start(3000);

    connect(map,SIGNAL(changeMap()),this,SLOT(initMap()));

    scene.addItem(hero);
    connect(hero,SIGNAL(IamDead()),this,SLOT(heroIsDead()));

    initMap();
    scene.installEventFilter(this);

    resume();
    connect(&_timer,SIGNAL(timeout()),this,SLOT(fuelAutoUp()));
}

GameController::~GameController()
{
    delete hero;
}

void GameController::initMap()
{
    int _back = 0;
    {
    QList<QGraphicsItem *> item = scene.items();
    foreach (QGraphicsItem *_item, item) {
        if(_item != hero){
         scene.removeItem(_item);
         delete _item;
            }
        }
    }
    QFile file(":/source/data/map.dat");
    file.open(QIODevice::ReadOnly);
    file.seek(sizeof(Dimao) * 16 * 20 * map->mapId);
    Dimao temp = Kong;
    for(int y = 0; y < 16; ++y)
        for(int x = 0; x < 20; ++x)
        {
            file.read((char*)(&temp),sizeof(Dimao));
            qreal _x= -SceneWidth/2 + 20 + x * 40;
            qreal _y= -SceneLength/2 + 20 + y * 40;
            switch (temp) {
            case Kong:
                 break;
            case Tree:{
                 BlockItem * _item = new BlockItem(_x,_y,Tree);
                 qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                 scene.addItem(_item);
                break;}
            case Water_Center:{
                BlockItem * _item = new BlockItem(_x,_y,Water_Center);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Water_Left:{
                BlockItem * _item = new BlockItem(_x,_y,Water_Left);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Water_Right:{
                BlockItem * _item = new BlockItem(_x,_y,Water_Right);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Water_Up:{
                BlockItem * _item = new BlockItem(_x,_y,Water_Up);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Water_Down:{
                BlockItem * _item = new BlockItem(_x,_y,Water_Down);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Rock:{
                BlockItem * _item = new BlockItem(_x,_y,Rock);
                qDebug()<<_item->pos().x()<<" "<<_item->pos().y();
                scene.addItem(_item);
                break;}
            case Player:{
                qDebug()<<"player"<<endl;
                hero->setPos(_x,_y);
                if(map->mapId==0){
                }
                break;}
            case _Enemy1:{
                Enemy_type_1 * _item = new Enemy_type_1(_x,_y);
                scene.addItem(_item);
                _item->setHp(100 + 200 * map->mapId);
                connect(_item,SIGNAL(removeEnemy(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                connect(_item,SIGNAL(enemyKillAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                break;}
            case _Enemy2:{
                Enemy_type_2 * _item = new Enemy_type_2(_x,_y);
                scene.addItem(_item);
                _item->setHp(100 + 200 * map->mapId);
                connect(_item,SIGNAL(removeEnemy(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                connect(_item,SIGNAL(enemyKillAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                break;
            }
            case _Enemy3:{
                Enemy_type_3 * _item = new Enemy_type_3(_x,_y);
                _item->setMoveDirection(Left);
                scene.addItem(_item);
                _item->setHp(100 + 200 * map->mapId);
                connect(_item,SIGNAL(removeEnemy(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                connect(_item,SIGNAL(enemyKillAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                break;
            }
            case Jump:{
                if(_back<2){
                    JumpItem * _item= new JumpItem(_x,_y,map->mapId+1);
                    scene.addItem(_item);
                    connect(_item,SIGNAL(getNextMap(int)),map,SLOT(mapJump(int)));
                    _back++;
                }
                else{
                    if(map->mapId-1>=0){
                        JumpItem * _item= new JumpItem(_x,_y,map->mapId-1);
                        scene.addItem(_item);
                        connect(_item,SIGNAL(getNextMap(int)),map,SLOT(mapJump(int)));
                    _back++;
                    if(_back>=3)
                        _back = 0;
                    }
                }
                break;
            }
            case _Trap_1_Left:{
                Trap_1 * _item= new Trap_1(_x,_y,Left,Left,false);
                scene.addItem(_item);
                _item->setHp(100 + hero->_getAtk() * 5);
                connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                break;
                }
            case _Trap_1_Left_UP:{
                    Trap_1 * _item= new Trap_1(_x,_y,Left,Up,true);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                }
           case _Trap_1_Left_RIGHT:{
                    Trap_1 * _item= new Trap_1(_x,_y,Left,Left,true);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                }
           case _Trap_1_Down:{
                    Trap_1 * _item= new Trap_1(_x,_y,Down,Left,false);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                    }
           case _Trap_1_Down_UP:{
                    Trap_1 * _item= new Trap_1(_x,_y,Down,Up,true);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                    }
           case _Trap_1_Down_LEFT:{
                    Trap_1 * _item= new Trap_1(_x,_y,Down,Left,true);
                    scene.addItem(_item);
                    _item->setHp(100 + hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                    }
                case _Trap_1_Right:{
                    Trap_1 * _item= new Trap_1(_x,_y,Right,Left,false);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                    }
                case _Trap_1_Right_UP:{
                        Trap_1 * _item= new Trap_1(_x,_y,Right,Up,true);
                        scene.addItem(_item);
                        _item->setHp(100 + hero->_getAtk() * 5);
                        connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                        connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                        connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                        break;
                    }
               case _Trap_1_Right_LEFT:{
                        Trap_1 * _item= new Trap_1(_x,_y,Right,Left,true);
                        scene.addItem(_item);
                        _item->setHp(100 +  hero->_getAtk() * 5);
                        connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                        connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                        connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                        break;
                    }
                case _Trap_1_Up:{
                         Trap_1 * _item= new Trap_1(_x,_y,Up,Left,false);
                         scene.addItem(_item);
                         _item->setHp(100 +  hero->_getAtk() * 5);
                         connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                         connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                         connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                         break;
                         }
                case _Trap_1_Up_DOWN:{
                         Trap_1 * _item= new Trap_1(_x,_y,Up,Up,true);
                         scene.addItem(_item);
                         _item->setHp(100 +  hero->_getAtk() * 5);
                         connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                         connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                         connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                         break;
                         }
                case _Trap_1_Up_RIGHT:{
                         Trap_1 * _item= new Trap_1(_x,_y,Up,Left,true);
                         scene.addItem(_item);
                         _item->setHp(100 +  hero->_getAtk() * 5);
                         connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                         connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                         connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                         break;
                         }
                case _Trap_2:{
                    Trap_2 * _item= new Trap_2(_x,_y);
                    scene.addItem(_item);
                    _item->setHp(100 +  hero->_getAtk() * 5);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                }
                case _Trap_3:{
                    Trap_3 * _item= new Trap_3(_x,_y);
                    scene.addItem(_item);
                    connect(_item,SIGNAL(trapKilledAt(qreal,qreal,MyType)),this,SLOT(enemyKill(qreal,qreal,MyType)));
                    connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
                    connect(_item,SIGNAL(removeTrap(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                    break;
                }
            case _Boss:{
                Boss * _item = new Boss(_x,_y);
                _item->setHp(hero->_getAtk() * 100 + 5000);
//                _item->setHp(100);
                scene.addItem(_item);
                connect(_item,SIGNAL(theEnd()),this,SLOT(virtory()));
                connect(_item,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newOMG(qreal,qreal,_Direction,int)));
                connect(_item,SIGNAL(callingMadBird(qreal,qreal,_Direction)),this,SLOT(settingMadBird(qreal,qreal,_Direction)));
                connect(_item,SIGNAL(callingMadDog(qreal,qreal,_Direction)),this,SLOT(settingMadDog(qreal,qreal,_Direction)));
                connect(_item,SIGNAL(removeBoss(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
                break;
                }
            case _Stuff:{
                    int a = rand()%9+14;
                    stuffDrop(_x,_y,a);
                    break;
                }
            default:
                break;
           }
        }
    file.close();
    qDebug()<<"init";
}


void GameController::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
        if(hero->isStuckUp())
            break;
        if(hero->isMessUp()){
            hero->setMoveDirection(Right);
            hero->moveRight();
            hero->move();
        }
        else{
        if(hero->getMoveDirection() == Left){
            hero->moveLeft();
            hero->move();
        }
            hero->setMoveDirection(Left);
        }
            break;
        case Qt::Key_Right:
        if(hero->isStuckUp())
            break;
        if(hero->isMessUp()){
            hero->setMoveDirection(Left);
            hero->moveLeft();
            hero->move();
        }
        else{
            if(hero->getMoveDirection() == Right){
                hero->moveRight();
                hero->move();
            }
            hero->setMoveDirection(Right);

        }
            break;
        case Qt::Key_Up:
        if(hero->isStuckUp())
            break;
        if(hero->isMessUp()){
            hero->setMoveDirection(Down);
            hero->moveDown();
            hero->move();
        }
        else{
            if(hero->getMoveDirection() == Up){
            hero->moveUp();
            hero->move();
            }
            hero->setMoveDirection(Up);

        }
            break;
        case Qt::Key_Down:
        if(hero->isStuckUp())
            break;
        if(hero->isMessUp()){
            hero->setMoveDirection(Up);
            hero->moveUp();
            hero->move();
        }
        else{
            if(hero->getMoveDirection() == Down){
            hero->moveDown();
            hero->move();
            }
            hero->setMoveDirection(Down);    
        }
            break;
        case Qt::Key_A:
            hero->punch();
            break;
        default:
            break;
    }
}

void GameController::heroIsDead()
{
    hero->backToLife();
    fuel = 100;
    emit getFuel(fuel);
    initMap();
}

void GameController::restart()
{
    map->mapJump(0);
    hero->resetHpMax();
    hero->resetXpMax();

    fuel = 100;
    emit getFuel(fuel);
}

void GameController::handleKeyReleased(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        hero->noPunch();
        break;
    case Qt::Key_D:
//        QSound::play(":/sound/sound/punch_sound.wav");
        newPunch(hero->getMoveDirection());
        break;
    case Qt::Key_S:
        bigOne();
        break;
    case Qt::Key_E:
        hero->stopMoveing();
        break;
    case Qt::Key_Q:
        if(hero->_getLevel() >= 2 )
            hero->flash();
        break;
    case Qt::Key_Escape:
        emit bye();
        break;
    case Qt::Key_I:
        emit tab();
        break;
    case Qt::Key_X:
//        QSound::play(":/sound/sound/fire_sound.wav");
        tora_tora_tora();
        break;
    default:
        break;
    }
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else
    {
        if(event->type()== QEvent::KeyRelease)
        {
            handleKeyReleased((QKeyEvent * ) event );
            return true;
        }
        return QObject::eventFilter(object, event);
    }
}

void GameController::bigOne()
{
    if(fuel - 5 >= 0 ){
        newPunch(Left);
        newPunch(Right);
        newPunch(Up);
        newPunch(Down);
        fuel -= 5;
        emit getFuel(fuel);
    }
}

void GameController::newPunch(_Direction dir)
{
    if(fuel - 5 >= 0){
        PunchItem * pun = NULL;
        qreal _x = hero->x();
        qreal _y = hero->y();
        switch (dir) {
        case Left:
             pun = new PunchItem(_x-Size/2,_y,dir,hero->_getAtk());
             break;
        case Right:
             pun = new PunchItem(_x+Size/2,_y,dir,hero->_getAtk());
             break;
        case Up:
             pun = new PunchItem(_x,_y-Size/2,dir,hero->_getAtk());
             break;
        case Down:
             pun = new PunchItem(_x,_y+Size/2,dir,hero->_getAtk());
             break;
        default:
            break;
            }
        scene.addItem(pun);
        connect(pun,SIGNAL(removePunch(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
        fuel -= 2;
        emit getFuel(fuel);
    }
}

void GameController::newHurt(qreal x,qreal y,_Direction dir,int _t)
{
    Hurt * hurt = NULL;

    hurt = new Hurt(x-Size/2,y,dir,_t);

    scene.addItem(hurt);
    connect(hurt,SIGNAL(removeHurt(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
}

void GameController::enemyKill(qreal x, qreal y , MyType _t)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int a = rand()%10;
    bool drop = false;
    if(a <= 2)
        drop = true;
    if(_t == Enemy_Type){
        hero->xpUp(10);
        if(drop){
            int b = rand()%7+1;
            stuffDrop(x,y,b);
        }
    }
    if(_t == Trap_Type){
        hero->xpUp(15);
        if(drop){
            int b = rand()%6+8;
            stuffDrop(x,y,b);
        }
    }
}

void GameController::tora_tora_tora()
{
    qDebug()<<"tora #################";
    if(fuel - 40 >= 0 && hero->_getLevel() >= 4){
        tora(hero->x(),hero->y(),hero->getMoveDirection(),hero->_getAtk());
        fuel -= 40;
        emit getFuel(fuel);
    }
}

void GameController::tora(qreal x, qreal y, _Direction dir, int a)
{
    Fire * he = new Fire(x,y,dir,a);
    scene.addItem(he);
    connect(he,SIGNAL(removeFire(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
    connect(he,SIGNAL(boom(qreal,qreal,_Direction,int)),this,SLOT(tora(qreal,qreal,_Direction,int)));
}

void GameController::stuffDrop(qreal x, qreal y,int a)
{
    StuffItem * item = new StuffItem(x,y,a);
    scene.addItem(item);
    connect(item,SIGNAL(getStuff(int)),this,SLOT(stuffPickUp(int)));
    connect(item,SIGNAL(removeStuff(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
}

void GameController::stuffPickUp(int a)
{
    emit getStuff(a);
}

void GameController::deleteItem(QGraphicsItem * item)
{
       if(item->data(G_O_Type) ==Enemy_Type){
            disconnect(dynamic_cast<Enemy *>(item),SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
            scene.removeItem(item);
            if(item != NULL){
            delete item;
            item =NULL;}
            return;
       }
        if(item->data(G_O_Type) == Fire_Type){
            disconnect(dynamic_cast<Fire *>(item),SIGNAL(boom(qreal,qreal,_Direction,int)),this,SLOT(tora(qreal,qreal,_Direction,int)));
            scene.removeItem(item);
            if(item != NULL){
            delete item;
            item =NULL;}
            return;
      }
        if(item->data(G_O_Type) == OMG_Type){
            disconnect(dynamic_cast<OMG *>(item),SIGNAL(boom(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
            scene.removeItem(item);
            if(item != NULL){
            delete item;
            item =NULL;}
            return;
        }
        if(item->data(G_O_Type) == Trap_Type){
            disconnect(dynamic_cast<Trap *>(item),SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
            scene.removeItem(item);
            if(item != NULL){
            delete item;
            item =NULL;}
            return;
        }
        scene.removeItem(item);
        if(item != NULL){
        delete item;
        item =NULL;}
        return;
}

void GameController::newOMG(qreal x1, qreal y1, _Direction dir, int _t)
{
    OMG * item = new OMG(x1,y1,dir,_t);
    scene.addItem(item);
    connect(item,SIGNAL(boom(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
    connect(item,SIGNAL(removeOMG(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem *)));
}

void GameController::settingMadDog(qreal x, qreal y, _Direction dir)
{
    Enemy_type_1 * dog = new Enemy_type_1(x,y);
    dog->hpLose(90);
    dog->setMoveDirection(dir);
    scene.addItem(dog);
    connect(dog,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
    connect(dog,SIGNAL(removeEnemy(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
}

void GameController::settingMadBird(qreal x, qreal y , _Direction dir)
{
    Enemy_type_3 * dog = new Enemy_type_3(x,y);
    dog->setHp(10);
    qDebug()<<"bird"<<endl;
    dog->setMoveDirection(dir);
    scene.addItem(dog);
    connect(dog,SIGNAL(hit(qreal,qreal,_Direction,int)),this,SLOT(newHurt(qreal,qreal,_Direction,int)));
    connect(dog,SIGNAL(removeEnemy(QGraphicsItem*)),this,SLOT(deleteItem(QGraphicsItem*)));
}

void GameController::virtory()
{
    JumpItem * a = new JumpItem(20,40,0);
    scene.addItem(a);
    connect(a,SIGNAL(getNextMap(int)),map,SLOT(mapJump(int)));

    hero->resetHpMax();
    hero->resetXpMax();
    fuel = 100;
}
