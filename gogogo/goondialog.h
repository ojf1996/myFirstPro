#ifndef GOONDIALOG_H
#define GOONDIALOG_H

#include<QDialog>
class myButton;

class goOnDialog :public QDialog
{
    Q_OBJECT

public:
    goOnDialog(QWidget * parent =NULL);
signals:
    void goOn();
public slots:
    void nth();
    void sth();
private:
    myButton * yesButton;
    myButton * noButton;
};

#endif // GOONDIALOG_H
