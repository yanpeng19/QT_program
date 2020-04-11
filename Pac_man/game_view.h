#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

// 场景
class game_view : public QGraphicsView
{
    Q_OBJECT

public:
    explicit game_view(QWidget * parent = 0);

protected:
    void keyPressEvent(QKeyEvent*event);
    void mousePressEvent(QMouseEvent * evnet);

};

#endif // GAME_VIEW_H
