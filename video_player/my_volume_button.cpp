#include "my_volume_button.h"
#include <QEvent>
#include <QPaintEvent>
#include <QRect>

my_volume_button::my_volume_button()
{

}

void my_volume_button::paintEvent(QPaintEvent *event)
{
    int x = rect().x();
    int y = rect().y();
    pos = QPointF(x,y);

    QPushButton::paintEvent(event);
}

QPointF my_volume_button::get_pos()
{
    return pos;
}
