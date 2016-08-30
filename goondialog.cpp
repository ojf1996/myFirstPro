#include "goondialog.h"
#include"mybutton.h"
#include<QLayout>
#include<QDebug>

goOnDialog::goOnDialog(QWidget * parent)
    :QDialog(parent),yesButton(new myButton(this)),noButton(new myButton(this))
{
    yesButton->setButtonPic(QPixmap(":/source/image/button.png"));
    yesButton->setButtonClickPic(QPixmap(":/source/image/button_click.png"));
    yesButton->setButtonEnterPic(QPixmap(":/source/image/button_enter.png"));
    yesButton->setText("是的，我要继续");

    noButton->setButtonPic(QPixmap(":/source/image/button.png"));
    noButton->setButtonClickPic(QPixmap(":/source/image/button_click.png"));
    noButton->setButtonEnterPic(QPixmap(":/source/image/button_enter.png"));
    noButton->setText("不，我只是手滑了");

    this->setCursor(Qt::PointingHandCursor);

    QHBoxLayout * a = new QHBoxLayout(this);

    a->addStretch();
    a->addWidget(yesButton);
    a->addStretch();
    a->addWidget(noButton);
    a->addStretch();
    this->setFixedSize(QSize(350,80));
    this->setWindowTitle("且慢");
    this->setLayout(a);

    this->setStyleSheet("background-color: rgba(50,50,50,80%);"
                        "border: 1px groove gray;border-radius: 10px; ");
    connect(yesButton,SIGNAL(clicked(bool)),this,SLOT(sth()));
    connect(noButton,SIGNAL(clicked(bool)),this,SLOT(nth()));
}

void goOnDialog::nth()
{
    qDebug()<<"click";
    close();
}

void goOnDialog::sth()
{
    qDebug()<<"click";
    emit goOn();
    close();
}




