#include <circle.h>

Circle::Circle(int x, int y, int r)
    : x(x), y(y), r(r) {}

void Circle::draw(QImage* pBackBuffer) {

    int width = pBackBuffer->width();
    int height = pBackBuffer->height();

    QRgb color = qRgb(0, 200, 0);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            float xTemp = j - x - width / 2;
            float yTemp = i + y - height / 2;

            if (xTemp * xTemp + yTemp * yTemp <= r * r) {
                pBackBuffer->setPixel(j, i, color);
            }
        }
    }
}

void Circle::drawFromLines(QImage* pBackBuffer) {

    int width = pBackBuffer->width();
    int height = pBackBuffer->height();

    float centerX = width / 2 + x;
    float centerY = height / 2 - y;

    float firstH = cut(centerY - r, 0, height);
    float lastH = cut(centerY + r, 0, height);

    uchar* pubBuffer = pBackBuffer->bits();

    for (float h = firstH; h < lastH; h++) {

        float dy = centerY - h;
        float cos = dy / r;
        float dx = r * sqrt(1 - cos * cos);

        float jumpInLine = cut(centerX - dx, 0, width);

        memset(pubBuffer + (int) h * pBackBuffer->bytesPerLine() + (int) jumpInLine * 3,
               0,
               (int) (sizeof(uchar) * 3 * (int) cut(cut(centerX + dx, 0, 2 * dx), 0, width - jumpInLine)));
    }
}

void Circle::setX(int value) {

    x = value;
}

void Circle::setY(int value) {

    y = value;
}

void Circle::setR(int value) {

    r = value;
}

float Circle::cut(float value, float minValue, float maxValue) {

    if (value < minValue) {
        return minValue;
    }
    if (value > maxValue) {
        return maxValue;
    }
    return value;
}



