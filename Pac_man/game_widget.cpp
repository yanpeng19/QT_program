#include "game_widget.h"
#include "ui_game_widget.h"
#include "game_map.h"
#include "const_data.h"
#include "main_ball.h"
#include <QTimer>
#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QGraphicsProxyWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QPointF>
#include "small_score_ball.h"
#include "big_score_ball.h"
#include "monster.h"
#include "game_map_door.h"
#include <iostream>
#include <QPen>
#include <iostream>
#include <algorithm>
#include "main_ball.h"
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QFont>
#include "game_mes.h"
#include <QColor>
#include "game_text_option.h"
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>

const double s = size;

Game_widget::Game_widget(QWidget *parent) :
    QWidget(parent)
{
    // 声明一个 700*700 的scene，以及scene的边界
    scene = new QGraphicsScene(0,0,700,700);
    scene->setSceneRect(0,0,700,700);

    // 初始化地图以及门
    map = new game_map;
    map->setPos(0,0);
    map->setData(0,WALL);

    door = new game_map_door();
    door->setPos(12*s,12*s);
    door->setData(0,DOOR);

    // 初始化信息
    mes = new game_mes();
    mes->setPos(-0.5*s,31*s);

    // 初始化主要球
    ball = new main_ball;
    ball->setData(0,BALL);
    ball->setPos(DEFAULT_MAIN_BALL_POS);

    // 初始化怪物
    m1 = new monster(nullptr,Qt::red,QPointF(6*s,10*s));
    m1->setData(0,MONSTER);
    m1->setData(1,0);
    //m1->setPos(DEFAULT_M1_POS);
    m1->setPos(6*s,10*s);

    ball->setFocus();

    ready = new QGraphicsSimpleTextItem;
    ready->setText("READY");
    ready->setFont(QFont("思源黑体",15));
    ready->setBrush(Qt::white);
    ready->setPos(12*s,10.5*s);

    // 初始化 GameOver 相关内容初始化
    background = new QGraphicsRectItem(-s*3,0,800+s*5,800);
    gameover = new QGraphicsSimpleTextItem("GAME OVER");
    try_again = new QGraphicsSimpleTextItem("Try again?");
    yes = new game_text(nullptr,"yes");
    no   = new game_text(nullptr,"no");
    yes->set_next(no);
    no->set_next(yes);
    yes->set_pre(no);
    no->set_pre(yes);
    temp_t = new QTimer;
    countdown = new QGraphicsSimpleTextItem();

    // 添加遮罩
    mask_l = new QGraphicsRectItem(0,0,s*2,s*1.8);
    mask_r = new QGraphicsRectItem(0,0,s*2,s*1.8);
    mask_l->setBrush(Qt::black);
    mask_r->setBrush(Qt::black);
    mask_l->setPos(-2.5*s,13*s);
    mask_r->setPos(27.5*s,13*s);

    // 初始化背景音乐
    //game_effct.setSource(QUrl::fromLocalFile("C:/Users/yan/Documents/pan_man/1.wav"));
    game_effct.setSource(QUrl::fromLocalFile("1.wav"));
    game_effct.setLoopCount(QSoundEffect::Infinite);
    game_effct.setVolume(0.25F);
    game_effct.play();

    //各种信号槽
    QObject::connect(temp_t,&QTimer::timeout,this,[=]
    {
        int i = countdown->text().toInt();
        if(i==1)
        {
            temp_t->stop();
            scene->removeItem(ready);
            scene->removeItem(countdown);
            update();
            timer_start();
        }
        else
        {
            i--;
            countdown->setText(QString(QString::number(i)));
        }
    });

    qDebug()<<connect(ball,&main_ball::point,m1,&monster::update_map);
    qDebug()<<connect(ball,&main_ball::impact_small_point,this,[=](small_score_ball* b)
    {
        mes->add_socre(10);
        Game_widget::impact_small_point(b);

    });
    qDebug()<<connect(ball,&main_ball::impact_big_point,this,[=](big_score_ball* b)
    {
        // ball->widget->mes
        mes->add_socre(50);
        impact_big_point(b);
        m1->escape_mode();
    });
    qDebug()<<connect(ball,&main_ball::impact_monster,this,[=](monster* m,QPointF p)
    {
        // ball->widget->mes
        if(m->get_state()==NORMAL)
        {
            //进入begin流程
            impact_monster_normal(m,p);

            m->state_timer_stop();
            mes->impact_monster_normal();
        }
        else if(m->get_state()==ESCAPE)
        {
            // 球在无敌状态碰到怪物
            // 分数+200，并且播放一小段动画
            // 怪物进入->DEATH 状态
            kill_steak_time = 0;
            kill_steak_score += 200;
            kill_steak_timer.stop();
            kill_steak_timer.start(1000);
            mes->add_socre(kill_steak_score);
            m->escape_mode_stop();
            m->set_state(DEATH);
        }

    });
    qDebug()<<connect(yes,&game_text::cliecked,this,[=]()
    {
        mes->set_life(3);
        mes->set_score(0);
        remove_items();
        begin();
    });
    qDebug()<<connect(no,&game_text::cliecked,this,[=]()
    {
       view->close();
    });
    qDebug()<<connect(mes,&game_mes::lives_over,this,[=]()
    {
        game_over();
    });
    qDebug()<<connect(&kill_steak_timer,&QTimer::timeout,this,[=]()
    {
       kill_steak_time++;
       if(kill_steak_time>=5)
       {
           kill_steak_timer.stop();
           kill_steak_score = 0;
           kill_steak_time=0;
       }
    });

    // 声明view
    view = new game_view ;
    view->setScene(scene);

    //view->setMaximumSize(800,800);
    view->setMinimumSize(800,800);
    view->setBackgroundBrush(QColor(0,0,0));

    QObject::connect(&main_timer,&QTimer::timeout,scene,&QGraphicsScene::advance);

    // 加载内容
    scene->addItem(map);
    // 初始化边界地图
    creat_barrier_map(scene,barrier_map);
    creat_home_map(scene,home_map);
    scene->addItem(door);
    scene->addItem(mes);
    creat_score_point();
    scene->addItem(m1);
    scene->addItem(ball);
    scene->addItem(mask_l);
    scene->addItem(mask_r);

    begin();
    //game_over();
    //view->show();
}

