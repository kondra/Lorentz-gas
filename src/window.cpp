#include <QtGui>
#include "widget.h"
#include "window.h"

static const int refresh_rate = 50;

Window::Window()
    : QWidget()
{
    Widget *native = new Widget(&model, this);
#ifdef LABEL
    QLabel *nativeLabel = new QLabel(tr("Native"));
    nativeLabel->setAlignment(Qt::AlignHCenter);
#endif

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
#ifdef LABEL
    layout->addWidget(nativeLabel, 1, 0);
#endif
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
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
