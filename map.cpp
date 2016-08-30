#include "map.h"
#include<QDebug>


Map::Map(QObject *parent) : QObject(parent),
    mapId(0)
{}

Map::~Map()
{}


void Map::mapJump(int next)
{   
    mapId = next;
    qDebug()<<"let's jump";
    emit changeMap();
    //顺序增加,初步设想
}

