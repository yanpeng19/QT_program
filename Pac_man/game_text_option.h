#ifndef GAME_TEXT_OPTION_H
#define GAME_TEXT_OPTION_H

#include <QObject>
#include <QGraphicsSimpleTextItem>
#include <QFont>

class game_text : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit game_text(QObject *parent = nullptr);
    game_text(QObject *parent = nullptr,QString s = "",QFont f=QFont());
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    QRectF boundingRect() const;
    void setFont(QFont f);

signals:
    void cliecked();

public slots:
    void keyPressEvent(QKeyEvent *event);
    void set_next(game_text * item);
    void set_pre(game_text * item);

private:
    qreal width;
    qreal high;
    QString s;
    QFont f;
    game_text * next;
    game_text * pre;
};

#endif // GAME_TEXT_OPTION_H
