#include <lemniscate.h>

Lemniscate::Lemniscate(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

//void Lemniscate::draw(QImage* pBackBuffer) {

//    int width = pBackBuffer->width();
//    int height = pBackBuffer->height();

//    QRgb color = qRgb(0, 200, 0);

//    float rightSide = ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) / 4;
//    rightSide *= rightSide;

//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {

//            float x1Temp = j - x1 - width / 2;
//            float y1Temp = i + y1 - height / 2;

//            float x2Temp = j - x2 - width / 2;
//            float y2Temp = i + y2 - height / 2;

//            if ((((x1Temp * x1Temp + y1Temp * y1Temp) * (x2Temp * x2Temp + y2Temp * y2Temp) >= 0.95 * rightSide) &&
//                 ((x1Temp * x1Temp + y1Temp * y1Temp) * (x2Temp * x2Temp + y2Temp * y2Temp) <= 1.05 * rightSide)) ||
//                    ((x1Temp * x1Temp + y1Temp * y1Temp) <= 9) || ((x2Temp * x2Temp + y2Temp * y2Temp) <= 9)) {
//                pBackBuffer->setPixel(j, i, color);
//            }
//        }
//    }
//}

void Lemniscate::draw(QImage* pBackBuffer) {

    drawAxes(pBackBuffer);
    drawFocus(x1, y1, pBackBuffer);
    drawFocus(x2, y2, pBackBuffer);

    if ((abs(x1 - x2) <= 3) && (abs(y1 - y2) <= 3)) {
        return;
    }

    int centerX = (x1 + x2) >> 1;
    int centerY = (y1 + y2) >> 1;

    int currentX = centerX;
    int currentY = centerY;

    int lastDirectionX;
    int lastDirectionY;

    int firstDirectionX;
    int firstDirectionY;

    bool crossedCenter = false;
    bool justStarted = true;
    bool justCrossed = false;

    long long minError;
    long long currentError;

    int currentDirectionX;
    int currentDirectionY;

    int tryX;
    int tryY;

    int tryDirectionX;
    int tryDirectionY;

    while (true) {

        setPixel(currentX, currentY, pBackBuffer);
        minError = LONG_LONG_MAX;

        for (tryDirectionX = -1; tryDirectionX <= 1; tryDirectionX++) {
            for (tryDirectionY = -1; tryDirectionY <= 1; tryDirectionY++) {

                if (((tryDirectionX == 0) && (tryDirectionY == 0))
                        || ((!justStarted) && (tryDirectionX * lastDirectionX + tryDirectionY * lastDirectionY <= 0))) {
                    continue;
                }

                tryX = currentX + tryDirectionX;
                tryY = currentY + tryDirectionY;

                if (!justCrossed && !justStarted && ((abs(tryX - centerX) <= 1) && (abs(tryY - centerY) <= 1))) {

                    setPixel(tryX, tryY, pBackBuffer);
                    currentX = centerX;
                    currentY = centerY;

                    if (crossedCenter) {
                        return;
                    }
                    crossedCenter = true;
                    justCrossed = true;

                    minError = LONG_LONG_MAX;
                    lastDirectionX = centerX - tryX - firstDirectionX;
                    lastDirectionY = centerY - tryY - firstDirectionY;

                    tryDirectionX = -2;
                    break;
                }

                currentError = error(tryX, tryY);
                if (currentError < minError) {

                    minError = currentError;
                    currentDirectionX = tryDirectionX;
                    currentDirectionY = tryDirectionY;
                }
            }
        }

        lastDirectionX = currentDirectionX;
        lastDirectionY = currentDirectionY;

        if (justStarted) {

            firstDirectionX = currentDirectionX;
            firstDirectionY = currentDirectionY;
            justStarted = false;
        }

        if (justCrossed) {
            justCrossed = false;
        }

        currentX += currentDirectionX;
        currentY += currentDirectionY;
    }
}

long long Lemniscate::error(int x, int y) {

    long long dx1 = x - x1;
    long long dy1 = y - y1;

    long long dx2 = x - x2;
    long long dy2 = y - y2;

    long long dx12 = x1 - x2;
    long long dy12 = y1 - y2;

    long long rightSide = dx12 * dx12 + dy12 * dy12;
    rightSide *= rightSide;

    return llabs(16 * (dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) - rightSide);
}

void Lemniscate::drawAxes(QImage* pBackBuffer) {

    uchar* pubBuffer = pBackBuffer->bits();
    memset(pubBuffer + pBackBuffer->bytesPerLine() * (int) (pBackBuffer->height() >> 1), 0, pBackBuffer->bytesPerLine());

    pubBuffer += 3 * (int) (pBackBuffer->width() >> 1);
    for(int i = 0; i < pBackBuffer->height(); i++) {

        *pubBuffer = 0;
        *(pubBuffer + 1) = 0;
        *(pubBuffer + 2) = 0;

        pubBuffer += pBackBuffer->bytesPerLine();
    }
}

void Lemniscate::drawFocus(int x, int y, QImage* pBackBuffer) {

    setPixel(x - 1, y, pBackBuffer);
    setPixel(x + 1, y, pBackBuffer);
    setPixel(x, y + 1, pBackBuffer);
    setPixel(x, y - 1, pBackBuffer);
}

void Lemniscate::setPixel(int x, int y, QImage* pBackBuffer) {

    int canvasX = (pBackBuffer->width() >> 1) + x;
    int canvasY = (pBackBuffer->height() >> 1) - y;

    if ((canvasX >= 0) && (canvasX < pBackBuffer->width())
            && (canvasY >= 0) && (canvasY < pBackBuffer->height())) {

        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3) = 0;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 1) = 0;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 2) = 0;
    }
}

void Lemniscate::setX1(int value) {

    x1 = value;
}

void Lemniscate::setY1(int value) {

    y1 = value;
}

void Lemniscate::setX2(int value) {

    x2 = value;
}

void Lemniscate::setY2(int value) {

    y2 = value;
}
