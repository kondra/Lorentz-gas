#include <QtGui>
#include "widget.h"
#include "model.h"

static const int w = 400;
static const int h = 400;

Widget::Widget(Model *model, QWidget *parent)
    : QWidget(parent), model(model)
{
    elapsed = 0;
    setFixedSize(w, h);
    model->setDim(w, h);
}

void Widget::animate()
{
    elapsed = qobject_cast<QTimer*>(sender())->interval() % 1000;
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    model->paint(&painter, event, elapsed);
    painter.end();
}
