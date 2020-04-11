#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QtDebug>
#include "game_map.h"
#include "game_view.h"
#include "main_ball.h"
#include <QTextEdit>
#include "small_score_ball.h"
#include <QVector>
#include "big_score_ball.h"
#include "monster.h"
#include "game_mes.h"
#include "game_text_option.h"
#include "game_map_door.h"
#include <QSoundEffect>

class Game_widget : public QWidget
{
    Q_OBJECT

public:
    explicit Game_widget(QWidget *parent = nullptr);
    ~Game_widget();

    void begin();

public slots:
    void creat_score_point();
    void timer_stop();
    void timer_start();

    void impact_small_point(small_score_ball* b);
    void impact_big_point(big_score_ball* b);
    void impact_monster_normal(monster* m,QPointF p);

    void reset_pos();    // 死亡一条声明之后，重置球和怪物的函数
    void next_level();   // 所有的球都被吃完了，重置怪物和球位置，并且保存分数和声明
    void remove_items(); // 重置地图资源用

    int game_over();   // 游戏结束画面，并且询问是否重新开始

    //void reset_game(); // 重置分数，球，怪物，
    //void main_ball_dead(); // 球死亡， ->地图加载

signals:


private:
    QGraphicsScene * scene;
    QTimer main_timer;
    game_view * view;
    game_map * map;
    game_map_door * door;
    game_mes * mes;
    QGraphicsSimpleTextItem*  ready;

    main_ball * ball;
    monster *m1;
//    monster *m2;
//    monster *m3;
//    monster *m4;

    QVector<small_score_ball*> small_balls;
    QVector<big_score_ball*> big_balls;

    // GameOver 相关界面信息
    QGraphicsRectItem * background;
    QGraphicsSimpleTextItem * gameover;
    QGraphicsSimpleTextItem * try_again;
    game_text *yes;
    game_text *no;
    QTimer *temp_t;
    QGraphicsSimpleTextItem*  countdown;
    QGraphicsRectItem * mask_l;
    QGraphicsRectItem * mask_r;

    QTimer kill_steak_timer;
    double kill_steak_time = 0;
    int kill_steak_score = 0;

    // 背景音乐
    QSoundEffect game_effct;
};

void creat_barrier_map(QGraphicsScene *scene,vector<vector<int>>&barrier_map);
void creat_home_map(QGraphicsScene *scene,vector<vector<int>>&home_map);

#endif // GAME_WIDGET_H
