#ifndef GAME_MAP_DOOR_H
#define GAME_MAP_DOOR_H

#include <QObject>
#include <QGraphicsItem>

class game_map_door : public QObject,public QGraphicsItem
{
    Q_OBJECT

public:
    explicit game_map_door(QObject *parent = nullptr);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

signals:

public slots:
};

#endif // GAME_MAP_DOOR_H
