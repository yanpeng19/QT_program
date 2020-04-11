#include "game_widget.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "game_map.h"
#include "game_view.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game_widget w;
    //w.begin();


    return a.exec();
}