Game_widget::~Game_widget()
{

}

void Game_widget::begin()
{
    // 设置 3秒 倒计时 READY  3->2->1

    scene->advance();
    scene->addItem(ready);

    countdown->setText("3");
    countdown->setFont(QFont("思源黑体",15));
    countdown->setBrush(Qt::white);
    countdown->setPos(13.25*s,13*s);
    scene->addItem(countdown);
    temp_t->start(1000);
    ball->setFocus();
    view->show();
}


void Game_widget::creat_score_point()
{

    // 首先添加大球
    big_score_ball* big1 = new big_score_ball;
    big_score_ball* big2 = new big_score_ball;
    big_score_ball* big3 = new big_score_ball;
    big_score_ball* big4 = new big_score_ball;

    big1->setPos(s,s*3);
    big2->setPos(26*s,s*3);
    big3->setPos(s,23*s);
    big4->setPos(26*s,23*s);

    big1->setData(0,BIG_POINT);
    big2->setData(0,BIG_POINT);
    big3->setData(0,BIG_POINT);
    big4->setData(0,BIG_POINT);

    scene->addItem(big1);
    scene->addItem(big2);
    scene->addItem(big3);
    scene->addItem(big4);

    big_balls.push_back(big1);
    big_balls.push_back(big2);
    big_balls.push_back(big3);
    big_balls.push_back(big4);


    // 循环添加分数小球
    for(int i = s;i<27*s;i+=s)
    {
        for(int j = s;j<9*s;j+=s)
        {
            QPainterPath path;
            path.moveTo(i,j);
            path.lineTo(i+1,j);
            if(!scene->items(path).empty()) continue;
            small_score_ball *temp = new small_score_ball();
            temp->setData(0,POINT);
            small_balls.push_back(temp);
            temp->setPos(i,j);
            scene->addItem(temp);
        }
    }

    for(int i = s;i<27*s;i+=s)
    {
        for(int j = 20*s;j<30*s;j+=s)
        {
            QPainterPath path;
            path.moveTo(i,j);
            path.lineTo(i+1,j);
            if(!scene->items(path).empty()) continue;
            small_score_ball *temp = new small_score_ball();
            temp->setData(0,POINT);
            small_balls.push_back(temp);
            temp->setPos(i,j);
            scene->addItem(temp);
        }
    }

    for(int i=9*s;i<20*s;i+=s)
    {
        QPainterPath path;
        path.moveTo(6*s,i);
        path.lineTo(6*s,i+1);
        if(!scene->items(path).empty()) continue;
        small_score_ball *temp = new small_score_ball();
        temp->setData(0,POINT);
        small_balls.push_back(temp);
        temp->setPos(6*s,i);
        scene->addItem(temp);
    }

    for(int i=9*s;i<20*s;i+=s)
    {
        QPainterPath path;
        path.moveTo(21*s,i);
        path.lineTo(21*s,i+1);
        if(!scene->items(path).empty()) continue;
        small_score_ball *temp = new small_score_ball();
        temp->setData(0,POINT);
        small_balls.push_back(temp);
        temp->setPos(21*s,i);
        scene->addItem(temp);
    }
}

