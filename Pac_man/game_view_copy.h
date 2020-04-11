#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsView>

// 场景
class game_view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit game_view(QWidget * parent = 0);

};

#endif // GAME_VIEW_H
