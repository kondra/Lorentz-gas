#include <QtGui>
#include "widget.h"
#include "window.h"

#define NATIVE

static const int refresh_rate = 50;

Window::Window()
    : QWidget()
{
#ifdef NATIVE
    Widget *native = new Widget(&helper, this);
//    QLabel *nativeLabel = new QLabel(tr("Native"));
//    nativeLabel->setAlignment(Qt::AlignHCenter);
#else
    GLWidget *openGL = new GLWidget(&helper, this);
    QLabel *openGLLabel = new QLabel(tr("OpenGL"));
    openGLLabel->setAlignment(Qt::AlignHCenter);
#endif

    QGridLayout *layout = new QGridLayout;
#ifdef NATIVE
    layout->addWidget(native, 0, 0);
//    layout->addWidget(nativeLabel, 1, 0);
#else
    layout->addWidget(openGL, 0, 1);
    layout->addWidget(openGLLabel, 1, 1);
#endif
    setLayout(layout);

    QTimer *timer = new QTimer(this);
#ifdef NATIVE
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
#else
    connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
#endif
    timer->start(refresh_rate);

    setWindowTitle(tr("Physics"));
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
