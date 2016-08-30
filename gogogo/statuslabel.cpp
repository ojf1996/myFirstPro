#include "statuslabel.h"
#include<QString>

StatusLabel::StatusLabel(QWidget * parent):QLabel(parent),atk(10),level(1)
{
    this->setStyleSheet("border: 1px red; border-radius: 4px;"
                        "background-color: rgba(50, 50, 50, 100%); "
                        "color: rgb(192,192,192);");
    this->setAlignment(Qt::AlignTop);
    this->setText("当前等级: "+QString::number(level)+" 当前攻击力: "+QString::number(atk));
}

void StatusLabel::updateAtk(int a)
{
    atk =a;
    this->setText("当前等级: "+QString::number(level)+" 当前攻击力: "+QString::number(atk));
    update();
}

void StatusLabel::updateLevel(int a)
{
    level =a;
    this->setText("当前等级: "+QString::number(level)+" 当前攻击力: "+QString::number(atk));
    update();
}
