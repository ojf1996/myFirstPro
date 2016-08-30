#include "mybutton.h"
#include<QMouseEvent>

myButton::myButton(QWidget * parent)
    :QPushButton(parent),
      buttonPic(new QPixmap()),
      buttonClickPic(new QPixmap()),
      buttonEnterPic(new QPixmap())
{
    this->resize(90,40);
    if(!buttonPic)
        this->setButtonPic(*buttonPic);
    this->setIconSize(QSize(90,40));
    this -> setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);

    this->setStyleSheet("QPushButton{"
                        "background-image:url(:/source/image/buttonBackGround.png);"//设置按钮背景图片
                        "background-repeat:repeat-xy;" //设置按钮的背景图片的重复规则，x方向y方向，xy方向
                        "background-position:Center;" //设定背景图片在按钮中的位置,按左对齐Left，右Right，中间Center，上Top，底部Bottom
                        "background-attachment:fixed;"
                        "background-clip:padding;"
                        "border:2px solid black;"  //宽度为3px的红色边框
                        "border-radius:5px}"); //边框角的弧度为8px
}

void myButton::enterEvent(QEvent * a)
{
    this->resize(120,56);
    this->setIcon(QIcon(*buttonEnterPic));
    this->setIconSize(QSize(56,56));
}

void myButton::leaveEvent(QEvent * a)
{
    this->resize(120,40);
    this->setIcon(QIcon(*buttonPic));
    this->setIconSize(QSize(40,40));
}

void myButton::mousePressEvent(QMouseEvent * a)
{
    this->setIcon(QIcon(*buttonClickPic));
}

void myButton::mouseReleaseEvent(QMouseEvent * a)
{
    if(a->button()==Qt::LeftButton)
         emit click();
}
