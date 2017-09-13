#include <canvas.h>
#include <QPainter>
#include <QImage>

Canvas::Canvas(Circle* circle) : circle(circle) {}

Canvas::~Canvas() {}

void Canvas::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    memset(pubBuffer, 255, backBuffer.byteCount());

    circle->drawFromLines(&backBuffer);
    painter.drawImage(0,0, backBuffer);
}

