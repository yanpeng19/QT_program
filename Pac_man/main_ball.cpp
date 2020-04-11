#include "main_ball.h"
#include "const_data.h"
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QDebug>
#include <QTime>
#include <QTransform>
#include <QPointF>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "const_data.h"
#include <QPropertyAnimation>
#include <QTimer>

main_ball::main_ball(QGraphicsItem *parent)
{
    state = 1;
    coordinate = DEFAULT_MAIN_BALL_POS;
    direction = RIGHT;
    turn_direction = 0;
    mouth_angle = 45;
    mouth_dir = 0; // 嘴巴向外侧扩张为0 ，向内为1
    speed = size/40; // 每秒移动 size 距离，以及嘴巴开合两次

    setFlag(QGraphicsItem::ItemIsFocusable);
    //setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

QPainterPath main_ball::shape() const
{
    QPainterPath path;
    if(coordinate.x()>size*0.5&&coordinate.x()<size*27)
    {
        //普通情况
        switch(direction)
        {
        case RIGHT:
        {
            path.moveTo(-0.25*size,0);
            path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);
            break;
        }
        case LEFT:
        {
            path.moveTo(0.25*size,0);
            path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),180+mouth_angle,360-mouth_angle*2);
            break;
        }
        case UP:
        {
            path.moveTo(0,-0.25*size);
            path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),180-mouth_angle,360-mouth_angle*2);
            break;
        }
        case DOWN:
        {
            path.moveTo(0,0.25*size);
            path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),270+mouth_angle,360-mouth_angle*2);
            break;
        }
        }

        return path;
    }
    else
    {
        // 分割情况
        if(coordinate.x()<(0.5*size))
        {
            if(direction==LEFT)
            {
                path.moveTo(0.25*size,0);
                path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),180+mouth_angle,360-mouth_angle*2);
                path.moveTo(28.25*size,0);
                path.arcTo(QRectF(27.25*size,-0.75*size,size*0.75*2,size*0.75*2),180+mouth_angle,360-mouth_angle*2);
            }
            else
            {
                // 创造两个球体，左边一个右边一个
                path.moveTo(-0.25*size,0);
                path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);
                path.moveTo(27.75*size,0);
                path.arcTo(QRectF(27.25*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);
            }
        }
        else
        {

            if(direction==LEFT)
            {
                path.moveTo(0.25*size,0);
                path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),180+mouth_angle,360-mouth_angle*2);
                path.moveTo(-27.75*size,0);
                path.arcTo(QRectF(-28.75*size,-0.75*size,size*0.75*2,size*0.75*2),180+mouth_angle,360-mouth_angle*2);
            }
            else
            {
                // RIHGT
                path.moveTo(-0.25*size,0);
                path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);
                path.moveTo(-28.25*size,0);
                path.arcTo(QRectF(-28.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);
            }
        }
    }

}

QRectF main_ball::boundingRect() const
{
    // 根据 x,y 绘制范围

    if(coordinate.x()>size&&coordinate.x()<size*27)
    {
        return QRectF(-size,-size,size*2,size*2);
    }
    else
    {
        // 分割情况
        return QRectF(-size*29,-size,size*58,size*2);
    }
}

