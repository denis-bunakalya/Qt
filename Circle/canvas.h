#ifndef CANVAS_H
#define CANVAS_H

#include <circle.h>
#include <QWidget>

class Canvas : public QWidget {

public:
    Canvas(Circle* circle);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent*);

private:
    Circle* circle;
};

#endif // CANVAS_H
