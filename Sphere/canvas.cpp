#include <canvas.h>
#include <QPainter>
#include <QImage>

Canvas::Canvas(Sphere* sphere) : sphere(sphere) {}

void Canvas::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    memset(pubBuffer, 255, backBuffer.byteCount());

    sphere->draw(&backBuffer);
    painter.drawImage(0,0, backBuffer);
}

void Canvas::mousePressEvent(QMouseEvent* event) {

    mousePressed = true;
    mouseX = event->x();
    mouseY = event->y();
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {

    if (mousePressed) {
        emit sendXY(sphere->getX() - event->x() + mouseX , sphere->getY() - event->y() + mouseY);

        mouseX = event->x();
        mouseY = event->y();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent*) {

    mousePressed = false;
}

