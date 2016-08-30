#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
class myButton;

class startMenu : public QWidget
{
    Q_OBJECT
public:
    explicit startMenu(QWidget *parent = 0);
signals:
   void gameStart();
   void finish();
   void resume();
public slots:
   void start();
   void restart();
   void over();
private:
    myButton * startBtn;
    myButton * resumeBtn;
    myButton * overBtn;
};

#endif // STARTMENU_H
