#include "game_mes.h"
#include "const_data.h"
#include <QFont>
#include <QGraphicsSimpleTextItem>
#include "const_data.h"
#include <QPainter>
#include <QTextItem>
#include <QtDebug>
#include <QTimer>

game_mes::game_mes(QObject *parent) : QObject(parent)
{
    score = 0;
    lives = 3;
}

QRectF game_mes::boundingRect() const
{
    return QRectF(0,0,28*size,3*size);
}

void game_mes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //画 生命、分数、名字 等等信息
    QFont f = painter->font();
    f.setFamily("Bauhaus 93");
    f.setPointSize(size);
    painter->setFont(f);
    painter->setPen(Qt::white);

    painter->drawText(QRect(0,0,size*5,size*2), ("SCORE:"));
    painter->setPen(Qt::yellow);
    painter->drawText(QRect(5*size,0,size*5,size*2),QString::number(score));

    // 根据life 画小球
    QPainterPath path;
    path.moveTo(0.5*size,0.6*size);
    path.arcTo(QRectF(0,0,size*0.6*2,size*0.6*2),30,300);

    painter->setPen(Qt::white);
    painter->drawText(QRect(12.5*size,0,size*5,size*2), ("LIVES:"));
    QPointF pos(size*16,size*0.15);



    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::yellow);
    painter->setRenderHint(QPainter::Antialiasing, true);

    for(size_t i=0;i<lives;i++)
    {
        painter->save();
        painter->translate(pos);
        painter->drawPath(path);
        painter->restore();
        pos.setX((pos.x()+size*1.5));
    }
}

void game_mes::advance(int p)
{
    if(lives == 0)
    {
        emit lives_over();
    }
}

unsigned game_mes::get_lives()
{
    return lives;

}

void game_mes::set_score(unsigned int i)
{
    score = i;
}

void game_mes::set_life(unsigned int i)
{
    if(i>=0&&i<=3) lives = i;
}

void game_mes::add_socre(int n)
{
    score+=n;
    update();
}

void game_mes::impact_s_point()
{
    score+=10;
    update();
}

void game_mes::impact_b_point()
{
    score+=50;
    update();
}

void game_mes::impact_monster_normal()
{
    lives--;
    update();
}

void game_mes::impact_monster_escape()
{
    score+=200;
    update();
}

void game_mes::restore()
{
    score = 0;
    lives = 3;
}




