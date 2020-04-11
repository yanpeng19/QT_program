 #include "monster.h"
#include "const_data.h"
#include <QPainter>
#include <QPainterPath>
#include <QtDebug>
#include <memory>
#include <math.h>
#include <iostream>
#include <QPointF>
#include <QGraphicsItem>
#include <QPixmap>
#include <QBitmap>
#include <QTimer>

using namespace std;

monster::monster(QObject *parent) : QObject(parent)
{
    color = Qt::red;
    map = vector<vector<int>>(29,vector<int>(31,99));
    speed = size/80;
    coordinate = pos();
    coordinate = QPointF(size*6,size*10);
    state = NORMAL;
    c1 = QPointF(-size*0.8+size*0.8*1/3*0.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c2 = QPointF(-size*0.8+size*0.8*1/3*1.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c3 = QPointF(-size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5);
    c4 = QPointF(size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5);
    c5 = QPointF(size*0.8*0.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c6 = QPointF(size*0.8*5/6,size*0.8*2*0.4+size*0.8*2*1/5);

    end1 = QPointF(-size*0.8+size*0.8*2*1/3,size*0.8*2*0.4);
    end2 = QPointF(size*0.8*1/3,size*0.8*2*0.4);
    end3 = QPointF(size*0.8,size*0.8*2*0.4);
    setPos(coordinate);
}

monster::monster(QObject *parent, QColor c, QPointF p) :
    QObject(parent),color(c),coordinate(p)
{
    map = vector<vector<int>>(29,vector<int>(31,99));
    speed = size/80;

//    c1 = QPointF(-size*0.8+size*0.8*1/3*0.5,size*0.8*2*0.4+size*0.8*2*1/5*1.5);
//    c2 = QPointF(-size*0.8+size*0.8*1/3*1.5,size*0.8*2*0.4+size*0.8*2*1/5*1.5);
//    c3 = QPointF(-size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5*1.5);
//    c4 = QPointF(size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5*1.5);
//    c5 = QPointF(size*0.8*0.5,size*0.8*2*0.4+size*0.8*2*1/5*1.5);
//    c6 = QPointF(size*0.8*5/6,size*0.8*2*0.4+size*0.8*2*1/5*1.5);

    c1 = QPointF(-size*0.8+size*0.8*1/3*0.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c2 = QPointF(-size*0.8+size*0.8*1/3*1.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c3 = QPointF(-size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5);
    c4 = QPointF(size*0.8*1/6,size*0.8*2*0.4+size*0.8*2*1/5);
    c5 = QPointF(size*0.8*0.5,size*0.8*2*0.4+size*0.8*2*1/5);
    c6 = QPointF(size*0.8*5/6,size*0.8*2*0.4+size*0.8*2*1/5);

    end1 = QPointF(-size*0.8+size*0.8*2*1/3,size*0.8*2*0.4);
    end2 = QPointF(size*0.8*1/3,size*0.8*2*0.4);
    end3 = QPointF(size*0.8,size*0.8*2*0.4);

    // 初始化身体轮廓路径
    main_body.moveTo((size*0.8),0);
    main_body.arcTo(QRectF(-size*0.8,-size*0.8*2*0.4,size*0.8*2,size*0.8*2*0.4*2),0,180);
    main_body.lineTo(-size*0.8,size*0.8*2*0.4);
    // 身体轮廓-画波浪脚
    main_body.cubicTo(c1,c2,end1);
    main_body.cubicTo(c3,c4,end2);
    main_body.cubicTo(c5,c6,end3);

    mouth.moveTo(-0.8*size*0.65,size*0.8*0.5);
    QPointF temp_end = QPointF(-0.8*size*0.8+0.8*size*0.8*2*1/3,size*0.5*0.8);
    QPointF temp_c1(-0.8*size*0.65+0.8*size*0.8*1/3*1/4,size*0.8*0.5*0.8);
    QPointF temp_c2(-0.8*size*0.65+0.8*size*0.8*1/3*3/4,size*0.8*0.5*0.8);
    mouth.cubicTo(temp_c1,temp_c2,temp_end);

    temp_end = QPointF(-0.8*size*0.65+0.8*size*0.8*2*2/3,size*0.5*0.8);
    temp_c1 = QPointF(-0.8*size*0.65+0.8*size*0.8*2*1/3+0.8*size*0.8*1/4*1/4,size*0.8*0.5*1.2);
    temp_c2 = QPointF(-0.8*size*0.65+0.8*size*0.8*2*1/3+0.8*size*0.8*2/3*3/4,size*0.8*0.5*1.2);
    mouth.cubicTo(temp_c1,temp_c2,temp_end);

    temp_end = QPointF(-0.8*size*0.65+0.8*size*0.8*2*3/3,size*0.5*0.8);
    temp_c1 = QPointF(-0.8*size*0.65+0.8*size*0.8*2*2/3+0.8*size*0.8*2/3*1/4,size*0.8*0.5*0.8);
    temp_c2 = QPointF(-0.8*size*0.65+0.8*size*0.8*2*2/3+0.8*size*0.8*2/3*3/4,size*0.8*0.5*0.8);
    mouth.cubicTo(temp_c1,temp_c2,temp_end);

    main_body.lineTo(size*0.8,0);

    setPos(coordinate);
}


QPainterPath monster::shape() const
{
    QPainterPath p;
    p.addEllipse(QRectF(-size/2,-size/2,size,size));

    if(coordinate.x()<size*0.5&&coordinate.x()>size*27)
        p.addEllipse(QRectF(-size/2+28,-size/2,size,size));

    return p;
}

QRectF monster::boundingRect() const
{
    if(coordinate.x()>size&&coordinate.x()<size*27)
    {
        return QRectF(-size,-size,size*2,size*2);
    }
    else
    {
        // 分割情况
        return QRectF(-size*30,-size,size*60,size*2);
    }
}

void monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 根据不同的状态，设置Brush
    QBrush main_brush;
    QBrush eye_brush;
    QBrush eyeball_brush;

    QPixmap image(size*2,size*2);
    image.fill(Qt::transparent);

    QPainter img_painter(&image);
    img_painter.translate(size,size);
    img_painter.setCompositionMode(QPainter::CompositionMode_Source);

    if(state==NORMAL||state==DEATH)
    {
        speed = MONSTER_NORMAL_SPEED;
        if(state==NORMAL)
        {
            main_brush = QBrush(color);
            eye_brush= QBrush(Qt::white);
            eyeball_brush = QBrush(Qt::black);
        }
        else
        {
            // 死亡模式 -> 只画眼睛
            main_brush = QBrush(Qt::NoBrush);
            eye_brush = QBrush(Qt::white);
            eyeball_brush = QBrush(Qt::black);
        }
        img_painter.setRenderHint(QPainter::Antialiasing, true);
        img_painter.setBrush(main_brush);
        img_painter.drawPath(main_body);


//        painter->setRenderHint(QPainter::Antialiasing, true);
//        painter->setBrush(main_brush);
//        painter->drawPath(main_body);

        // 眼睛
        QPainterPath eye;
//        painter->setBrush(eye_brush);
//        painter->setPen(Qt::NoPen);
//        painter->drawEllipse(-size*0.8*0.8*1.2,-size*0.8*0.5,size*0.8*0.8,size*0.8*0.8);
//        painter->drawEllipse(size*0.8*0.8*0.2,-size*0.8*0.5,size*0.8*0.8,size*0.8*0.8);
        img_painter.setBrush(eye_brush);
        img_painter.setPen(Qt::NoPen);
        img_painter.drawEllipse(-size*0.8*0.8*1.2,-size*0.8*0.5,size*0.8*0.8,size*0.8*0.8);
        img_painter.drawEllipse(size*0.8*0.8*0.2,-size*0.8*0.5,size*0.8*0.8,size*0.8*0.8);

        //眼球
        img_painter.setBrush(eyeball_brush);
        //painter->setBrush(eyeball_brush);

        //根据方向画眼球
        if(direction==LEFT)
        {
//            painter->drawRect(QRectF(-size*0.8*0.8*1.15,-size*0.8*0.5*0.6,size*0.8*0.4,size*0.8*0.4));
//            painter->drawRect(QRectF(size*0.8*0.8*0.15,-size*0.8*0.5*0.6,size*0.8*0.4,size*0.8*0.4));
            img_painter.drawRect(QRectF(-size*0.8*0.8*1.15,-size*0.8*0.5*0.6,size*0.8*0.4,size*0.8*0.4));
            img_painter.drawRect(QRectF(size*0.8*0.8*0.15,-size*0.8*0.5*0.6,size*0.8*0.4,size*0.8*0.4));
        }
        else if(direction==RIGHT)
        {
//            painter->drawRect(-size*0.8*0.8*0.65,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
//            painter->drawRect(size*0.8*0.55,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(-size*0.8*0.8*0.65,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(size*0.8*0.55,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
        }
        else if(direction == UP)
        {
//            painter->drawRect(-size*0.8*0.8,-size*0.8*0.8*0.65,size*0.8*0.4,size*0.8*0.4);
//            painter->drawRect(size*0.8*0.4,-size*0.8*0.8*0.65,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(-size*0.8*0.8,-size*0.8*0.8*0.65,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(size*0.8*0.4,-size*0.8*0.8*0.65,size*0.8*0.4,size*0.8*0.4);
        }
        else
        {
//            painter->drawRect(-size*0.8*0.725,-size*0.8*0.8*0.205,size*0.8*0.4,size*0.8*0.4);
//            painter->drawRect(size*0.8*0.4,-size*0.8*0.8*0.205,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(-size*0.8*0.725,-size*0.8*0.8*0.205,size*0.8*0.4,size*0.8*0.4);
            img_painter.drawRect(size*0.8*0.4,-size*0.8*0.8*0.205,size*0.8*0.4,size*0.8*0.4);
        }
    }
    else if(state==ESCAPE||state==ESCAPE_FLASH)
    {
        // 逃离状态-> 身体 + 嘴 + 不动的眼睛     蓝白配色
        if(state==ESCAPE)
        {
            main_brush = QBrush(Qt::blue);
            eyeball_brush = QBrush(Qt::white);
        }
        else
        {
            main_brush = QBrush(Qt::white);
            eyeball_brush = QBrush(Qt::red);
        }


        img_painter.setPen(Qt::NoPen);
        img_painter.setBrush(main_brush);
        img_painter.drawPath(main_body);

        img_painter.setBrush(eyeball_brush.color());
        img_painter.setPen(eyeball_brush.color());
        img_painter.drawPath(mouth);

        img_painter.drawEllipse(-size*0.8*0.65,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
        img_painter.drawEllipse(size*0.8*0.4,-size*0.8*0.5*0.65,size*0.8*0.4,size*0.8*0.4);
    }

    painter->drawPixmap(-size,-size,image);

    //如果超出了范围，需要加画一个镜像，在左/右侧
    if(coordinate.x()<size*0.5||coordinate.x()>size*27.5)
    {
        if(coordinate.x()<size*0.5)
        {
            painter->drawPixmap(27*size,-size,image);
//            //遮罩
//            painter->setBrush(Qt::green);
//            painter->drawRect(-size,-size*0.9,0.5*size-coordinate.x(),1.8*size);
//            painter->drawRect(27*size+(0.5*size-coordinate.x()),-size*0.9,size*2-(0.5*size-coordinate.x()),1.8*size);
        }
        else
        {
            painter->drawPixmap(-29*size,-size,image);
        }
    }
}

void monster::advance(int p)
{

    // 根据球的编号 data->(1,0/1/2/3); 制定行动路线
    if(!p) return;
    if(coordinate.x()>=size*13&&coordinate.x()<=14*size&&coordinate.y()==size*14&&state==DEATH)
        state=NORMAL;

    //qDebug()<<coordinate.x()/size << coordinate.y()/size;

    if(data(1)==0)
    {
        // 0 号怪物的行动思路
        if(state==NORMAL||state==ESCAPE||state==ESCAPE_FLASH)
        {
            int left,right,up,down;
            if(state==NORMAL)
            {
                // 根据map 前后左右的数值 来判断下一步的行动路线 并且获得下一个目标坐标点NEXT_POINT;
                left = right = up = down = 999;
                int x = (coordinate.x()/size);
                int y = coordinate.y()/size;

                // x,y 是否为整数坐标
                bool flag_x = 0;
                bool flag_y = 0;
                if(x*size==coordinate.x()) flag_x = 1;
                if(y*size==coordinate.y()) flag_y = 1;
                x++;

                if(!flag_x)
                {
                    //那么智能左右移动
                    left=map[x][y];
                    if(x+1<30) right = map[x+1][y];
                }
                else if(!flag_y)
                {
                    // 只能上下移动
                    up = map[x][y];
                    if(y+1<30) down = map[x][y+1];
                }
                else
                {
                    // 正好在路口
                    if(x-1>=0) left = map[x-1][y];

                    if(x+1<30) right = map[x+1][y];
                    if(y-1>=0) up = map[x][y-1];
                    if(y+1<30) down = map[x][y+1];
                }
                int m = 0;
                m = min( min(left,right),min(up,down));

                if(m==left)
                {
                    direction=LEFT;
                    next_point = QPointF((x-2)*size,y*size);
                }
                else if(m == right)
                {
                    direction = RIGHT;
                    next_point = QPointF((x)*size,y*size);
                }
                else if(m==up)
                {
                    direction =UP;
                    next_point = QPointF((x-1)*size,(y-1)*size);
                }
                else
                {
                    direction =DOWN;
                    next_point = QPointF((x-1)*size,(y+1)*size);
                }

//                // 极端情况2中
//                if(next_point.x()>27) next_point.setX(0);
//                else if(next_point.x()<0) next_point.setX(27);
            }
            else if(state == ESCAPE||state==ESCAPE_FLASH)
            {
                left = right = up = down = 0;
                int x = coordinate.x()/size;
                int y = coordinate.y()/size;
                bool flag_x = 0;
                bool flag_y = 0;
                if(x*size==coordinate.x()) flag_x = 1;
                if(y*size==coordinate.y()) flag_y = 1;
                x++;

                if(!flag_x)
                {
                    //那么智能左右移动
                    left=map[x][y];
                    if(x+1<30) right = map[x+1][y];
                }
                else if(!flag_y)
                {
                    // 只能上下移动
                    up = map[x][y];
                    if(y+1<30) down = map[x][y+1];
                }
                else
                {
                    // 正好在路口
                    if(x-1>=0) left = map[x-1][y];
                    if(x+1<30) right = map[x+1][y];
                    if(y-1>=0) up = map[x][y-1];
                    if(y+1<30) down = map[x][y+1];
                }
                if(left>=99) left = 0;
                if(right>=99) right = 0;
                if(up>=99) up = 0;
                if(down >= 99) down = 0;
                int m = 0;
                m = max(max(left,right),max(up,down));

                if(m==left)
                {
                    direction=LEFT;
                    next_point = QPointF((x-2)*size,y*size);
                }
                else if(m == right)
                {
                    direction = RIGHT;
                    next_point = QPointF((x)*size,y*size);
                }
                else if(m==up)
                {
                    direction =UP;
                    next_point = QPointF((x-1)*size,(y-1)*size);
                }
                else
                {
                    direction =DOWN;
                    next_point = QPointF((x-1)*size,(y+1)*size);
                }
            }
        }
        else
        {
            // state == DEATH;
            // 寻找路径到地图中心点的路径
            speed = MONSTER_DEATH_SPEED;
            int left,right,up,down;
            left = right = up = down = 999;

            int x = coordinate.x()/size;
            int y = coordinate.y()/size;

            // x,y 是否为整数坐标
            bool flag_x = 0;
            bool flag_y = 0;
            if(x*size==coordinate.x()) flag_x = 1;
            if(y*size==coordinate.y()) flag_y = 1;
            x++;

            if(!flag_x)
            {
                //那么智能左右移动
                left=home_map[x][y];
                if(x+1<28) right = home_map[x+1][y];
            }
            else if(!flag_y)
            {
                // 只能上下移动
                up = home_map[x][y];
                down = home_map[x][y+1];
            }
            else
            {
                // 正好在路口
                if(x-1>=0) left = home_map[x-1][y];
                if(x+1<30) right = home_map[x+1][y];
                if(y-1>=0) up = home_map[x][y-1];
                if(y+1<30) down = home_map[x][y+1];
            }

            int m = 0;
            m = min( min(left,right),min(up,down));

            if(m==left)
            {
                direction=LEFT;
                next_point = QPointF((x-2)*size,y*size);
            }
            else if(m == right)
            {
                direction = RIGHT;
                next_point = QPointF((x)*size,y*size);
            }
            else if(m==up)
            {
                direction =UP;
                next_point = QPointF((x-1)*size,(y-1)*size);
            }
            else
            {
                direction =DOWN;
                next_point = QPointF((x-1)*size,(y+1)*size);
            }
        }
        // 根据方向更新坐标
        switch(direction)
        {
        case RIGHT:
        {
            coordinate.setX(coordinate.x()+speed);
            if(coordinate.x()>=size*28) coordinate.setX(coordinate.x()-size*28);
            else if(coordinate.x()>next_point.x()) coordinate.setX(next_point.x());

            break;
        }
        case LEFT:
        {
            coordinate.setX(coordinate.x()-speed);
            if(coordinate.x()<0) coordinate.setX(28*size+coordinate.x());
            else if(coordinate.x()<next_point.x()) coordinate.setX(next_point.x());

            break;
        }
        case UP:
        {
            coordinate.setY(coordinate.y()-speed);
            if(coordinate.y()<next_point.y()) coordinate.setY(next_point.y());

            break;
        }
        case DOWN:
        {
            coordinate.setY(coordinate.y()+speed);
            if(coordinate.y()>next_point.y()) coordinate.setY(next_point.y());
            break;
        }
        }
        setPos(coordinate);
        update();
    }
//    for(int i = 0;i<map[0].size();i++)
//    {
//        for(int j = 0;j<map.size();j++)
//        {
//            if(map[j][i]<10) cout << 0;
//            cout << map[j][i] << " ";
//        }
//        cout <<endl;
//    }
    //然后前进
}

void monster::set_color(QColor c)
{
    color = c;
}

void monster::update_map(QPointF ball_coor)
{
    // 根据球的位置来画地图
    if(data(1)==0)
    {
        map = vector<vector<int>>(30,vector<int>(30,99));
        vector<vector<bool>> temp(30,vector<bool>(30,0));  // 记录某个节点是否已经计算；，吗你

        int x = (ball_coor.x()/size)+1;
        int y = ball_coor.y()/size;

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
                if(!temp[x][y]||map[x][y]>t)
                {
                    temp[x][y] = 1;
                    map[x][y]=t;

                    // 上下左右都推入栈中
                    if(x-1>=0&&!barrier_map[x-1][y])
                        stack.push_back(pair<int,int>(x-1,y));
                    if(x+1<30&&!barrier_map[x+1][y])
                        stack.push_back(pair<int,int>(x+1,y));
                    if(y-1>=0&&!barrier_map[x][y-1])
                        stack.push_back(pair<int,int>(x,y-1));
                    if(y+1<30&&!barrier_map[x][y+1])
                        stack.push_back(pair<int,int>(x,y+1));
                }
            }
            t++;
        }

        // 二次更新，判断坐标 -0.5*size，14 和 27.5*size,14 的大小，其中较大者值更正为较小者，并且重新迭代
        if(map[0][14]<map[29][14])
        {
            stack.push_back(pair<int,int>(29,14));
            t = map[0][14];
        }
        else if(map[0][14]>map[29][14])
        {
            stack.push_back(pair<int,int>(0,14));
            t = map[29][14];
        }

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
                if(!temp[x][y]||map[x][y]>t)
                {
                    temp[x][y] = 1;
                    map[x][y]=t;

                    // 上下左右都推入栈中
                    if(x-1>=0&&!barrier_map[x-1][y])
                        stack.push_back(pair<int,int>(x-1,y));
                    if(x+1<30&&!barrier_map[x+1][y])
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
}

void monster::set_coordinate(QPointF p)
{
    coordinate = p;
}

void monster::escape_mode()
{
    t = 0;
    state = ESCAPE;
    //state_timer.setSingleShot(true);

    qDebug()<< QObject::connect(&state_timer,&QTimer::timeout,this,[=]
    {
        t+=0.1;
        if(t>=2.5&&t<6)
        {
            // 3秒之后， 在3.5  4.5  5.5 分别闪烁，每次闪烁时间0.5秒
            // 5.5秒
            if((t>=3.5&&t<3.7)||(t>=4.5&&t<4.7)||(t>=5.5&&t<5.7))
            {
                // 设置状态
                state = ESCAPE_FLASH;
            }
            else state = ESCAPE;

        }
        else if(t>=6)
        {
            escape_mode_stop();
        }
    });

    state_timer.start(100);
}

void monster::escape_mode_stop()
{
    state_timer.disconnect();
    state = NORMAL;
    state_timer.stop();
}

void monster::set_state(STATE s)
{
    state = s;
}

void monster::state_timer_stop()
{
    state = NORMAL;
    state_timer.disconnect();
    state_timer.stop();
}

STATE monster::get_state()
{
    return state;
}
