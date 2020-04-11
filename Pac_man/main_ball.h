#ifndef MAIN_BALL_H
#define MAIN_BALL_H

#include <QGraphicsItem>
#include <QPointf>
#include <QTimer>
#include <QTime>
#include "small_score_ball.h"
#include "big_score_ball.h"
#include "monster.h"
#include <QPropertyAnimation>

class main_ball : public QGraphicsObject
{

    Q_OBJECT

public:
    explicit main_ball(QGraphicsItem *parent = 0);


    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void advance(int phase);

signals:
    void point(QPointF p);
    void pause();
    void impact_small_point(small_score_ball* b);
    void impact_big_point(big_score_ball* b);
    void impact_monster(monster* m,QPointF p);

public slots:
    void clean_turn_direction();
    void set_coordinate(QPointF p);
    void set_direction(int i);
    void set_mouse(int i);
    //int death_animation();        // 死亡动画+音乐

private:
    int state;            // 无敌为1 普通为2
    QPointF coordinate;   // 坐标
    int direction;        // 方向
    int turn_direction;   // 存储的临时转向，存0.3秒
    QTime time;           // 转向倒计时器
    QTimer timer;
    int mouth_angle;      // 嘴巴角度
    bool mouth_dir;
    double speed;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAIN_BALL_H
