#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

#include "helper.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Helper helper;
};

#endif
