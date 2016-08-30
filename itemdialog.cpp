#include "itemdialog.h"
#include<QDebug>
#include<QLayout>

itemDialog::itemDialog(QWidget * parent)
    :QDialog(parent),herbWidget(new QWidget(this)),
    weaponWidget(new QWidget(this)),collectionWidget(new QWidget(this)),
     herbBtn(new myButton(this)),weaponBtn(new myButton(this)),collectionBtn(new myButton(this))
{
    this->resize(400,600);

    herbWidget->resize(400,500);
    weaponWidget->resize(400,500);
    collectionWidget->resize(400,500);

    herbWidget->move(this->geometry().x(),this->geometry().y()+50);
    weaponWidget->move(this->geometry().x() ,this->geometry().y()+50);
    collectionWidget->move(this->geometry().x(),this->geometry().y()+50);


    //设置按钮样式
    herbBtn->setButtonPic(QPixmap(":/tab/tab/herb_button.png"));
    herbBtn->setButtonClickPic(QPixmap(":/tab/tab/herb_button.png"));
    herbBtn->setButtonEnterPic(QPixmap(":/tab/tab/herb_button.png"));
    herbBtn->setText("药品");

    weaponBtn->setButtonPic(QPixmap(":/tab/tab/weapon_button.png"));
    weaponBtn->setButtonClickPic(QPixmap(":/tab/tab/weapon_button.png"));
    weaponBtn->setButtonEnterPic(QPixmap(":/tab/tab/weapon_button.png"));
    weaponBtn->setText("武器");

    collectionBtn->setButtonPic(QPixmap(":/tab/tab/collection_button.png"));
    collectionBtn->setButtonEnterPic(QPixmap(":/tab/tab/collection_button.png"));
    collectionBtn->setButtonClickPic(QPixmap(":/tab/tab/collection_button.png"));
    collectionBtn->setText("收藏");
    //********************************    小红药   *********************************//
    ItemLabel * herb_1 = new ItemLabel(this,1,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_heal_small.png","小号血瓶，居家必备良药，回复10HP");
    herb_1->setHeal();
    herb_1->_setScale(10);
    herb_1->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_1->setObjectName("item_1");
    herb_1->getOne();
    connect(herb_1,SIGNAL(heal(int)),this,SLOT(getHeal(int)));

    //*******************************   中红药 *******************************//
    ItemLabel * herb_2 = new ItemLabel(this,2,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_heal_middle.png","中号血瓶，居家必备良药，回复30HP");
    herb_2->setHeal();
    herb_2->_setScale(30);
    herb_2->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_2->setObjectName("item_2");
    connect(herb_2,SIGNAL(heal(int)),this,SLOT(getHeal(int)));

    //******************************** 大血瓶 **************************************//
    ItemLabel * herb_3 = new ItemLabel(this,3,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_heal_big.png","大号血瓶\n居家必备良药，回复50HP");
    herb_3->setHeal();
    herb_3->_setScale(50);
    herb_3->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_3->setObjectName("item_3");
    connect(herb_3,SIGNAL(heal(int)),this,SLOT(getHeal(int)));

    //******************************** 净化药水 *************************************//
    ItemLabel * herb_4 = new ItemLabel(this,4,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_purify.png","净化药水\n\"喝了它，我百毒不侵\”某人中毒而死之前");
    herb_4->setPurify();
    herb_4->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_4->setObjectName("item_4");
    connect(herb_4,SIGNAL(purify()),this,SLOT(getPurify()));

    //****************************** CD药水 *****************************************//
    ItemLabel * herb_5 = new ItemLabel(this,5,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_refresh.png","冷却药水，CD更新");
    herb_5->setRefresh();
    herb_5->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_5->setObjectName("item_5");
    connect(herb_5,SIGNAL(refresh()),this,SLOT(getRefresh()));

    //****************************** 小蓝瓶 *******************************************//
    ItemLabel * herb_6 = new ItemLabel(this,6,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_fuel_small.png","小号蓝瓶");
    herb_6->setFuel();
    herb_6->_setScale(30);
    herb_6->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_6->setObjectName("item_6");
    connect(herb_6,SIGNAL(fuel(int)),this,SLOT(getFuel(int)));

    //******************************** 大蓝瓶 ********************************************//
    ItemLabel * herb_7 = new ItemLabel(this,7,":/tab/tab/slot.png",
                                       ":/tab/tab/herb_fuel_big.png","大号蓝瓶");
    herb_7->setFuel();
    herb_7->_setScale(50);
    herb_7->setSoundTrack(":/sound/sound/herb_sound.wav");
    herb_7->setObjectName("item_7");
    connect(herb_7,SIGNAL(fuel(int)),this,SLOT(getFuel(int)));

    //************************* 药品栏布局******************************************//
    QHBoxLayout * a1 = new QHBoxLayout();
    a1->addStretch();
    a1->addWidget(herb_1);
    a1->addStretch();
    a1->addWidget(herb_2);
    a1->addStretch();
    a1->addWidget(herb_3);
    a1->addStretch();

    QHBoxLayout * a2 = new QHBoxLayout();
    a2->addStretch();
    a2->addWidget(herb_4);
    a2->addStretch();
    a2->addWidget(herb_5);
    a2->addStretch();

    QHBoxLayout * a3 = new QHBoxLayout();
    a3->addStretch();
    a3->addWidget(herb_6);
    a3->addStretch();
    a3->addWidget(herb_7);
    a3->addStretch();

    QVBoxLayout * a4 = new QVBoxLayout();
    a4->addStretch();
    a4->addLayout(a1);
    a4->addStretch();
    a4->addLayout(a2);
    a4->addStretch();
    a4->addLayout(a3);
    a4->addStretch();

    herbWidget->setLayout(a4);

    //******************************* 武器一 *******************************//
    ItemLabel * weapon_1 = new ItemLabel(this,8,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_6.png","大刀\n\"做大事，不是大成就是大败.\"\n大刀王五");
    weapon_1->setConsume(false);
    weapon_1->setAtkUp();
    weapon_1->_setScale(10);
    weapon_1->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_1->setObjectName("item_8");
    connect(weapon_1,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //****************************** 武器二 ********************************//
    ItemLabel * weapon_2 = new ItemLabel(this,9,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_3.png","镰刀\n\"You may get a second chanceat life.But you can’t cheat death.\"《死神来了》");
    weapon_2->setConsume(false);
    weapon_2->setAtkUp();
    weapon_2->_setScale(15);
    weapon_2->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_2->setObjectName("item_9");
    connect(weapon_2,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //****************************** 武器三 ********************************************//
    ItemLabel * weapon_3 = new ItemLabel(this,10,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_4.png","圣物之盾\n\"邪恶永无歇止，我等亦当如是.\"圣骑士");
    weapon_3->setConsume(false);
    weapon_3->setAtkUp();
    weapon_3->_setScale(20);
    weapon_3->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_3->setObjectName("item_10");
    connect(weapon_3,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //****************************** 武器四 ***********************************************//
    ItemLabel * weapon_4 = new ItemLabel(this,11,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_1.png","幽儿希卡枪\n结合枪和槌的武器，刺，捶结合");
    weapon_4->setConsume(false);
    weapon_4->setAtkUp();
    weapon_4->_setScale(30);
    weapon_4->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_4->setObjectName("item_11");
    connect(weapon_4,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //******************************  武器五  ****************************//
    ItemLabel * weapon_5 = new ItemLabel(this,12,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_5.png","暗月光剑\n复仇的故事无人记起，但，仅有剑明了复仇的涵义即可.");
    weapon_5->setConsume(false);
    weapon_5->setAtkUp();
    weapon_5->_setScale(40);
    weapon_5->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_5->setObjectName("item_12");
    connect(weapon_5,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //******************************** 武器六 *****************************************//
    ItemLabel * weapon_6 = new ItemLabel(this,13,":/tab/tab/slot.png",
                                       ":/tab/tab/weapon_2.png","灵魂光剑\n吾愿以吾之灵魂，还世界一个光明.jianfeng Ou.");
    weapon_6->setConsume(false);
    weapon_6->setAtkUp();
    weapon_6->_setScale(50);
    weapon_6->setSoundTrack(":/sound/sound/repair_sound.wav");
    weapon_6->setObjectName("item_13");
    connect(weapon_6,SIGNAL(atkUp(int)),this,SLOT(getAtkUp(int)));

    //***************************   武器布局  ******************************//
    QVBoxLayout * b1 = new QVBoxLayout(this);

    QHBoxLayout * b2 = new QHBoxLayout(this);
    b2->addStretch();
    b2->addWidget(weapon_1);
    b2->addStretch();
    b2->addWidget(weapon_2);
    b2->addStretch();
    b2->addWidget(weapon_3);
    b2->addStretch();

    QHBoxLayout * b3 = new QHBoxLayout(this);
    b3->addStretch();
    b3->addWidget(weapon_4);
    b3->addStretch();
    b3->addWidget(weapon_5);
    b3->addStretch();
    b3->addWidget(weapon_6);
    b3->addStretch();

    b1->addStretch();
    b1->addLayout(b2);
    b1->addStretch();
    b1->addLayout(b3);
    b1->addStretch();

    weaponWidget->setLayout(b1);

    //******************************** 收藏品一 *********************************//
    ItemLabel * collection_1 = new ItemLabel(this,14,":/tab/tab/slot.png",
                                       ":/tab/tab/collection_1.png","黄金戒指\n黄金，黄金");
    collection_1->setConsume(false);
    collection_1->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_1->setObjectName("item_14");
    //***************************** 收藏二 *****************************************//
    ItemLabel * collection_2 = new ItemLabel(this,15,":/tab/tab/slot.png",
                                       ":/tab/tab/collection_2.png","光明\n黑夜给了我黑色的眼睛，我却用它寻找光明");
    collection_2->setConsume(false);
    collection_2->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_2->setObjectName("item_15");
    //***************************** 收藏三 *****************************************//
    ItemLabel * collection_3 = new ItemLabel(this,16,":/tab/tab/slot.png",
                                       ":/tab/tab/collection_3.png","黄蜂戒指\n\"黄蜂尾后针，最...老婆别揪我耳朵\"");
    collection_3->setConsume(false);
    collection_3->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_3->setObjectName("item_16");
    //***************************** 收藏四 *****************************************//
   ItemLabel * collection_4 = new ItemLabel(this,17,":/tab/tab/slot.png",
                                           ":/tab/tab/collection_4.png","钥匙\n\"你想知道门后面的世界吗？\"");
   collection_4->setConsume(false);
   collection_4->setSoundTrack(":/sound/sound/dimond_sound.wav");
   collection_4->setObjectName("item_17");
   //***************************** 收藏五 *****************************************//
    ItemLabel * collection_5 = new ItemLabel(this,18,":/tab/tab/slot.png",
                                               ":/tab/tab/collection_5.png","黑暗刀刃\n母亲交给女儿自保(亦可自我了结)的刀刃，也只被用过一次");
    collection_5->setConsume(false);
    collection_5->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_5->setObjectName("item_18");
    //***************************** 收藏六 *****************************************//
    ItemLabel * collection_6 = new ItemLabel(this,19,":/tab/tab/slot.png",
                                           ":/tab/tab/collection_6.png","混沌温床\n\"生活不止眼前的苟且.\"");
    collection_6->setConsume(false);
    collection_6->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_6->setObjectName("item_19");
    //***************************** 收藏七 *****************************************//
    ItemLabel * collection_7 = new ItemLabel(this,20,":/tab/tab/slot.png",
                                           ":/tab/tab/collection_7.png","奇迹\n\"生活就像一盒巧克力.\"");
    collection_7->setConsume(false);
    collection_7->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_7->setObjectName("item_20");
    //***************************** 收藏八 *****************************************//
    ItemLabel * collection_8 = new ItemLabel(this,21,":/tab/tab/slot.png",
                                           ":/tab/tab/collection_8.png","书\n\"书读百遍，其义自现.\"");
    collection_8->setConsume(false);
    collection_8->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_8->setObjectName("item_21");
    //***************************** 收藏九 *****************************************//
    ItemLabel * collection_9 = new ItemLabel(this,22,":/tab/tab/slot.png",
                                               ":/tab/tab/collection_9.png","the lord of rings");
    collection_9->setConsume(false);
    collection_9->setSoundTrack(":/sound/sound/dimond_sound.wav");
    collection_9->setObjectName("item_22");
    //******************************** 收藏品布局 *****************************************//
    QVBoxLayout * c1 = new QVBoxLayout(this);

    QHBoxLayout * c2 = new QHBoxLayout(this);
    c2->addStretch();
    c2->addWidget(collection_1);
    c2->addStretch();
    c2->addWidget(collection_2);
    c2->addStretch();
    c2->addWidget(collection_3);
    c2->addStretch();

    QHBoxLayout * c3 = new QHBoxLayout(this);
    c3->addStretch();
    c3->addWidget(collection_4);
    c3->addStretch();
    c3->addWidget(collection_5);
    c3->addStretch();
    c3->addWidget(collection_6);
    c3->addStretch();

    QHBoxLayout * c4 = new QHBoxLayout(this);
    c4->addStretch();
    c4->addWidget(collection_7);
    c4->addStretch();
    c4->addWidget(collection_8);
    c4->addStretch();
    c4->addWidget(collection_9);
    c4->addStretch();

    c1->addStretch();
    c1->addLayout(c2);
    c1->addStretch();
    c1->addLayout(c3);
    c1->addStretch();
    c1->addLayout(c4);

    collectionWidget->setLayout(c1);

    //********************************* 关联信号与槽 ***************************************//
    connect(herbBtn,SIGNAL(clicked(bool)),this,SLOT(changPage1()));
    connect(weaponBtn,SIGNAL(clicked(bool)),this,SLOT(changPage2()));
    connect(collectionBtn,SIGNAL(clicked(bool)),this,SLOT(changPage3()));

    herbBtn->move(geometry().x()+10,geometry().y()+40);
    weaponBtn->move(this->geometry().x() + 140,this->geometry().y() + 40);
    collectionBtn->move(this->geometry().x() + 270, this->geometry().y() + 40);


    herbWidget->move(this->geometry().x(),this->geometry().y()+50);
    weaponWidget->move(this->geometry().x(),this->geometry().y()+50);
    collectionWidget->move(this->geometry().x(),this->geometry().y()+50);

    herbWidget->show();
    weaponWidget->hide();
    collectionWidget->hide();

    setStyleSheet("background-color: rgba(50,50,50,40%);"
                  "border: 1px black; border-radius: 5px;");

}

void itemDialog::changPage1()
{
    weaponWidget->hide();
    collectionWidget->hide();
    herbWidget->show();
}

void itemDialog::changPage2()
{
    herbWidget->hide();
    collectionWidget->hide();
    weaponWidget->show();
}

void itemDialog::changPage3()
{
    weaponWidget->hide();
    herbWidget->hide();
    collectionWidget->show();
}

void itemDialog::getOne(int a)
{
    QList<QLabel *>  list= this->findChildren<QLabel * >("item_"+QString::number(a));
    if(list.count()<=0)
        return;
    dynamic_cast<ItemLabel *>(list.at(0))->getOne();
}

void itemDialog::resetItem()
{
    for(int i = 1; i < 23; ++i){
        QList<QLabel *>  list= this->findChildren<QLabel * >("item_"+QString::number(i));
        if(list.count() > 0){
            dynamic_cast<ItemLabel *>(list.at(0))->changNum(0);
            if(i > 7 && i < 14){
                dynamic_cast<ItemLabel *>(list.at(0))->setAtkUp();
            }
            update();
        }
        else
            qDebug()<<"********************* failed ************************";
    }
}
