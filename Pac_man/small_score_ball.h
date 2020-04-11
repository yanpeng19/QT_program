#ifndef SMALL_SCORE_BALL_H
#define SMALL_SCORE_BALL_H

#include <QObject>
#include <QVector>
#include <QGraphicsObject>
#include <QPointF>
#include "const_data.h"

class small_score_ball : public QGraphicsObject
{
   Q_OBJECT

public:
    small_score_ball();

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    QPointF coordinate;
};

#endif // SMALL_SCORE_BALL_H
