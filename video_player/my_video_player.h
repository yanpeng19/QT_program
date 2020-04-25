#ifndef MY_VIDEO_PLAYER_H
#define MY_VIDEO_PLAYER_H

#include <QMediaPlayer>
#include <QWidget>
#include <QVideoWidget>
#include <QKeyEvent>
#include <QLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QBoxLayout>
#include <QMouseEvent>
#include "control_bar.h"


// 播放器类，基于QMediaPlyaer
//

class my_video_player :public QWidget
{
public:
    my_video_player(QWidget* parent = NULL);

public slots:

    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

    // 设置窗口标题，时间长度 信息
    void set_media_meta_mes();

private:
    // 基础内容
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    control_bar * control_b;

    QWidget * back_ground;
    QPushButton * open;
};

#endif // MY_VIDEO_PLAYER_H
