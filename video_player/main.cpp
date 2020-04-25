#include "mainwindow.h"
#include <QApplication>
#include "my_video_player.h"
#include "control_bar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    my_video_player w;
    w.show();

    return a.exec();
}