void main_ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 画一个圆
    painter->save();

    QPointF test_point(size,0);
    QPainterPath path;

    painter->translate(0,0);

    // 画球
    path.moveTo(-0.25*size,0);
    path.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);

    QBrush b(QColor(242,245,24));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setBrush(b);
    painter->setPen(QColor(242,245,24));


    // 画边框
    QPainterPath p;
    p.moveTo(-0.25*size,0);
    p.arcTo(QRectF(-0.75*size,-0.75*size,size*0.75*2,size*0.75*2),mouth_angle,360-mouth_angle*2);

    switch(direction)
    {
    case UP:
    {
        painter->rotate(270);
        break;
    }
    case LEFT:
    {
        painter->rotate(180);
        break;
    }
    case DOWN:
    {
        painter->rotate(90);
        break;
    }
    }

    // 画球
    painter->drawPath(path);

    if(coordinate.x()<0.5*size||coordinate.x()>size*27)
    {
        //画两个，然后用黑色的方框盖住超出部分的
        painter->save();
        if(coordinate.x()<0.5*size)
        {
            if(direction==LEFT)
            {
                // 画遮罩
                painter->rotate(180);
                painter->setBrush(Qt::black);
                painter->setPen(Qt::NoPen);
                painter->drawRect(-size,-size*0.9,size*0.5-coordinate.x(),size*1.8);

                // 画右边的球
                painter->setBrush(Qt::yellow);
                painter->translate(28*size,0);
                painter->rotate(180);
                painter->drawPath(path);
                painter->rotate(180);

                painter->setBrush(Qt::black);
                painter->drawRect(-coordinate.x()-0.5*size,-size*0.9,size*1.8-(0.5*size-coordinate.x())*0.9,size*1.8);
            }
            else
            {

                //画遮罩
                painter->setBrush(Qt::black);
                painter->setPen(Qt::NoPen);
                painter->drawRect(-1.5*size,-size*0.9,size-coordinate.x(),size*1.8);

                // 黄笔
                painter->setBrush(Qt::yellow);
                painter->translate(size*28,0);
                painter->drawPath(path);

                painter->setBrush(Qt::black);
                painter->drawRect(-size-coordinate.x()+0.5*size,-size*0.9,size*1.8,size*1.8);
            }
            painter->translate(size*27,0);
            // x < size 在地图右边再画一个
        }
        else
        {
            // coordinate.x() > 27.5
            if(direction==LEFT)
            {
                //画遮罩
                painter->rotate(180);
                painter->setBrush(Qt::black);
                painter->setPen(Qt::NoPen);
                painter->drawRect(-(coordinate.x()-27.5*size),-size*0.9,coordinate.x()-26.5*size,size*1.8);

                //画新的

                painter->rotate(180);
                painter->setBrush(Qt::yellow);
                painter->translate(28*size,0);
                painter->drawPath(path);

                //左半球遮罩
                painter->rotate(180);
                painter->setBrush(Qt::black);
                painter->drawRect(-(coordinate.x()-27.5*size),-size*0.9,-(coordinate.x()-25.5*size),size*1.8);
            }
            else
            {
                 painter->setBrush(Qt::black);
                 painter->setPen(Qt::NoPen);
                 painter->drawRect(size-(coordinate.x()-26.5*size),-0.9*size,coordinate.x()-27.5*size+size,1.8*size);

                 painter->setBrush(Qt::yellow);
                 painter->translate(-size*28,0);
                 painter->drawPath(path);
                 painter->setBrush(Qt::black);
                 painter->drawRect(size-(coordinate.x()-26.5*size),-0.9*size,(size+(27.5-coordinate.x())),1.8*size);

            }
        }
    }
    painter->restore();
}


void main_ball::clean_turn_direction()
{
    turn_direction=0;
}

void main_ball::set_coordinate(QPointF p)
{
    coordinate = p;
}

void main_ball::set_direction(int i)
{
    direction = i;
}

void main_ball::set_mouse(int i)
{
    mouth_angle = i;
}

