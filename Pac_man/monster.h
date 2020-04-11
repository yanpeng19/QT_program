#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <vector>
#include <QTimer>

enum STATE{NORMAL,ESCAPE,ESCAPE_FLASH,DEATH};

class monster : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    monster(QObject *parent = nullptr);
    monster(QObject *parent = nullptr,QColor c = Qt::red,QPointF p = QPointF(0,0));

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void advance(int p);

signals:

public slots:
    void set_color(QColor c);
    void update_map(QPointF ball_coor);   // 根据球的坐标来判断前进路线
    void set_coordinate(QPointF p);
    void escape_mode();                   // 球进入逃跑模式
    void escape_mode_stop();

    void set_state(STATE s);
    void state_timer_stop();
    STATE get_state();


private:
    STATE state = NORMAL;
    QColor color;

    double speed;
    QPointF coordinate;   // 坐标
    int direction;        // 方向
    std::vector<std::vector<int>> map; // 前进路线图
    QPointF next_point;   // 行动路线中，下一个节点，帮助矫正


    QPainterPath main_body;              // 外表路径
    QPainterPath mouth;                  // 嘴巴弧线
    QPointF c1,c2,c3,c4,c5,c6;           // 画脚用的4个位置
    QPointF end1,end2,end3;              // 画脚的3个位置

    QTimer state_timer;
    double t = 0;
};

#endif // MASTER_H
