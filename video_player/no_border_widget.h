#ifndef NO_BORDER_WIDGET_H
#define NO_BORDER_WIDGET_H

#include <QWidget>

class no_border_widget : public QWidget
{
    Q_OBJECT
public:
    explicit no_border_widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);
signals:

public slots:
};

#endif // NO_BORDER_WIDGET_H