void main_ball::advance(int phase)
{
    // 推进动作
    // a.首先判断方向是否可以转
    // b.然后判断是否可以前进
    // b1.如果新的方向没有前进的空间，那么不做转向和更新->恢复原坐标和方向
    // b2.如果有那么->
    // 1.重新确定嘴巴角度
    // 2.根据方向确定下一个坐标
    if(!phase) return;

    //qDebug()<<coordinate.x()/size << coordinate.y()/size;

    // 键盘先备份，如果转弯后无法前进，那么就恢复方向
    auto direction_back = direction;
    QPainterPath test_p2;

    if(turn_direction!=0||turn_direction!=direction)
    {
        if(turn_direction==LEFT)
        {
            direction = LEFT;
            test_p2.moveTo(coordinate.x()-size-speed/2,coordinate.y()-size+speed/2);
            test_p2.lineTo(coordinate.x()-size-speed/2,coordinate.y()+size-speed/2);
        }
        else if(turn_direction==RIGHT)
        {
            direction = RIGHT;
            test_p2.moveTo(coordinate.x()+size+speed/2,coordinate.y()-size+speed/2);
            test_p2.lineTo(coordinate.x()+size+speed/2,coordinate.y()+size- speed/2);
        }
        else if(turn_direction==UP)
        {
            direction = UP;
            test_p2.moveTo(coordinate.x()-size+speed/2,coordinate.y()-size-speed/2);
            test_p2.lineTo(coordinate.x()+size-speed/2,coordinate.y()-size-speed/2);
        }

        else if(turn_direction==DOWN)
        {
            direction = DOWN;
            test_p2.moveTo(coordinate.x()-size+speed/2,coordinate.y()+size+speed/2);
            test_p2.lineTo(coordinate.x()+size-speed/2,coordinate.y()+size+speed/2);
        }

        //获取scene 坐标点所有内容
        QList<QGraphicsItem*> items = scene()->items(test_p2);
        for(auto a :items)
        {
            if(a->data(0)==WALL||a->data(0)==DOOR)
            {
                //墙壁无法前进，不做转身，恢复方向
                direction = direction_back;
                break;
            }
        }
    }

    //qDebug()<< turn_direction;
    bool flag = 1;
    auto coordinate_back = coordinate;
    QPainterPath test_p;
    QPointF pf(0,0);
    qreal x,y;

    // 根据方向更新x,y坐标
    switch(direction)
    {
    case RIGHT:
    {
        coordinate.setX(coordinate.x()+speed);
        test_p.moveTo(coordinate.x()+size-speed/2,coordinate.y()-size+speed/2);
        test_p.lineTo(coordinate.x()+size-speed/2,coordinate.y()+size-speed/2);

        if(coordinate.x()>size*28) coordinate.setX(0);
        break;
    }
    case LEFT:
    {
        coordinate.setX(coordinate.x()-speed);
        test_p.moveTo(coordinate.x()-size+speed/2,coordinate.y()-size+speed/2);
        test_p.lineTo(coordinate.x()-size+speed/2,coordinate.y()+size-speed/2);

        if(coordinate.x()<0) coordinate.setX(28*size);
        break;
    }
    case UP:
    {
        coordinate.setY(coordinate.y()-speed);
        test_p.moveTo(coordinate.x()-size+speed/2,coordinate.y()-size+speed/2);
        test_p.lineTo(coordinate.x()+size-speed/2,coordinate.y()-size+speed/2);
        break;
    }
    case DOWN:
    {
        coordinate.setY(coordinate.y()+speed);
        test_p.moveTo(coordinate.x()-size+speed/2,coordinate.y()+size-speed/2);
        test_p.lineTo(coordinate.x()+size-speed/2,coordinate.y()+size-speed/2);
        break;
    }
    }
    setPos(coordinate);
    // 根据方向和坐标 判断 坐标位置->方向的  size 的位置，是否为墙壁，如果是，则不前进，恢复原状

    //获取scene 坐标点所有内容
    QList<QGraphicsItem*> items = scene()->items(test_p);
    for(auto a :items)
    {
        //qDebug()<< a->data(0);
        if(a->data(0)==WALL||a->data(0)==DOOR)
        {
            //墙壁无法前进，不做前进，恢复坐标
            coordinate = coordinate_back;
            setPos(coordinate);
            emit point(coordinate);

            items = collidingItems();
            for(auto a :items)
            {
                if(a->data(0)==MONSTER)
                {
                    emit impact_monster(dynamic_cast<monster*>(a),coordinate);
                    //qDebug()<<"impact a monster";
                }

            }
            return;
        }
    }

    // 前方无墙壁，更新嘴巴角度
    if(mouth_dir<=0)
    {
        // 向外扩张
        if(mouth_angle>=60) mouth_dir = 1;
        else mouth_angle+=2;
    }
    else
    {
        if(mouth_angle<=0) mouth_dir =0;
        else mouth_angle-=2;
    }

    items = collidingItems();
    for(auto a :items)
    {
        if(a->data(0)==POINT)
            emit impact_small_point(dynamic_cast<small_score_ball*>(a));

        if(a->data(0)==BIG_POINT)
            emit impact_big_point(dynamic_cast<big_score_ball*>(a));

        if(a->data(0)==MONSTER)
            emit impact_monster(dynamic_cast<monster*>(a),coordinate);
    }


    //qDebug()<<coordinate;
    emit point(coordinate);
    update();
}

void main_ball::keyPressEvent(QKeyEvent *event)
{

    // 键盘事件改变方向
    // 将新的方向存在临时转向中，0.3秒后清除
    if(event->key()==Qt::Key_Left||event->key()==Qt::Key_A||event->key()==Qt::Key_Right||event->key()==Qt::Key_D||
            event->key()==Qt::Key_Up||event->key()==Qt::Key_W||event->key()==Qt::Key_Down||event->key()==Qt::Key_S)
    {
        qDebug()<<event->key();
        if(event->key()==Qt::Key_Left||event->key()==Qt::Key_A) turn_direction = LEFT;
        else if(event->key()==Qt::Key_Right||event->key()==Qt::Key_D) turn_direction = RIGHT;
        else if(event->key()==Qt::Key_Up||event->key()==Qt::Key_W) turn_direction = UP;
        else turn_direction = DOWN;

        qDebug()<< turn_direction;
        timer.stop();
        timer.setInterval(700);
        timer.setSingleShot(1);
        timer.start();
        qDebug() << connect(&timer,&QTimer::timeout,this,[&]{turn_direction=0;});
    }

}
