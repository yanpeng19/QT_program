#ifndef CONTROL_BAR_H
#define CONTROL_BAR_H

#include <QWidget>
#include <QPushButton>
#include <QMediaPlayer>
#include <QSlider>
#include <QLabel>
#include <QMediaPlayer>
#include "no_border_widget.h"
#include "my_volume_button.h"

class control_bar : public QWidget
{
    Q_OBJECT
public:
    explicit control_bar(QWidget *parent = nullptr,QMediaPlayer *_player=nullptr);

    void connect_play_button();
    void connect_time_line();
    void connect_volume_button();

signals:

public slots:

private:    
    // 连接播放器和控制按钮的信号槽
    void initialize();
    void initialize_play_button();
    void initialize_time_slider_label();
    void initialize_volume();

    QMediaPlayer * player;

    //播放按钮 ，音量调节， slider 控制条， 时间 4个组件
    QPushButton * play_button;
    QPushButton * volume_button;
    QSlider * time_slider;

    QLabel * time;
    qint64 time_lenth;
    QString total_time_lenth;

    no_border_widget * volume_slider_widget;
    QSlider * volume_slider;
    bool is_play;
};

#endif // CONTROL_BAR_H
