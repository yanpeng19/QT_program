#include "big_score_ball.h"
#include <QPainter>
#include <QPainterPath>
#include "const_data.h"

big_score_ball::big_score_ball(QObject *parent) : QObject(parent)
{

}

QPainterPath big_score_ball::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-size/5,-size/5,size/2.5,size/2.5));
    return path;
}

QRectF big_score_ball::boundingRect() const
{
    return QRectF(-size/5,-size/5,size/2.5,size/2.5);
}

void big_score_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(-size/5,-size/5,size/2.5,size/2.5));
}
