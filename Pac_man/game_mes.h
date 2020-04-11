#ifndef GAME_MES_H
#define GAME_MES_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QTimer>

class game_mes : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit game_mes(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void advance(int p);
    unsigned get_lives();

signals:
    void lives_over();

public slots:
    void set_score(unsigned int);
    void set_life(unsigned int);
    void add_socre(int n);
    void impact_s_point();
    void impact_b_point();
    void impact_monster_normal();
    void impact_monster_escape();
    void restore();

private:
    unsigned score;
    unsigned lives;  
};

#endif // GAME_MES_H
