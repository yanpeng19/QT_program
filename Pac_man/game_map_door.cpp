#include "game_map_door.h"
#include "const_data.h"
#include <QPainter>
#include <QPainterPath>

game_map_door::game_map_door(QObject *parent) : QObject(parent)
{

}

QRectF game_map_door::boundingRect() const
{
    return QRectF(-1.5*size,0,6*size,3*size);
}

QPainterPath game_map_door::shape() const
{
    QPainterPath path;
    path.addRect(0,0,3*size,0.5*size);
    path.addRect(-1.5*size,0.5*size,6*size,3*size);
    return path;
}

void game_map_door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRect(QRectF(0.1*size,0.2*size,size*2.8,0.1*size));

//    painter->setPen(Qt::red);
//    painter->drawRect(0,0,3*size,0.5*size);
//    painter->drawRect(-1.5*size,0.5*size,6*size,3*size);
}
