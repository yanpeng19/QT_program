#include "my_video_player.h"
#include <QFileDialog>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QSizePolicy>
#include <QBoxLayout>
#include <QtGui>
#include <QPalette>

my_video_player::my_video_player(QWidget *parent):
    QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0,0,0,0));
    setPalette(pal);

    setMinimumSize(600,600);

    // 设置播放器及播放窗口
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    control_b = new control_bar(this,player);

    back_ground = new QWidget(this);
    back_ground->resize(width(),height()-80);
    back_ground->setStyleSheet("background-color:#334c7b");

    open = new QPushButton(back_ground);
    open->resize(120,120);
    open->move(back_ground->width()/2-80,back_ground->height()/2-60);
    open->setPalette(pal);
    open->setStyleSheet("QPushButton{background-image: url(D:/open_file_normal.svg);"
                        "background-repeat:no-repeat;"
                        "background-position:center;"
                        "background-color:transparent;}"
                        "QPushButton:hover{background-image: url(D:/open_file_selected.svg);}"
                        );

    connect(open,&QPushButton::clicked,[=]
    {
        // 简单选择一个视频文件进行加载,并且自动播放
        QString file_name = QFileDialog::getOpenFileName(this);
        if(!file_name.isEmpty())
        {
            videoWidget->resize(width(),height());
            player->setMedia(QUrl::fromLocalFile(file_name));
            player->play();
            back_ground->hide();
            control_b->hide();
        }
    });

    control_b->move(0,height()-80);
}

void my_video_player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        player->pause();
    }
    else if(event->key()==Qt::Key_Enter)
    {
        player->play();
    }
    else if(event->key()==Qt::Key_A)
        control_b->hide();
    else if(event->key()==Qt::Key_B)
        control_b->show();

    QWidget::keyPressEvent(event);
}

void my_video_player::resizeEvent(QResizeEvent *event)
{
    videoWidget->resize(event->size());
    auto h = event->size().height();
    auto w = event->size().width();

    control_b->move(0,h-80);
    control_b->resize(w,80);
    back_ground->resize(width(),height()-80);
    open->move(back_ground->width()/2-80,back_ground->height()/2-60);
}
