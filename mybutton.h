#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QPushButton>

class myButton : public QPushButton
{
    Q_OBJECT
public:
    myButton(QWidget * parent = NULL);
    void setButtonPic(QPixmap a){*buttonPic = a;this->setIcon(*buttonPic);}
    void setButtonClickPic(QPixmap a){*buttonClickPic = a;}
    void setButtonEnterPic(QPixmap a){*buttonEnterPic = a;}
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QPixmap * buttonPic;
    QPixmap * buttonClickPic;
    QPixmap * buttonEnterPic;
};

#endif // MYBUTTON_H
