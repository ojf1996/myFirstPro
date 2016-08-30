#include <QGraphicsView>
#include <QTimer>
#include<QProgressBar>
#include<QLayout>
#include<QDebug>
#include"startmenu.h"
#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"
#include"map.h"
#include"goondialog.h"
#include"itemdialog.h"
#include"hero.h"
#include"statuslabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this)),
      sMenu(new startMenu(this)),
      dialog(new goOnDialog(this)),
      _dialog(new itemDialog(this)),    
      statusBar(new QWidget(this)),
      hpVolume(new QProgressBar(statusBar)),
      xpVolume(new QProgressBar(statusBar)),
      fuelVolume(new QProgressBar(statusBar)),
      statusLabel(new StatusLabel(statusBar)),
      sound(new QSound(":/sound/sound/bgm_start.wav",this))
{
    //*******************  设置样式 *****************************//
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    this->setFixedSize(WindowWidth,WindowLength);
    //********************** 设置背景图片 *************************//
    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow{border-image:url(:/source/image/mainwindowBg.png);}");
    //状态栏
    //*********************** 设置血量及经验槽，蓝槽（未知是否实现）样式 ********************//
    hpVolume->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
                               "QProgressBar::chunk{background-color: #CD2626;width: 10px;}");
    hpVolume->setGeometry(100, 100, 150, 30);
    hpVolume->setValue(100);
    hpVolume->setMaximum(100);

    xpVolume->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
                               "QProgressBar::chunk{background-color: rgb(192,192,192);width: 10px;}");
    xpVolume->setGeometry(100, 100, 200, 30);
    xpVolume->setValue(0);
    xpVolume->setMaximum(100);

    fuelVolume->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 5px;text-align: center;}"
                               "QProgressBar::chunk{background-color: #0000ff;width: 10px;}"
                              "font-color:black;");
    fuelVolume->setGeometry(100, 100, 150, 30);
    fuelVolume->setValue(100);
    fuelVolume->setMaximum(100);

    hpVolume->hide();
    xpVolume->hide();
    fuelVolume->hide();

    QHBoxLayout * a1 = new QHBoxLayout(statusBar);
    a1->addWidget(hpVolume);
    a1->addStretch();
    a1->addWidget(xpVolume);
    a1->addStretch();
    a1->addWidget(fuelVolume);
    a1->addStretch();
    a1->addWidget(statusLabel);
    a1->addStretch();

    statusBar->setLayout(a1);
    statusBar->move(0,0);
    statusBar->setFixedSize(WindowWidth,40);

    statusBar->setStyleSheet("border: 1px groove gray; border-radius: 5px;"
                             "background-color: rgba(50, 50, 50, 100%); "
                             "color: rgb(138,43,226);");

    //****************************** 关联槽与信号 ******************************//
    connect(sMenu,SIGNAL(gameStart()),this,SLOT(initScene()));//开始游戏
    connect(sMenu,SIGNAL(resume()),this,SLOT(fightBack()));//继续游戏
    connect(sMenu,SIGNAL(finish()),this,SLOT(finish()));//结束游戏
    connect(dialog,SIGNAL(goOn()),this,SLOT(close()));//关联消息窗口
    connect(game,SIGNAL(bye()),this,SLOT(leaving()));//暂停
    connect(game,SIGNAL(tab()),this,SLOT(_tab()));//物品栏
    //************************ 关联控制器与物品窗口 ********************************//
    connect(_dialog,SIGNAL(heal(int)),game->getHero(),SLOT(heal(int)));
    connect(_dialog,SIGNAL(purify()),game->getHero(),SLOT(purify()));
    connect(_dialog,SIGNAL(atkUp(int)),game->getHero(),SLOT(atkUp(int)));
    connect(_dialog,SIGNAL(hpMaxUp(int)),game->getHero(),SLOT(hpMaxUp(int)));
    connect(game,SIGNAL(getStuff(int)),_dialog,SLOT(getOne(int)));
    connect(_dialog,SIGNAL(fuel(int)),game,SLOT(fuelUp(int)));
    //********************** 关联任务与状态显示 ************************************//
    connect(game->getHero(),SIGNAL(getHp(int)),hpVolume,SLOT(setValue(int)));
    connect(game->getHero(),SIGNAL(getHpMax(int)),hpVolume,SLOT(setMaximum(int)));
    connect(game->getHero(),SIGNAL(getCXp(int)),xpVolume,SLOT(setValue(int)));
    connect(game->getHero(),SIGNAL(getExpMax(int)),xpVolume,SLOT(setMaximum(int)));
    connect(game->getHero(),SIGNAL(getAtk(int)),statusLabel,SLOT(updateAtk(int)));
    connect(game->getHero(),SIGNAL(getLevel(int)),statusLabel,SLOT(updateLevel(int)));
    connect(game,SIGNAL(getFuel(int)),fuelVolume,SLOT(setValue(int)));

    begin();
}

MainWindow::~MainWindow()
{
    delete game;
    delete scene;
    delete view;
}

void MainWindow::initScene()
{
    sound->stop();
    game->resume();
    game->restart();
    statusBar->show();
    hpVolume->show();
    xpVolume->show();
    fuelVolume->show();
    statusLabel->show();
    _dialog->resetItem();
    view->move(0,40);
    scene->setSceneRect(-SceneWidth/2, -SceneLength/2, SceneWidth, SceneLength);
    initSceneBackground();
    view->setFixedSize(SceneWidth+10,SceneLength+10);
    this->adjustSize();
    view->show();
}

void MainWindow::fightBack()
{
    sound->stop();
    statusBar->show();
    hpVolume->show();
    xpVolume->show();\
    fuelVolume->show();
    statusLabel->show();
    view->move(0,40);
    initSceneBackground();
    view->setFixedSize(SceneWidth+10,SceneLength+10);
    game->resume();
    view->show();
}

void MainWindow::initSceneBackground()
{
    QPixmap background(":/source/image/path.png");

    view->setBackgroundBrush(background);
}

void MainWindow::leaving()
{
    sound->play();
    statusBar->hide();
    _dialog->hide();
    game->pause();
    view->hide();
    sMenu->show();
}



void MainWindow::begin()
{
    sound->play();
    statusBar->hide();
    view->hide();
    game->pause();
    sMenu->show();
}

void MainWindow::finish()
{
   dialog->show();
}

void MainWindow::_tab()
{
    _dialog->show();
}
