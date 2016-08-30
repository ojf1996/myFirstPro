#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include<QLabel>
#include<QString>
#include<QSound>

class ItemLabel : public QLabel
{
    Q_OBJECT

public:
    ItemLabel(QWidget * parent = NULL,int = 0,QString = "",QString = "",QString = "");
    ~ItemLabel(){delete descriptionLabel;sound->stop();delete sound;}
    void setPicName(QString a){*pic = QPixmap(a);}
    void setPressPicName(QString a){*pressPic = QPixmap(a);}
    void setDescription(QString a){description = a;}
    void setHeal(){canHeal = true;}
    void setFuel(){canFuel = true;}
    void setRefresh(){canRefresh = true;}
    void setPurify(){canPurify = true;}
    void setHpMaxUp(){canHpMaxUp = true;}
    void setFuelMaxUp(){canFuealMaxUp = true;}
    void setAtkUp(){canAtkUp = true;}
    void changNum(int a){if(a>=0){num = a;}}
    int getNum(){return num;}
    void _setScale(int a){if(a>0 && a< 100){_scale = a;}}
    void setSoundTrack(QString a){soundTrack = a;sound = new QSound(a,this);}
    void setConsume(bool a){isConsumption = a;}
    const int ID;//编号

signals:
    void heal(int);
    void fuel(int);
    void refresh();
    void purify();
    void hpMaxUp(int);
    void fuelMaxUp(int);
    void atkUp(int);

public slots:
    void beUsed();
    void getOne();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    bool canHeal;//能否回血
    bool canFuel;//能否回蓝
    bool canRefresh;//刷新技能CD
    bool canPurify;//净化异常状态
    bool canHpMaxUp;//上升血量
    bool canFuealMaxUp;//上升蓝槽
    bool canAtkUp;
    bool isConsumption;//是否消耗品
    int num;//数量
    QPixmap * pic;
    QPixmap * pressPic;
    QString description;//物品描述
    int _scale;//回蓝/血幅度
    QLabel * descriptionLabel;
    QString soundTrack;
    QSound * sound;

};

#endif // ITEMLABEL_H
