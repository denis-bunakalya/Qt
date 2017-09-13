#include <sphere.h>
#include <qmath.h>
#include <QColor>

Sphere::Sphere(int x, int y, int scale, int filter)
    : x(x), y(y), scale(scale), filter(filter), image(NULL) {}

void Sphere::draw(QImage* pBackBuffer) {

    if ((image == NULL) || (image->isNull())) {
        return;
    }

    int width = pBackBuffer->width();
    int height = pBackBuffer->height();

    float scaleFactor = (scale <= 0) ? 1 + (((float) scale) / 1000) : 1 + (((float) scale) / 100);
    float r = 256 * scaleFactor;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if ((i - height / 2) * (i - height / 2) + (j - width / 2) * (j - width / 2) >= r * r) {
                continue;
            }

            float teta = qAcos((float) (height / 2 - i) / r) * 180 / 3.14;

            int fullY = (teta + y) / 180;
            if (teta + y < 0) {
                fullY--;
            }

            float fi = qAcos((float) (width / 2 - j) / (qSin(teta * 3.14 / 180) * r)) * 180 / 3.14;

            int fullX = (fi + x) / 360;
            if (fi + x < 0) {
                fullX--;
            }

            float curX = (image->width() - 1) * ((fi + x) - fullX * 360) / 360;
            float curY = (image->height() - 1) * ((teta + y) - fullY * 180) / 180;

            if (!filter) {
                QRgb color = image->pixel(curX, curY);
                setPixel(j, i, qRed(color), qGreen(color), qBlue(color), pBackBuffer);

            } else {
                int nextX = curX + 1;
                float tX = curX - (int) curX;

                int nextY = curY + 1;
                float tY = curY - (int) curY;

                if ((tX < 0.5) && (curX != 0)) {

                    nextX = curX;
                    curX--;
                    tX += 0.5;

                } else {
                    tX -= 0.5;
                }

                if ((tY < 0.5) && (curY != 0)) {

                    nextY = curY;
                    curY--;
                    tY += 0.5;

                } else {
                    tY -= 0.5;
                }

                QRgb color = image->pixel(curX, curY);

                QRgb nextXColor = image->pixel(nextX, curY);
                QRgb nextYColor = image->pixel(curX, nextY);
                QRgb nextXYColor = image->pixel(nextX, nextY);

                setPixel(j, i,
                         (1 - tX) * (1 - tY) * qRed(color) + tX * (1 - tY) * qRed(nextXColor) + tY * (1 - tX) * qRed(nextYColor) + tX * tY * qRed(nextXYColor),
                         (1 - tX) * (1 - tY) * qGreen(color) + tX * (1 - tY) * qGreen(nextXColor) + tY * (1 - tX) * qGreen(nextYColor) + tX * tY * qGreen(nextXYColor),
                         (1 - tX) * (1 - tY) * qBlue(color) + tX * (1 - tY) * qBlue(nextXColor) + tY * (1 - tX) * qBlue(nextYColor) + tX * tY * qBlue(nextXYColor),
                         pBackBuffer);
            }
        }
    }
}

void Sphere::setPixel(int canvasX, int canvasY, int r, int g, int b, QImage* pBackBuffer) {

    if ((canvasX >= 0) && (canvasX < pBackBuffer->width())
            && (canvasY >= 0) && (canvasY < pBackBuffer->height())) {

        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3) = r % 256;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 1) = g % 256;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 2) = b % 256;
    }
}

void Sphere::setX(int value) {

    x = value;
}

void Sphere::setY(int value) {

    y = value;
}

void Sphere::setScale(int value) {

    scale = value;
}

void Sphere::setFilter(int value) {

    filter = value;
}

void Sphere::setImage(QImage* value) {

    image = value;
}

int Sphere::getX() const {

    return x;
}

int Sphere::getY() const {

    return y;
}
