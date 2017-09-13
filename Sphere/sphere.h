#ifndef SPHERE_H
#define SPHERE_H

#include <QImage>

class Sphere {

public:
    Sphere(int x, int y, int scale, int filter);
    void draw(QImage* pBackBuffer);

    void setX(int value);
    void setY(int value);

    void setScale(int value);
    void setFilter(int value);

    void setImage(QImage* value);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;

    int scale;
    int filter;

    QImage* image;

    void setPixel(int canvasX, int canvasY, int r, int g, int b, QImage* pBackBuffer);
};

#endif // SPHERE_H
