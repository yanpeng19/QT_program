#include "control_bar.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QSlider>
#include <QDebug>
#include <QLabel>

control_bar::control_bar(QWidget *parent,QMediaPlayer* _player) : QWidget(parent)
{
    player = _player;
    is_play = 0;
    time_lenth  = 0;

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0,0,0,0));
    setPalette(pal);

    // 初始化和连接信号槽
    initialize();

    // 设置布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(play_button);
    layout->addWidget(time_slider);
    layout->addWidget(time);
    layout->addWidget(volume_button);


    if(parent)  resize(parent->height(),80);

    qDebug()<<mapToGlobal(volume_button->pos());
}

void control_bar::connect_play_button()
{
    // 播放按钮图标设置
    connect(player,&QMediaPlayer::stateChanged,this,[=](QMediaPlayer::State state)
    {
       if(state==QMediaPlayer::PlayingState)
       {
           // 进入播放状态，设置按钮图标
           play_button->setStyleSheet("QPushButton{background-image: url(D:/pause.svg);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center;"
                                      "background-color:transparent;}");
           is_play=1;
       }
       else
       {
           play_button->setStyleSheet("QPushButton{background-image: url(D:/play.svg);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center;"
                                      "background-color:transparent;}");
           is_play = 0;
       }
    });

    // 播放按钮按下
    connect(play_button,&QPushButton::clicked,this,[=]()
    {
       if(is_play)  player->pause();
       else player->play();
    });

    // 加载媒体源则重新获得时间总长度
    QObject::connect(player,&QMediaPlayer::durationChanged,this,[&](qint64 value)
    {
       qDebug()<< value;
       time_lenth = player->duration();
       qDebug()<<time_lenth;

       int m = time_lenth/1000/60;
       int s = (time_lenth-m*1000*60)/1000;
       total_time_lenth = QString("%1:%2").arg(m).arg(s);
       time->setText("00:00/"+total_time_lenth);

       time_slider->setMaximum(time_lenth/1000);
       time_slider->setValue(0);
    });

}

void control_bar::connect_time_line()
{
    // 时间条：  QMediaPlayer::positionChanged 毫秒为单位的信号
    // 设置时间 ： QMediaPlayer::setPosition(qint64 positon)
    // 连接 time_slider 时间条 和 视频源媒体的位置
    qDebug()<<connect(player,&QMediaPlayer::mediaChanged,this,[=]()
    {
        // 播放源更改， 修改视频长度，时间归零，以及标题
        QString title = player->metaData("Title").toString();
        parentWidget()->setWindowTitle(title);
    });

    qDebug()<< connect(player,&QMediaPlayer::positionChanged,this,[=](qint64 position)
    {
       time_slider->setValue(position/1000);
    });

    qDebug()<< connect(time_slider,&QSlider::valueChanged,this,[=](int value)
    {

        //时间条改动之后，设置当前时间
        int m = value/60;
        int s = (value-m*60);
        QString t;

        if(m<10) t+= '0';
        t+= QString::number(m);
        t+= ':';
        if(s<10) t+= '0';
        t+= QString::number(s);
        t+= '/';
        t+= total_time_lenth;

        time->setText(t);
    });

    //QSlider 拖动之后，调整时间帧
    qDebug()<< connect(time_slider,&QSlider::sliderMoved,this,[=](int value)
    {
        player->setPosition(value*1000);
    });
}

void control_bar::connect_volume_button()
{

}

void control_bar::initialize()
{
    // 初始化各种
    initialize_play_button();
    initialize_time_slider_label();
    initialize_volume();

    // 连接player 播放器 和 播放栏 各种信号槽

    // 连接播放按钮相关信号
    connect_play_button();

    // 设置播放时间Slider 相关信号
    connect_time_line();

    // 连接音量按钮相关信号
    connect_volume_button();
}

void control_bar::initialize_play_button()
{
    play_button = new QPushButton(this);

    play_button->setFixedSize(40,40);
    play_button->setStyleSheet("QPushButton{background-image: url(D:/play.svg);"
                               "background-repeat:no-repeat;"
                               "background-position:center;"
                               "background-color:transparent;}");
    play_button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void control_bar::initialize_time_slider_label()
{
    time_slider = new QSlider(Qt::Horizontal,this);
    time = new QLabel(this);
    time->setText("00:00/00:00");
    time->setStyleSheet("color:white;");
    time->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}

void control_bar::initialize_volume()
{
    volume_button = new QPushButton(this);
    volume_button->setFixedSize(40,40);
    volume_button->setStyleSheet("QPushButton{background-image: url(D:/volume.svg);"
                                 "background-repeat:no-repeat;"
                                 "background-position:center;"
                                 "background-color:transparent;}");
    volume_button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    volume_slider_widget = new no_border_widget();

    volume_slider_widget->setWindowFlags(Qt::FramelessWindowHint);
    //volume_slider_widget->setAttribute(Qt::WA_TranslucentBackground);

    volume_slider = new QSlider(Qt::Vertical,volume_slider_widget);
    volume_slider->resize(10,200);
    volume_slider->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    volume_slider_widget->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    volume_slider_widget->show();



    volume_slider_widget->move(mapToGlobal(volume_button->pos()));

//    QPalette pal = palette();
//    pal.setColor(QPalette::Background,QColor(0,0,0,0));
//    volume_slider_widget->setPalette(pal);
//    volume_slider_widget->setAttribute(Qt::WA_TranslucentBackground, true);
}