void Game_widget::timer_start()
{
    // 推进场景定时器
    main_timer.start(1000/240);
}

void Game_widget::impact_small_point(small_score_ball *b)
{
    scene->removeItem(b);
    auto pos = std::find(small_balls.begin(),small_balls.end(),b);
    if(pos!=small_balls.end())
        small_balls.erase(pos);
    if(small_balls.empty()&&big_balls.empty()) next_level();
}

void Game_widget::impact_big_point(big_score_ball *b)
{
    scene->removeItem(b);
    auto pos = std::find(big_balls.begin(),big_balls.end(),b);
    if(pos!=big_balls.end())
        big_balls.erase(pos);
}

void Game_widget::impact_monster_normal(monster *m,QPointF p)
{
//    //碰到怪物之后的处理-> 停止主定时器->从scene中删除 分数+怪物+球 -> 播放死亡动画
//    // -> 重置球位置+怪物位置 -> 重新启动定时器

    // 停止计时器，恢复为止
    // 重新开始
    timer_stop();
    m->state_timer_stop();
    reset_pos();

    if(mes->get_lives()) begin();
    //else game_over();
}

void Game_widget::reset_pos()
{
    //重置球的位置，怪物的位置
    ball->set_coordinate(DEFAULT_MAIN_BALL_POS);
    ball->set_direction(RIGHT);
    ball->set_mouse(0);
    //m1->set_coordinate(DEFAULT_M1_POS);
    m1->set_coordinate(QPointF(6*s,10*s));
}

void Game_widget::next_level()
{
    timer_stop();
    // 重置球和怪物的位置
    reset_pos();
    remove_items();
    //并且重新开始
    begin();
}

void Game_widget::remove_items()
{
    // 首先把所有内容从场景中清空
    while(!small_balls.empty())
    {
        auto a = small_balls.back();
        small_balls.pop_back();
        scene->removeItem(a);
        delete a;
    }
    while(!big_balls.empty())
    {
        auto a = big_balls.back();
        big_balls.pop_back();
        scene->removeItem(a);
        delete a;
    }

    auto list = scene->items();
    for(auto a : list)
        scene->removeItem(a);

    list = scene->items();

    // 加载内容
    scene->addItem(map);
    scene->addItem(door);
    creat_score_point();
    scene->addItem(mes);
    scene->addItem(m1);
    m1->state_timer_stop();
    m1->set_state(NORMAL);
    scene->addItem(ball);
    scene->addItem(mask_l);
    scene->addItem(mask_r);
    scene->advance();
    scene->update();
}

