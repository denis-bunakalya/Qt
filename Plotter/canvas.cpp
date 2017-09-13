#include <canvas.h>
#include <QPainter>
#include <QImage>

Canvas::Canvas(Lemniscate* lemniscate) : lemniscate(lemniscate) {}

Canvas::~Canvas() {}

void Canvas::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    memset(pubBuffer, 255, backBuffer.byteCount());

    lemniscate->draw(&backBuffer);
    painter.drawImage(0,0, backBuffer);
}

