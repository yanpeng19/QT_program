#include "game_view.h"
#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QString>
#include <QToolTip>
#include <QGraphicsItem>

game_view::game_view(QWidget * parent):
    QGraphicsView(parent)
{

}

void game_view::keyPressEvent(QKeyEvent *event)
{
   // qDebug()<<event->key();
    if(event->key()==Qt::Key_Escape)
        system("pause");

    QGraphicsView::keyPressEvent(event);
}

void game_view::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"View:" <<event->pos();
//    qDebug()<<"Scene:"<< this->mapToScene(event->pos());

//    QList<QGraphicsItem*> items = scene()->items(this->mapToScene(event->pos()));
//    if(items.empty()) qDebug() << "No item";
//    else for(auto a : items)
//    {

//        qDebug()<< a->pos()<<a->data(0);
//    }
    //QGraphicsView::mousePressEvent(event);
}
