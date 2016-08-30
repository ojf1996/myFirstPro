#ifndef MAP_H
#define MAP_H

#include"constants.h"
#include <QObject>



class Map : public QObject
{
    Q_OBJECT
public:   
    Map(QObject *parent = 0);
    ~Map();
    int mapId;
signals:
    void changeMap();
public slots:
    void mapJump(int);

};

#endif // MAP_H
