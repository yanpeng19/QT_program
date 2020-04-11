#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <QGraphicsItem>
#include <QPainterPath>
#include "const_data.h"

class game_map : public QGraphicsItem
{

public:
    game_map();

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    QPainterPath path;
    QPainterPath bouding_path;
};

#endif // GANME_MAP_H
