#ifndef BIG_SCORE_BALL_H
#define BIG_SCORE_BALL_H

#include <QObject>
#include <QGraphicsItem>

class big_score_ball : public QObject ,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit big_score_ball(QObject *parent = nullptr);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

signals:

public slots:
};

#endif // BIG_SCORE_BALL_H
