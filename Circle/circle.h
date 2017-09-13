#ifndef CIRCLE_H
#define CIRCLE_H

#include <QImage>

class Circle {

public:
    Circle(int x, int y, int r);
    void draw(QImage* pBackBuffer);
    void drawFromLines(QImage* pBackBuffer);

    void setX(int value);
    void setY(int value);
    void setR(int value);

private:
    int x;
    int y;
    int r;

    float cut(float value, float minValue, float maxValue);
};

#endif // CIRCLE_H
