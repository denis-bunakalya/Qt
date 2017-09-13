#ifndef LEMNISCATE_H
#define LEMNISCATE_H

#include <QImage>

class Lemniscate {

public:
    Lemniscate(int x1, int y1, int x2, int y2);
    void draw(QImage* pBackBuffer);

    void setX1(int value);
    void setY1(int value);

    void setX2(int value);
    void setY2(int value);

private:
    int x1;
    int y1;

    int x2;
    int y2;

    long long error(int x, int y);

    void drawAxes(QImage* pBackBuffer);
    void drawFocus(int x, int y, QImage* pBackBuffer);
    void setPixel(int x, int y, QImage* pBackBuffer);
};

#endif // LEMNISCATE_H
