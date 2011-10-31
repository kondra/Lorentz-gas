#include <QtGui>
#include "model.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//hardcoded
static const int side = 25;
static const qreal atomR = 5;
static const qreal electronR = 2;

//user defined
static const int n = 50;
static const qreal speed = 100;

Model::Model()
{
    background = QBrush(Qt::white);
    atomBrush = QBrush(Qt::black);
    electronBrush = QBrush(Qt::red);

    num = n;
    int angle, x, y;
    for (int i = 0; i < num; i++) {
        //FIXME
        x = rand() % 400;
        y = rand() % 400;
        positions.append(QPointF(x, y));
        angle = rand() % 360;
        speedDir.append((M_PI / 360) * angle);
    }
}

void Model::setDim(int w, int h)
{
    width = w;
    height = h;
}

void Model::checkBorders(QPointF& p, qreal& phi)
{
    int h = height - electronR;
    int w = width - electronR;
    qreal y = p.y();
    qreal x = p.x();
    qreal dy = y - h;
    qreal dx = x - w;
    if (dy > 0) {
        p.ry() = h - dy;
        phi = 2 * M_PI - phi;
    }
    if (dx > 0) {
        p.rx() = w - dx;
        phi = 3 * M_PI - phi;
    }
    if (y < electronR) {
        p.ry() = 2 * electronR - y;
        phi = 2 * M_PI - phi;
    }
    if (x < electronR) {
        p.rx() = 2 * electronR - x;
        phi = 3 * M_PI - phi;
    }
}

void Model::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    QPointF p;
    QRect rect = event->rect();
    painter->fillRect(rect, background);

    painter->save();

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

    painter->setBrush(electronBrush); 
    qreal s;
    QPointF p1, p2;
    for (int i = 0; i < num; i++) {
        s = speed * elapsed / 1000;
        p.rx() = cos(speedDir[i]) * s;
        p.ry() = sin(speedDir[i]) * s;
        p1 = positions[i];
        p2 = positions[i] += p;
        checkBorders(positions[i], speedDir[i]);
        painter->drawEllipse(positions[i], electronR, electronR);
    }

    painter->restore();
}
