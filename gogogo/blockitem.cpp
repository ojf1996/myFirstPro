#include <QPainter>
#include "blockitem.h"

BlockItem::BlockItem(qreal x,qreal y,Dimao face)
{
    setPos(x,y);
    setData(G_O_Type,Block_Type);
    switch (face) {
        case Rock:
        picName = ":/source/image/rock.png";
        break;
        case Tree:
            picName = ":/source/image/tree.png";
            break;
        case Water_Center:
            picName = ":/source/image/water_center.png";
            break;
        case Water_Left:
            picName = ":/source/image/water_left.png";
            break;
        case Water_Right:
            picName = ":/source/image/water_right.png";
            break;
        case Water_Up:
            picName = ":/source/image/water_up.png";
            break;
        case Water_Down:
            picName = ":/source/image/water_down.png";
            break;
        default:
            picName = ":/source/image/unknown.png";
            break;
    }
}

QRectF BlockItem::boundingRect()const
{
    return QRectF(-Size/2,-Size/2,Size,Size);
}

QPainterPath BlockItem::shape()const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pix(picName);
    painter->drawPixmap(-Size/2,-Size/2,Size,Size,pix,0,0,Size,Size);
}




