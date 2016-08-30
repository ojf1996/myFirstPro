#include "startmenu.h"
#include"mybutton.h"
#include<QLayout>

startMenu::startMenu(QWidget *parent) : QWidget(parent),
    startBtn(new myButton(this)),resumeBtn(new myButton(this)),overBtn(new myButton(this))
{
    this->resize(200,300);

    startBtn->setButtonPic(QPixmap(":/source/image/button.png"));
    startBtn->setButtonClickPic(QPixmap(":/source/image/button_click.png"));
    startBtn->setButtonEnterPic(QPixmap(":/source/image/button_enter.png"));
    startBtn->setText("来吧，我迫不及待了");

    resumeBtn->setButtonPic(QPixmap(":/source/image/button.png"));
    resumeBtn->setButtonClickPic(QPixmap(":/source/image/button_click.png"));
    resumeBtn->setButtonEnterPic(QPixmap(":/source/image/button_enter.png"));
    resumeBtn->setText("我还能再战300回合");

    overBtn->setButtonPic(QPixmap(":/source/image/button.png"));
    overBtn->setButtonClickPic(QPixmap(":/source/image/button_click.png"));
    overBtn->setButtonEnterPic(QPixmap(":/source/image/button_enter.png"));
    overBtn->setText("再见我的盆友");

    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(hide()));

    connect(resumeBtn,SIGNAL(clicked(bool)),this,SLOT(restart()));
    connect(resumeBtn,SIGNAL(clicked(bool)),this,SLOT(hide()));

    connect(overBtn,SIGNAL(clicked(bool)),this,SLOT(over()));

    QVBoxLayout * layout = new QVBoxLayout(this);

    layout->addStretch();
    layout->addWidget(startBtn);
    layout->addStretch();
    layout->addWidget(resumeBtn);
    layout->addStretch();
    layout->addWidget(overBtn);
    layout->addStretch();
    this->setLayout(layout);
}

void startMenu::start()
{
    emit gameStart();
}

void startMenu::restart()
{
    emit resume();
}

void startMenu::over()
{
    emit finish();
}
