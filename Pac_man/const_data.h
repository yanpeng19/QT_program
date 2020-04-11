#ifndef CONST_DATA_H
#define CONST_DATA_H

#include <vector>
#include <QGraphicsScene>
#include <QVector>
#include <QPointF>

using namespace std;

const int UP = 10;
const int LEFT = 20;
const int RIGHT = 30;
const int DOWN = 40;

// 以下为 DATA(0) 身份
const int WALL = 0;
const int MONSTER = 1;
const int POINT = 2;
const int BIG_POINT = 3;
const int BALL = 4;
const int DOOR = 5;
const int TEXT = 6;

// TEXT DATA(1)细分
const int YES = 80;
const int NO = 81;

const double size = 15;
const QPointF DEFAULT_MAIN_BALL_POS = QPointF(13.5*size,17*size);
const QPointF DEFAULT_M1_POS = QPointF(13.5*size,14*size);

const double MONSTER_NORMAL_SPEED = size/60;
const double MONSTER_DEATH_SPEED = size/30;

// 边界地图
extern vector<vector<int>> barrier_map;
// 从地图各点回到中心的图
extern vector<vector<int>> home_map;

#endif // CONST_DATA_H
