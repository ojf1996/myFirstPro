#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include<QDialog>
#include<QDebug>
#include"itemlabel.h"
#include"mybutton.h"

class itemDialog : public QDialog
{
    Q_OBJECT
public:
     itemDialog(QWidget * parent = NULL);
public slots:
     void getHeal(int a){emit heal(a);qDebug()<<"******* heal ********";}
     void getFuel(int a){emit fuel(a);}
     void getRefresh(){emit refresh();}
     void getPurify(){emit purify();}
     void getHpMaxUp(int a){emit hpMaxUp(a);}
     void getFuelUp(int a){emit fuelMaxUp(a);}
     void getAtkUp(int a){emit atkUp(a);}
     void getOne(int);
     void changPage1();
     void changPage2();
     void changPage3();
     void resetItem();
signals:
     void heal(int);
     void fuel(int);
     void purify();
     void refresh();
     void hpMaxUp(int);
     void fuelMaxUp(int);
     void atkUp(int);

private:
     QWidget * herbWidget;
     QWidget * weaponWidget;
     QWidget * collectionWidget;

     myButton * herbBtn;
     myButton * weaponBtn;
     myButton * collectionBtn;
};

#endif // ITEMDIALOG_H
