#include "itemlabel.h"
#include<QDebug>
#include<QMouseEvent>
#include<QPainter>

ItemLabel::ItemLabel(QWidget * parent ,int id,QString a,QString b,QString c)
    :QLabel(parent),ID(id),canHeal(false),canFuel(false),canRefresh(false),canPurify(false),
      isConsumption(true),num(0),pic(new QPixmap()),pressPic(new QPixmap()),_scale(0),descriptionLabel(this),soundTrack("")
{
    setPicName(a);
    setPressPicName(b);
    setDescription(c);
    this->setStyleSheet("border: 1px groove gray; border-radius: 5px;"
                        "background-color: rgba(50, 50, 50, 100%); "
                        "color: rgb(138,43,226);");

    descriptionLabel = new QLabel(NULL,Qt::FramelessWindowHint);
    descriptionLabel->setStyleSheet("border: 1px groove gray; border-radius: 5px;"
                                    "background-color: rgba(68, 69, 69, 100%); "
                                    "color: rgb(192,192,192);");

    descriptionLabel->setFixedSize(100,100);
    descriptionLabel->setAlignment(Qt::AlignTop);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setText(description);
    this->setFixedSize(60,60);
}

void ItemLabel::beUsed()
{
    if(num>=1){

    if(canHeal)
        emit heal(_scale);
    if(canFuel)
        emit fuel(_scale);
    if(canRefresh)
        emit refresh();
    if(canPurify)
        emit purify();
    if(canHpMaxUp){
        emit hpMaxUp(_scale);
        if(!isConsumption)
            canHpMaxUp = false;
    }
    if(canFuealMaxUp){
        emit fuelMaxUp(_scale);
        if(!isConsumption)
            canFuealMaxUp = false;
    }
    if(canAtkUp){
        emit atkUp(_scale);
        if(!isConsumption)
            canAtkUp = false;
    }


    if(isConsumption)
       num-=1;
       update();
    }
}

void ItemLabel::getOne()
{
    num+=1;
    update();
}

void ItemLabel::paintEvent(QPaintEvent * a)
{
    QPainter painter(this);

    if(num == 0)
    {
        painter.drawPixmap(10,1,40,41,*pic,0,0,40,40);
    }
    else
    {
        painter.drawPixmap(10,1,40,41,*pressPic,0,0,40,40);
        painter.drawText(QRectF(10,42,60,60),Qt::AlignTop,("数量: "+QString::number(getNum())));
    }
    a->accept();
}

void ItemLabel::mousePressEvent(QMouseEvent *a)
{
    if(getNum()> 0)
        if(!(soundTrack.isEmpty())){
            sound->play();
        }
    a->accept();
}

void ItemLabel::mouseReleaseEvent(QMouseEvent * a)
{
      beUsed();
      a->accept();
}

void ItemLabel::enterEvent(QEvent *event)
{
    if(getNum()>0){
     descriptionLabel->move(this->mapToGlobal(QPoint(0,0)).x()+60,this->mapToGlobal(QPoint(0,0)).y() - 10);
     descriptionLabel->show();
    }
    event->accept();
}

void ItemLabel::leaveEvent(QEvent *event)
{
    descriptionLabel->hide();
    event->accept();
}


