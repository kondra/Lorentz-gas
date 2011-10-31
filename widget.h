#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class Model;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Model *model, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPainter painter;
    Model *model;
    int elapsed;
};

#endif
