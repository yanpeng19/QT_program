#ifndef MY_VOLUME_BUTTON_H
#define MY_VOLUME_BUTTON_H

#include <QPushButton>

class my_volume_button : public QPushButton
{
    Q_OBJECT
public:
    my_volume_button();
    void paintEvent(QPaintEvent* event);

    QPointF get_pos();
signals:

public slots:

private:
    QPointF pos;
};


#endif // MY_VOLUME_BUTTON_H