int Game_widget::game_over()
{
    // 游戏结束画面，创造一个黑幕覆盖，然后上面写GAME OVER
    // 并且拥有focus选项

    timer_stop();
    background->setBrush(Qt::black);
    background->setPos(QPointF(-s,-s));

    QFont f;
    f.setFamily("微软雅黑");
    f.setPointSize(s*2);

    gameover->setPen(QColor(255,255,255));
    gameover->setFont(f);
    gameover->setBrush(QColor(255,255,255));
    gameover->setPos(s*5,s*4);
    gameover->setFlag( QGraphicsItem::ItemIsSelectable,0);

    f.setPointSize(s);

    try_again->setPen(QColor(255,255,255));
    try_again->setFont(f);
    try_again->setBrush(QColor(255,255,255));
    try_again->setPos(s*10,s*7.5);
    try_again->setFlag( QGraphicsItem::ItemIsSelectable,0);

    yes->setFont(f);
    no->setFont(f);

    yes->setFocus();
    yes->setPos(s*12,s*10);
    no->setPos(s*12,s*12);

    yes->setData(0,TEXT);
    no->setData(0,TEXT);
    yes->setData(1,YES);
    yes->setData(1,NO);


    scene->addItem(background);
    scene->addItem(gameover);
    scene->addItem(try_again);
    scene->addItem(yes);
    scene->addItem(no);
    yes->setFocus();
    update();
    return 1;
}

void Game_widget::timer_stop()
{
    main_timer.stop();
}

void creat_barrier_map(QGraphicsScene *scene, vector<vector<int>> &barrier_map)
{
    barrier_map = vector<vector<int>>(30,vector<int>(31,1));
    // 更正- 因为地图存在-0.5*size 坐标，所以边界地图增加两列，地图横坐标偏移量为1
    // 即 坐标 -0.5*size,13*size  = barried_map[0][13]

    for(int i = 0;i<30;i++)
    {
        for(int j = 0;j<=30;j++)
        {
            QPainterPath path;
            path.moveTo((i-1)*size,j*size);
            path.lineTo((i-1)*size-0.6*size,j*size);
            path.lineTo((i-1)*size-0.6*size,j*size+0.6*size);

            auto items = scene->items(path);
            if(items.empty()) barrier_map[i][j]=0;
            else barrier_map[i][j] = 1;
        }
    }
}

void creat_home_map(QGraphicsScene *scene, vector<vector<int> > &home_map)
{
    // 创建回家地图，以位置
    home_map = vector<vector<int>>(28,vector<int>(30,999));
    vector<vector<bool>> temp(28,vector<bool>(30,0));  // 记录某个节点是否已经计算；

    int x = 14;
    int y = 14;

    // 存放合法节点
    vector<pair<int,int>> stack;
    stack.push_back(pair<int,int>(x,y));

    int t = 0; // 步数 每次都迭代可以 t 步内可以到达的位置，并且填充表格
    while(!stack.empty())
    {
        auto stack_temp = stack;
        stack.clear();

        while(!stack_temp.empty())
        {
            x = stack_temp.back().first;
            y = stack_temp.back().second;
            stack_temp.pop_back();

            // 然后判断大小，如果本身可以<t布内到达，则不动，否则将步数填入其中，并且将其接壤的合法坐标推进栈中

            if(!temp[x][y]||home_map[x][y]>t)
            {
                temp[x][y] = 1;
                home_map[x][y]=t;
                // 上下左右都推入栈中
                if(x-1>=0&&!barrier_map[x-1][y])
                    stack.push_back(pair<int,int>(x-1,y));
                if(x+1<28&&!barrier_map[x+1][y])
                    stack.push_back(pair<int,int>(x+1,y));
                if(y-1>=0&&!barrier_map[x][y-1])
                    stack.push_back(pair<int,int>(x,y-1));
                if(y+1<30&&!barrier_map[x][y+1])
                    stack.push_back(pair<int,int>(x,y+1));
            }
        }
        t++;
    }
}
