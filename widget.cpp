#include <QtGui>
#include "widget.h"
#include "helper.h"

static const int w = 400;
static const int h = 400;

Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    elapsed = 0;
    setFixedSize(w, h);
    helper->setDim(w, h);
}

void Widget::animate()
{
    elapsed = qobject_cast<QTimer*>(sender())->interval() % 1000;
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->paint(&painter, event, elapsed);
    painter.end();
}
