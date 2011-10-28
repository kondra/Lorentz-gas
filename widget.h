#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter painter;
    Helper *helper;
    int elapsed;
};

#endif
