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
static const int n = 1;
static const qreal speed = 100;

Model::Model()
{
    background = QBrush(Qt::white);
    atomBrush = QBrush(Qt::black);
    electronBrush = QBrush(Qt::red);

    xBegin = (400 % side) / 2; //FIXME width
    yBegin = (400 % side) / 2; //FIXME height
    xBegin = xBegin ? xBegin : side;
    yBegin = yBegin ? yBegin : side;

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

void Model::checkAtom(QPointF& p, qreal& phi)
{
    qreal x = p.x();
    qreal y = p.y();
    qreal xC = floor(x / side) * side + xBegin;
    qreal yC = floor(y / side) * side + yBegin;

    qreal normalAngle = atan2(y - yC, x - xC);
    phi = 2 * normalAngle - phi + M_PI;
}

void Model::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    QPointF p;
    QRect rect = event->rect();
    painter->fillRect(rect, background);

    painter->save();

    painter->setBrush(atomBrush);
    for (int i = yBegin; i < rect.height(); i += side) {
        for (int j = xBegin; j < rect.width(); j += side) {
            p.ry() = i;
            p.rx() = j;
            painter->drawEllipse(p, atomR, atomR);
        }
    }

    painter->setBrush(electronBrush); 
    qreal s = speed * elapsed / 1000;
    QPointF p1, p2;

    for (int i = 0; i < num; i++) {
//        checkAtom(positions[i], speedDir[i]);

        p.rx() = cos(speedDir[i]) * s;
        p.ry() = sin(speedDir[i]) * s;
        p1 = positions[i];
        p2 = positions[i] += p;
        checkBorders(positions[i], speedDir[i]);
        painter->drawEllipse(positions[i], electronR, electronR);
    }

    painter->restore();
}
