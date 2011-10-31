#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

#include "model.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Model model;
};

#endif
