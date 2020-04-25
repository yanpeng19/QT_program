#include "no_border_widget.h"
#include <QPainter>

no_border_widget::no_border_widget(QWidget *parent) : QWidget(parent)
{

}

void no_border_widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // QColor最后一个参数代表alpha通道，一般用作透明度
    painter.fillRect(rect(), QColor(50, 50, 50, 0));
}
