#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>

class QGraphicsScene;
class QGraphicsView;
class GameController;
class startMenu;
class goOnDialog;
class itemDialog;
class QProgressBar;
class StatusLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void leaving();
    void initScene();
    void begin();
    void fightBack();
    void finish();
    void _tab();
private:
    void initSceneBackground();
    QGraphicsScene *scene;
    QGraphicsView *view;
    GameController *game;

    startMenu * sMenu;
    goOnDialog * dialog;
    itemDialog * _dialog;

    QWidget * statusBar;
    QProgressBar * hpVolume;
    QProgressBar * xpVolume;
    QProgressBar * fuelVolume;
    StatusLabel * statusLabel;

    QSound * sound;

};

#endif // MAINWINDOW_H
