#ifndef STATUSLABEL_H
#define STATUSLABEL_H

#include<QLabel>

class StatusLabel : public QLabel
{
    Q_OBJECT
public:
    StatusLabel(QWidget * parent = NULL);
public slots:
    void updateAtk(int);
    void updateLevel(int);
    void resetLabel(){
        level = 1;
        atk = 10;
        update();
    }
private:
    int atk;
    int level;
};

#endif // STATUSLABEL_H
