#ifndef MODEL_H
#define MODEL_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

class Model
{
public:
    Model();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void setDim(int w, int h);

private:
    void checkBorders(QPointF& p, qreal& phi);

    int width;
    int height;

    QBrush background;
    QBrush atomBrush;
    QBrush electronBrush;

    int num;
    QVector<qreal> speedDir;
    QVector<QPointF> positions;
};

#endif
