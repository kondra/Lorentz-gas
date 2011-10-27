#include <QtGui>
#include "helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static const int side = 25;
static const qreal atomR = 5;
static const qreal electronR = 2;

static const qreal speed = 150;

Helper::Helper()
{
    background = QBrush(Qt::white);
    atomBrush = QBrush(Qt::black);
    electronBrush = QBrush(Qt::red);

//    int x = rand() % width;
//    int y = rand() % height;
//    positions.append(QPointF(x, y));
//    speedDir.append((2 * M_PI) / rand());
    positions.append(QPointF(10, 200));
    speedDir.append(2 * M_PI - M_PI / 12);
    num = 1;
}

void Helper::setDim(int w, int h)
{
    width = w;
    height = h;
}

void Helper::checkBorders(QPointF& p, qreal& phi)
{
    qreal y = p.y();
    qreal x = p.x();
    qreal dy = y - height;
    qreal dx = x - width;
    if (dy > 0) {
        p.ry() = height - dy;
        phi = 2 * M_PI - phi;
    }
    if (dx > 0) {
        p.rx() = width - dx;
        if (phi < M_PI)
            phi = M_PI / 2 + phi;
        else
            phi = 3 * M_PI - phi;
    }
    if (y < 0) {
        p.ry() = -y;
    }
    if (x < 0) {
        p.rx() = -x;
        if (phi < M_PI)
            phi = M_PI - phi;
        else
            phi = 2 * M_PI - phi;
    }
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    QPointF p;
    QRect rect = event->rect();
    painter->fillRect(rect, background);

    painter->save();

    /*
    painter->setBrush(atomBrush);
    int iBegin = (rect.height() % side) / 2;
    int jBegin = (rect.width() % side) / 2;
    iBegin = iBegin ? iBegin : side;
    jBegin = jBegin ? jBegin : side;
    for (int i = iBegin; i < rect.height(); i += side) {
        for (int j = jBegin; j < rect.width(); j += side) {
            p.ry() = i;
            p.rx() = j;
            painter->drawEllipse(p, atomR, atomR);
        }
    }
    */

    painter->setBrush(electronBrush); 
    qreal s;
    for (int i = 0; i < num; i++) {
        s = speed * elapsed / 1000;
        p.rx() = cos(speedDir[i]) * s;
        p.ry() = sin(speedDir[i]) * s;
        positions[i] += p;
        checkBorders(positions[i], speedDir[i]);
        painter->drawEllipse(positions[i], electronR, electronR);
    }

    painter->restore();
}
