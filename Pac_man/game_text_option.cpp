#include "game_text_option.h"
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include <QPainter>
#include <QPointF>
#include "const_data.h"
#include <QPen>
#include <QKeyEvent>
#include <QtDebug>

game_text::game_text(QObject *parent)
{
    setFlags(QGraphicsItem::ItemIsFocusable);
}

game_text::game_text(QObject *parent, QString _s,QFont _f) : s(_s),f(_f)
{
    setFlags(QGraphicsItem::ItemIsFocusable);
    width = size*5;
    high = size*2;
}

void game_text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //获取字体信息包括大小-为止-字体家族

    QPen pen;
    pen.setWidth(1);

    if(hasFocus()) pen.setBrush(Qt::yellow);
    else pen.setBrush(Qt::white);

    painter->setFont(f);
    painter->setPen(pen);
    painter->drawText(QRectF(0,0,width,high),s);
}

QRectF game_text::boundingRect() const
{
    return QRectF(0,0,3*size,2*size);
}

void game_text::setFont(QFont _f)
{
    f = _f;
}

void game_text::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return)
    {
        emit cliecked();
        qDebug()<<"emit";
    }
    if(event->key()==Qt::Key_W||event->key()==Qt::Key_Up)
    {
        pre->setFocus();
    }
    if(event->key()==Qt::Key_S||event->key()==Qt::Key_Down)
    {
        next->setFocus();
    }


    QGraphicsItem::keyPressEvent(event);
}

void game_text::set_next(game_text *item)
{
    next= item;
}

void game_text::set_pre(game_text *item)
{
    pre = item;
}
