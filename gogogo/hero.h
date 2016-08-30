#ifndef HERO_H
#define HERO_H

#include <QGraphicsItem>
#include<QSound>
#include <QRectF>
#include<QString>
#include<QDebug>
#include<QTimer>
#include"constants.h"

class Hero :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Hero();
    //***************************绘图及行走**************************************//
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void setMoveDirection(_Direction direction);
    _Direction getMoveDirection()const;
    QPainterPath shape();
    void noPunch();
    void punch();   

    void stopMoveing();

    void move();
    void flash();

    bool isMessUp(){return isMess;}
    bool isStuckUp(){return isStuck;}

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    int _getAtk(){
        return atk;
    }
    int _getLevel(){
        return level;
    }
public slots:
    //******************************* 人物属性部分 ***************************************//
    void hpLose(){
//        QSound::play(":/sound/sound/howl_sound.wav");
        picName = ":/source/image/hit.png";
        update();
        hp-=30;emit getHp(hp);
        emit getHpMax(hpMax);
                 }
    //************* 秒杀 **************
    void Killing(){
        hp = 0;emit getHp(hp);
        emit getHpMax(hpMax);
                  }
    //************** 复活 ********************
    void backToLife(){
        hp = hpMax;
        emit getHp(hp);
        emit getHpMax(hpMax);
                     }
    //***************** 升级 ***************
    void levelUp(){
        level++;
        currentExp = 0;
        xp *= 1.2;
        hpMax += level * 30;
        atk +=  5;
        hp = hpMax;
        purify();

        emit getHp(hp);
        emit getHpMax(hpMax);
        emit getCXp(currentExp);
        emit getExpMax(xp);
        emit getAtk(atk);
        emit getLevel(level);
    }

    void xpUp(int a){
        if(currentExp + a > xp){
            levelUp();
            emit getCXp(currentExp);
            emit getExpMax(xp);
            return;
        }
        currentExp += a;
        emit getCXp(currentExp);
        emit getExpMax(xp);
    }

    //*************** 治疗 ************************
    void heal(int a){
        if(hp + a > hpMax)
            hp = hpMax;
        else
            hp+=a;
        qDebug()<<"accept";
        emit getHp(hp);
        emit getHpMax(hpMax);

        }
    //********************* 净化 *****************
    void purify(){
        isStuck = false;
        isPoisoned = false;
        isMess = false;
        time.stop();
    }
    //************************ 攻击力上升 ****************
    void atkUp(int a){
        if(a>=0)
            atk+=a;
        emit getAtk(atk);
    }
    //************************ 生命上限 **********************
    void hpMaxUp(int a){
        if(a>=0)
            hpMax+=a;
        emit getHpMax(hpMax);
    }
    //********************* 中毒 ******************************
    void poisoned(){
        isPoisoned = true;
        emit isUnusal(level * 500 + 5000);
    }
    //************************** 眩晕 **************************
    void stuck(){
        isStuck = true;
        emit isUnusal(level * 500 + 2000);
    }
    //*************************** 混乱 ****************************
    void mess(){
        isMess = true;
        emit isUnusal(level * 500 + 2000);
    }

    void resetHpMax(){
        hp =100;
        hpMax = 100;
        atk =10;
        emit getAtk(atk);
        emit getHp(hp);
        emit getHpMax(hpMax);
    }

    void resetXpMax(){
        level = 1;
        currentExp = 0;
        xp = 100;
        emit getLevel(level);
        emit getCXp(currentExp);
        emit getExpMax(xp);
    }

signals:
    void IamDead();
    void isUnusal(int);
    void getHp(int);
    void getHpMax(int);
    void getCXp(int);
    void getExpMax(int);
    void getAtk(int);
    void getLevel(int);
protected:    
    void advance(int step);

private:
    //************************ 绘图部分和动作部分 **************************************//
    void handleCollisions();
    void changePicture();
    QString picName;//动画图片路径
    int count;//用于动画
    int speed;//调整刷新频率
    bool _punch;//出拳
    bool moving;//动
    _Direction  moveDirection;//前进方向

    //***************************** 人物属性部分 ****************************************//
    int level;//等级
    int currentExp;//经验值
    int xp;//经验
    int hp;//血量
    int hpMax;//hp上线
    int atk;//攻击力
    bool isPoisoned;//中毒
    bool isStuck;//眩晕
    bool isMess;//混乱
    QTimer time;
};

#endif // HERO_H
