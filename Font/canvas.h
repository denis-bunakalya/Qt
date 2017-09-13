#ifndef CANVAS_H
#define CANVAS_H

#include <font.h>
#include <QWidget>
#include <QMouseEvent>

class Canvas : public QWidget {

    Q_OBJECT

public:
    Canvas(Font* font);

signals:
    void sendXY(int, int);

protected:
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent*);

private:
    Font* font;

    bool mousePressed;
    int mouseX;
    int mouseY;
};

#endif // CANVAS_H
