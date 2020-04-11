#include "game_map.h"

#include <QPainterPath>
#include <QPainter>
#include <QTransform>
#include <QVariant>
#include "const_data.h"
#include <QColor>

game_map::game_map()
{
    QPainterPath frame;

    //上半部分内部线条
    frame.moveTo(size/2,0);
    frame.arcTo(QRectF(0,0,size,size),90,90);

    frame.moveTo(0,0.5*size);
    frame.lineTo(0,8*size);
    frame.arcTo(QRectF(0*size,8*size,size,size),180,90);

    frame.moveTo(0.5*size,9*size);
    frame.lineTo(4.5*size,9*size);
    frame.moveTo(5*size,9.5*size);
    frame.arcTo(QRectF(4*size,9*size,size,size),0,90);

    frame.moveTo(5*size,9.5*size);
    frame.lineTo(5*size,12.5*size);
    frame.moveTo(4.5*size,13*size);
    frame.arcTo(QRectF(4*size,12*size,size,size),279,90);
    frame.moveTo(4.5*size,13*size);
    frame.lineTo(-0.5*size,13*size);

    frame.moveTo(0.5*size,0);
    frame.lineTo(12.5*size,0);
    frame.moveTo(13*size,0.5*size);
    frame.arcTo(QRectF(12*size,0,size,size),0,90);
    frame.moveTo(13*size,0.5*size);
    frame.lineTo(13*size,3.5*size);

    frame.moveTo(13*size,3.5*size);
    frame.arcTo(QRectF(13*size,3*size,size,size),180,180);
    frame.lineTo(14*size,0.5*size);

    frame.moveTo(14.5*size,0*size);
    frame.arcTo(QRectF(14*size,0,size,size),90,90);
    frame.moveTo(14.5*size,0*size);
    frame.lineTo(26.5*size,0);
    frame.moveTo(27*size,0.5*size);
    frame.arcTo(QRectF(26*size,0,size,size),0,90);
    frame.moveTo(27*size,0.5*size);

    frame.lineTo(27*size,8.5*size);
    frame.moveTo(26.5*size,9*size);
    frame.arcTo(QRectF(26*size,8*size,size,size),280,90);
    frame.moveTo(26.5*size,9*size);
    frame.lineTo(22.5*size,9*size);

    frame.moveTo(22.5*size,9*size);
    frame.arcTo(QRectF(22*size,9*size,size,size),90,90);
    frame.lineTo(22*size,12.5*size);

    frame.moveTo(22*size,12.5*size);
    frame.arcTo(QRectF(22*size,12*size,size,size),180,90);
    frame.lineTo(27.5*size,13*size);

    // 上半部分外圈线条
    frame.moveTo(27.5*size,(13-0.5)*size);
    frame.lineTo(23*size,(13-0.5)*size);

    frame.moveTo((22+0.5)*size,12*size);
    frame.arcTo(QRectF((22.5)*size,11.5*size,size,size),180,90);
    frame.moveTo((22+0.5)*size,12*size);
    frame.lineTo((22+0.5)*size,10*size);

    frame.moveTo(23*size,9.5*size);
    frame.arcTo(QRectF(22.5*size,9.5*size,size,size),90,90);
    frame.moveTo(23*size,9.5*size);
    frame.lineTo(27*size,9.5*size);

    frame.arcTo(QRectF(26.5*size,8.5*size,size,size),270,90);
    frame.lineTo(27.5*size,0*size);
    frame.arcTo(QRectF(26.5*size,-0.5*size,size,size),0,90);
    frame.lineTo(0*size,-0.5*size);
    frame.arcTo(QRectF(-0.5*size,-0.5*size,size,size),90,90);

    frame.lineTo(-0.5*size,9*size);
    frame.arcTo(QRectF(-0.5*size,8.5*size,size,size),180,90);
    frame.lineTo(4*size,9.5*size);

    frame.moveTo(4.5*size,10*size);
    frame.arcTo(QRectF(3.5*size,9.5*size,size,size),0,90);
    frame.moveTo(4.5*size,10*size);
    frame.lineTo(4.5*size,12*size);

    frame.moveTo(4*size,12.5*size);
    frame.arcTo(QRectF(3.5*size,11.5*size,size,size),270,90);
    frame.moveTo(4*size,12.5*size);
    frame.lineTo(-0.5*size,12.5*size);

    // 边框下半部分绘制
    frame.moveTo(-0.5*size,15*size);
    frame.lineTo(4.5*size,15*size);
    frame.moveTo(5*size,15.5*size);
    frame.arcTo(QRectF(4*size,15*size,size,size),0,90);
    frame.moveTo(5*size,15.5*size);
    frame.lineTo(5*size,18.5*size);
    frame.moveTo(4.5*size,19*size);
    frame.arcTo(QRectF(4*size,18*size,size,size),270,90);
    frame.moveTo(4.5*size,19*size);
    frame.lineTo(0.5*size,19*size);
    frame.arcTo(QRectF(0*size,19*size,size,size),90,90);
    frame.moveTo(0*size,19.5*size);
    frame.lineTo(0*size,23.5*size);
    frame.arcTo(QRectF(0*size,23*size,size,size),180,90);
    frame.lineTo(1.5*size,24*size);
    frame.moveTo(1.5*size,25*size);
    frame.arcTo(QRectF(1*size,24*size,1*size,size),270,180);
    frame.moveTo(1.5*size,25*size);
    frame.lineTo(0.5*size,25*size);
    frame.arcTo(QRect(0,25*size,size,size),90,90);
    frame.moveTo(0,25.5*size);
    frame.lineTo(0,29.5*size);
    frame.arcTo(QRectF(0,29*size,size,size),180,90);

    frame.moveTo(0.5*size,30*size);
    frame.lineTo(26.5*size,30*size);
    frame.arcTo(QRectF(26*size,29*size,size,size),270,90);

    frame.lineTo(27*size,25.5*size);
    frame.arcTo(QRect(26*size,25*size,size,size),0,90);
    frame.lineTo(25.5*size,25*size);
    frame.moveTo(25.5*size,24*size);
    frame.arcTo(QRectF(25*size,24*size,size,size),90,180);
    frame.moveTo(25.5*size,24*size);
    frame.lineTo(26.5*size,24*size);
    frame.arcTo(QRectF(26*size,23*size,size,size),270,90);
    frame.lineTo(27*size,19.5*size);
    frame.arcTo(QRectF(26*size,19*size,size,size),0,90);
    frame.lineTo(22.5*size,19*size);
    frame.moveTo(22*size,18.5*size);
    frame.arcTo(QRectF(22*size,18*size,size,size),180,90);
    frame.moveTo(22*size,18.5*size);
    frame.lineTo(22*size,15.5*size);
    frame.moveTo(22.5*size,15*size);
    frame.arcTo(QRectF(22*size,15*size,size,size),90,90);
    frame.moveTo(22.5*size,15*size);
    frame.lineTo(27.5*size,15*size);

    frame.moveTo(27.5*size,15.5*size);
    frame.lineTo(23*size,15.5*size);
    frame.arcTo(QRectF(22.5*size,15.5*size,size,size),90,90);
    frame.lineTo(22.5*size,18*size);
    frame.arcTo(QRectF(22.5*size,17.5*size,size,size),180,90);
    frame.lineTo(27*size,18.5*size);
    frame.moveTo(27.5*size,19*size);
    frame.arcTo(QRectF(26.5*size,18.5*size,size,size),0,90);
    frame.moveTo(27.5*size,19*size);
    frame.lineTo(27.5*size,30*size);
    frame.moveTo(27*size,30.5*size);
    frame.arcTo(QRectF(26.5*size,29.5*size,size,size),270,90);
    frame.moveTo(27*size,30.5*size);
    frame.lineTo(0*size,30.5*size);
    frame.moveTo(-0.5*size,30*size);
    frame.arcTo(QRectF(-0.5*size,29.5*size,size,size),180,90);
    frame.moveTo(-0.5*size,30*size);
    frame.lineTo(-0.5*size,19*size);
    frame.moveTo(0,18.5*size);
    frame.arcTo(QRectF(-0.5*size,18.5*size,size,size),90,90);

    frame.moveTo(0,18.5*size);
    frame.lineTo(4*size,18.5*size);
    frame.arcTo(QRectF(3.5*size,17.5*size,size,size),270,90);
    frame.lineTo(4.5*size,16*size);
    frame.arcTo(QRectF(3.5*size,15.5*size,size,size),0,90);
    frame.lineTo(-0.5*size,15.5*size);

    path.addPath(frame);


    // 上半部分图形
    path.addRoundedRect(QRectF(2*size,2*size,3*size,2*size),0.5*size,0.5*size);
    path.addRoundedRect(QRectF(7*size,2*size,4*size,2*size),0.5*size,0.5*size);
    path.addRoundedRect(QRectF(2*size,6*size,3*size,1*size),0.5*size,0.5*size);

    path.addRoundedRect(QRectF(16*size,2*size,4*size,2*size),0.5*size,0.5*size);
    path.addRoundedRect(QRectF(22*size,2*size,3*size,2*size),size/2,size/2);
    path.addRoundedRect(QRectF(22*size,6*size,3*size,size),size/2,size/2);

    // 下半部分图形
    path.addRoundedRect(QRectF(7*size,15*size,size,4*size),size/2,size/2);
    path.addRoundedRect(QRectF(7*size,21*size,4*size,size),size/2,size/2);
    path.addRoundedRect(QRectF(19*size,15*size,size,4*size),size/2,size/2);
    path.addRoundedRect(QRectF(16*size,21*size,4*size,size),size/2,size/2);

    // 上半场部分T
    // 画 T
    path.moveTo(8*size,6.5*size);
    path.arcTo(QRectF(7*size,6*size,size,size),0,180);
    path.lineTo(7*size,12.5*size);
    path.moveTo(7*size,12.5*size);
    path.arcTo(QRectF(7*size,12*size,size,size),180,180);
    path.lineTo(8*size,10.2*size);

    path.moveTo(8.2*size,10*size);
    path.arcTo(QRectF(8*size,10*size,0.4*size,0.4*size),90,90);
    path.moveTo(8.2*size,10*size);
    path.lineTo(10.5*size,10*size);
    path.arcTo(QRectF(10*size,9*size,size,size),270,180);
    path.lineTo(8.2*size,9*size);
    path.moveTo(8*size,8.8*size);
    path.arcTo(QRectF(8*size,8.6*size,0.4*size,0.4*size),180,90);
    path.moveTo(8*size,8.8*size);
    path.lineTo(8*size,6.5*size);

     // 中间的T
    path.moveTo(10.5*size,6*size);
    path.arcTo(QRectF(10*size,6*size,size,size),90,180);
    path.lineTo(12.8*size,7*size);
    path.moveTo(13*size,7.2*size);
    path.arcTo(QRectF(12.6*size,7*size,0.4*size,0.4*size),0,90);

    path.moveTo(13*size,7.2*size);
    path.lineTo(13*size,9.5*size);
    path.arcTo(QRectF(13*size,9*size,size,size),180,180);
    path.lineTo(14*size,7.2*size);
    path.moveTo(14.2*size,7*size);
    path.arcTo(QRectF(14*size,7*size,0.4*size,0.4*size),90,90);
    path.moveTo(14.2*size,7*size);
    path.lineTo(16.5*size,7*size);
    path.arcTo(QRectF(16*size,6*size,size,size),270,180);
    path.lineTo(10.5*size,6*size);


    // 右边的
    path.moveTo(16.5*size,9*size);
    path.arcTo(QRectF(16*size,9*size,size,size),90,180);
    path.lineTo(18.8*size,10*size);
    path.moveTo(19*size,10.2*size);
    path.arcTo(QRectF(18.6*size,10*size,0.4*size,0.4*size),0,90);
    path.moveTo(19*size,10.2*size);
    path.lineTo(19*size,12.5*size);
    path.arcTo(QRectF(19*size,12*size,size,size),180,180);
    path.lineTo(20*size,6.5*size);
    path.arcTo(QRectF(19*size,6*size,size,size),0,180);
    path.lineTo(19*size,8.8*size);
    path.moveTo(18.8*size,9*size);
    path.arcTo(QRectF(18.6*size,8.6*size,0.4*size,0.4*size),270,90);
    path.moveTo(18.8*size,9*size);
    path.lineTo(16.5*size,9*size);

    // 下半场非常规图形

    // 左上
    path.moveTo(2.5*size,21*size);
    path.arcTo(QRectF(2*size,21*size,size,size),90,180);
    path.lineTo(3.5*size,22*size);
    path.moveTo(4*size,23*size);
    path.arcTo(QRectF(3*size,22*size,size,size),0,90);
    path.moveTo(4*size,22.5*size);
    path.lineTo(4*size,24.5*size);
    path.arcTo(QRectF(4*size,24*size,size,size),180,180);
    path.lineTo(5*size,21.5*size);
    path.arcTo(QRectF(4*size,21*size,size,size),0,90);
    path.lineTo(2.5*size,21*size);

    //左下
    path.moveTo(2.5*size,27*size);
    path.arcTo(QRectF(2*size,27*size,size,size),90,180);
    path.lineTo(10.5*size,28*size);
    path.arcTo(QRect(10*size,27*size,size,size),270,180);
    path.lineTo(8.5*size,27*size);
    path.moveTo(8*size,26.5*size);
    path.arcTo(QRectF(8*size,26*size,size,size),180,90);
    path.moveTo(8*size,26.5*size);
    path.lineTo(8*size,24.5*size);
    path.arcTo(QRectF(7*size,24*size,size,size),0,180);
    path.lineTo(7*size,26.5*size);
    path.moveTo(6.5*size,27*size);
    path.arcTo(QRectF(6*size,26*size,size,size),270,90);
    path.moveTo(6.5*size,27*size);
    path.lineTo(2.5*size,27*size);

    // 右上
    path.moveTo(22*size,21.5*size);
    path.lineTo(22*size,24.5*size);
    path.arcTo(QRectF(22*size,24*size,size,size),180,180);
    path.lineTo(23*size,22.5*size);
    path.moveTo(23.5*size,22*size);
    path.arcTo(QRectF(23*size,22*size,size,size),90,90);
    path.moveTo(23.5*size,22*size);
    path.lineTo(24.5*size,22*size);
    path.arcTo(QRectF(24*size,21*size,size,size),270,180);
    path.lineTo(22.5*size,21*size);
    path.arcTo(QRectF(22*size,21*size,size,size),90,90);

    // 右下
    path.moveTo(16.5*size,28*size);
    path.lineTo(24.5*size,28*size);
    path.arcTo(QRectF(24*size,27*size,size,size),270,180);
    path.lineTo(20.5*size,27*size);
    path.moveTo(20*size,26.5*size);
    path.arcTo(QRectF(20*size,26*size,size,size),180,90);
    path.moveTo(20*size,26.5*size);
    path.lineTo(20*size,24.5*size);
    path.arcTo(QRectF(19*size,24*size,size,size),0,180);
    path.lineTo(19*size,26.5*size);
    path.moveTo(18.5*size,27*size);
    path.arcTo(QRectF(18*size,26*size,size,size),270,90);
    path.moveTo(18.5*size,27*size);
    path.lineTo(16.5*size,27*size);
    path.arcTo(QRectF(16*size,27*size,size,size),90,180);

    // 下半部分T*1
    path.moveTo(10.5*size,18*size);
    path.arcTo(QRect(10*size,18*size,size,size),90,180);
    path.lineTo(12.5*size,19*size);
    path.moveTo(13*size,19.5*size);
    path.arcTo(QRectF(12*size,19*size,size,size),0,90);
    path.moveTo(13*size,19.5*size);
    path.lineTo(13*size,21.5*size);
    path.arcTo(QRectF(13*size,21*size,size,size),180,180);
    path.lineTo(14*size,19.5*size);
    path.moveTo(14.5*size,19*size);
    path.arcTo(QRectF(14*size,19*size,size,size),90,90);
    path.moveTo(14.5*size,19*size);
    path.lineTo(16.5*size,19*size);
    path.arcTo(QRectF(16*size,18*size,size,size),270,180);
    path.lineTo(10.5*size,18*size);

    // 下半部分T*1
    path.moveTo(10.5*size,24*size);
    path.arcTo(QRect(10*size,24*size,size,size),90,180);
    path.lineTo(12.5*size,25*size);
    path.moveTo(13*size,25.5*size);
    path.arcTo(QRectF(12*size,25*size,size,size),0,90);
    path.moveTo(13*size,25.5*size);
    path.lineTo(13*size,27.5*size);
    path.arcTo(QRectF(13*size,27*size,size,size),180,180);
    path.lineTo(14*size,25.5*size);
    path.moveTo(14.5*size,25*size);
    path.arcTo(QRectF(14*size,25*size,size,size),90,90);
    path.moveTo(14.5*size,25*size);
    path.lineTo(16.5*size,25*size);
    path.arcTo(QRectF(16*size,24*size,size,size),270,180);
    path.lineTo(10.5*size,24*size);

    // 怪物房
    path.moveTo(12*size,12*size);
    path.lineTo(10*size,12*size);
    path.lineTo(10*size,16*size);
    path.lineTo(17*size,16*size);
    path.lineTo(17*size,12*size);
    path.lineTo(15*size,12*size);
    path.lineTo(15*size,12.5*size);
    path.lineTo(16.5*size,12.5*size);
    path.lineTo(16.5*size,12.5*size);
    path.lineTo(16.5*size,15.5*size);
    path.lineTo(10.5*size,15.5*size);
    path.lineTo(10.5*size,12.5*size);
    path.lineTo(12*size,12.5*size);
    path.lineTo(12*size,12*size);

    // 绘制边界path 通过添加rect
    bouding_path.addRect(QRectF(-0.5*size,-0.5*size,0.5*size,9.5*size));
    bouding_path.addRect(QRectF(-0.5*size,9*size,5.5*size,4*size));

    bouding_path.addRect(QRectF(0,-0.5*size,27.5*size,0.5*size));

    bouding_path.addRect(QRectF(13*size,0*size,size,4*size));
    bouding_path.addRect(QRectF(27*size,0,0.5*size,9*size));
    bouding_path.addRect(QRectF(22*size,9*size,5.5*size,4*size));
    bouding_path.addRect(QRectF(2*size,2*size,3*size,2*size));
    bouding_path.addRect(QRectF(7*size,2*size,4*size,2*size));
    bouding_path.addRect(QRectF(2*size,6*size,3*size,size));
    bouding_path.addRect(QRectF(16*size,2*size,4*size,2*size));
    bouding_path.addRect(QRectF(22*size,2*size,3*size,2*size));
    bouding_path.addRect(QRectF(7*size,6*size,size,7*size));
    bouding_path.addRect(QRectF(8*size,9*size,3*size,size));
    bouding_path.addRect(QRectF(10*size,6*size,7*size,size));
    bouding_path.addRect(QRectF(13*size,7*size,size,3*size));
    bouding_path.addRect(QRectF(16*size,9*size,3*size,size));
    bouding_path.addRect(QRectF(19*size,6*size,size,7*size));
    bouding_path.addRect(QRectF(22*size,6*size,3*size,size));

    bouding_path.addRect(QRectF(-0.5*size,15*size,5.5*size,4*size));
    bouding_path.addRect(QRectF(-0.5*size,19*size,0.5*size,11*size));
    bouding_path.addRect(QRectF(0,24*size,2*size,size));
    bouding_path.addRect(QRectF(-0.5*size,30*size,28*size,0.5*size));
    bouding_path.addRect(QRectF(22*size,15*size,5.5*size,4*size));
    bouding_path.addRect(QRectF(27*size,19*size,0.5*size,11*size));
    bouding_path.addRect(QRectF(25*size,24*size,2*size,size));
    bouding_path.addRect(QRectF(7*size,15*size,size,4*size));
    bouding_path.addRect(QRectF(2*size,21*size,3*size,size));
    bouding_path.addRect(QRectF(4*size,22*size,size,3*size));
    bouding_path.addRect(QRectF(7*size,21*size,4*size,size));
    bouding_path.addRect(QRectF(2*size,27*size,9*size,size));
    bouding_path.addRect(QRectF(7*size,24*size,size,3*size));
    bouding_path.addRect(QRectF(10*size,18*size,7*size,size));
    bouding_path.addRect(QRectF(13*size,19*size,size,3*size));
    bouding_path.addRect(QRectF(10*size,24*size,7*size,size));
    bouding_path.addRect(QRectF(13*size,25*size,size,3*size));
    bouding_path.addRect(QRectF(19*size,15*size,size,4*size));
    bouding_path.addRect(QRectF(16*size,21*size,4*size,size));
    bouding_path.addRect(QRectF(16*size,27*size,9*size,size));
    bouding_path.addRect(QRectF(19*size,24*size,size,3*size));
    bouding_path.addRect(QRectF(22*size,21*size,size,4*size));
    bouding_path.addRect(QRectF(23*size,21*size,size*2,size));

    bouding_path.addRect(QRectF(10*size,12*size,2*size,0.5*size));
    bouding_path.addRect(QRectF(15*size,12*size,2*size,0.5*size));
    bouding_path.addRect(QRectF(10*size,12.5*size,0.5*size,3.5*size));
    bouding_path.addRect(QRectF(16.5  *size,12.5*size,0.5*size,3.5*size));
    bouding_path.addRect(QRectF(10.5*size,15.5*size,6*size,0.5*size));

}

QPainterPath game_map::shape() const
{
    //返回地图边界
    // 使用Path
    return bouding_path;
}

QRectF game_map::boundingRect() const
{
    return QRectF(-size,-size,29*size,32*size);
}

void game_map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 实际画法
    QBrush b(QColor(24,45,152));
    QPen p(QColor(250,0,0));
    p.setBrush(b);
    p.setWidth(2);
    painter->setPen(p);
    painter->drawPath(path);

    //painter->setPen(QColor(Qt::red));
    //painter->drawPath(bouding_path);

}
