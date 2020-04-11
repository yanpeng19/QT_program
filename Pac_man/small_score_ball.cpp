#include "small_score_ball.h"
#include <QPainter>
#include <QPainterPath>

small_score_ball::small_score_ball()
{

}

QPainterPath small_score_ball::shape() const
{
    QPainterPath path;
    path.addEllipse(QRectF(-size/20,-size/20,size/10,size/10));
    return path;
}

QRectF small_score_ball::boundingRect() const
{
    return QRectF(-size/20,-size/20,size/10,size/10);
}

void small_score_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 画一个白色的原点
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(-size/20,-size/20,size/10,size/10));
}




