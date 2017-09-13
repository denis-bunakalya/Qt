#include <font.h>
#include <cfloat>
#include <qmath.h>
#include <algorithm>

bool operator<(const QVector<int> v1, const QVector<int> v2) {
    return v1[0] < v2[0];
}

Font::Font(int x, int y, int scale, bool fill, bool outline)
    : x(x), y(y), scale(scale), fill(fill), outline(outline),
      unscaledFigures(NULL) {}

void Font::draw(QImage* pBackBuffer) {

    if (fill) {
        drawFill(pBackBuffer);
    }
    if (outline) {
        drawOutline(pBackBuffer);
    }
}

void Font::drawOutline(QImage *pBackBuffer) {

    int nextIndex;
    int nextNextIndex;

    for (int i = 0; i < figures.size(); i++){
        for (int j = 0; j < figures.at(i).size(); j++) {
            nextIndex = (j + 1) % figures.at(i).size();

            if (figures[i][j][2] && figures[i][nextIndex][2]) {

                drawLine(figures[i][j][0], figures[i][j][1],
                        figures[i][nextIndex][0], figures[i][nextIndex][1], pBackBuffer);

            } else if (figures[i][j][2]) {
                nextNextIndex = (nextIndex + 1) % figures.at(i).size();

                drawBezier(figures[i][j][0], figures[i][j][1],
                        figures[i][nextIndex][0], figures[i][nextIndex][1],
                        figures[i][nextNextIndex][0], figures[i][nextNextIndex][1], pBackBuffer);
            }
        }
    }
}

void Font::drawFill(QImage* pBackBuffer) {

    QList<QVector<float>> linesEquations;
    prepareLinesEquations(linesEquations);

    QList<QVector<float>> bezierEquations;
    prepareBezierEquations(bezierEquations);

    for (int y = - pBackBuffer->height() / 2 - this->y; y < pBackBuffer->height() / 2 - this->y; y++) {
        QList<QVector<int>> xs;

        addXsFromLines(y, linesEquations, xs);
        addXsFromBezier(y, bezierEquations, xs);

        std::sort(xs.begin(), xs.end());

        for (int i = 0; i < xs.size(); i += 2) {
            int x2 = xs.at(((i + 1) == xs.size()) ? i : i + 1)[0];

            for (int x = xs.at(i)[0]; x < x2; x++) {
                setPixel(x, y, 0, 0, 255, pBackBuffer);
            }
        }
    }
}

void Font::prepareLinesEquations(QList<QVector<float>>& linesEquations) {

    for (int i = 0; i < figures.size(); i++) {
        for (int j = 0; j < figures.at(i).size(); j++) {
            int nextIndex = (j + 1) % figures.at(i).size();

            if (figures[i][j][2] && figures[i][nextIndex][2]) {

                QVector<float> lineEquation(7);
                float Y1minusY2 = figures[i][j][1] - figures[i][nextIndex][1];

                if (Y1minusY2 == 0) {
                    lineEquation[0] = 0;

                    lineEquation[1] = figures[i][j][0];
                    lineEquation[2] = figures[i][nextIndex][0];

                    lineEquation[3] = figures[i][j][1];
                    lineEquation[4] = figures[i][nextIndex][1];

                } else {
                    lineEquation[0] = 1;

                    lineEquation[1] = (figures[i][j][0] - figures[i][nextIndex][0]) / Y1minusY2;
                    lineEquation[2] = (figures[i][nextIndex][0] * figures[i][j][1]
                            - figures[i][j][0] * figures[i][nextIndex][1]) / Y1minusY2;

                    lineEquation[3] = qMin(figures[i][j][1], figures[i][nextIndex][1]);
                    lineEquation[4] = qMax(figures[i][j][1], figures[i][nextIndex][1]);

                    lineEquation[5] = (figures[i][j][1] == lineEquation[3]) ? figures[i][j][0] : figures[i][nextIndex][1];
                    lineEquation[6] = (figures[i][j][0] == lineEquation[5]) ? figures[i][nextIndex][1] : figures[i][j][0];
                }
                linesEquations.append(lineEquation);
            }
        }
    }
}

void Font::addXsFromLines(int& y, QList<QVector<float>>& linesEquations, QList<QVector<int>>& xs) {

    for (int i = 0; i < linesEquations.size(); i++) {
        if ((y < linesEquations[i][3]) || (y > linesEquations[i][4])) {
            continue;
        }
        QVector<int> x(2);
        int pointType = 0;

        if (linesEquations[i][0] == 0) {

            x[0] = linesEquations[i][1];
            x[1] = 0;
            xs.append(x);

            x[0] = linesEquations[i][2];
            x[1] = 0;
            xs.append(x);

        } else {
            x[0] = roundf(y * linesEquations[i][1] + linesEquations[i][2]);

            if (x[0] == linesEquations[i][5]) {
                pointType = 1;

            } else if (x[0] == linesEquations[i][6]) {
                pointType = 2;
            }
            x[1] = (pointType == 1) ? 2 : 1;

            if ((pointType == 0) || !xs.contains(x)) {
                x[1] = pointType;
                xs.append(x);
            }
        }
    }
}

void Font::prepareBezierEquations(QList<QVector<float>>& bezierEquations) {

    for (int i = 0; i < figures.size(); i++) {
        for (int j = 0; j < figures.at(i).size(); j++) {

            int nextIndex = (j + 1) % figures.at(i).size();
            int nextNextIndex = (nextIndex + 1) % figures.at(i).size();

            if (figures[i][j][2] && !figures[i][nextIndex][2]) {
                QVector<float> bezierEquation(9);

                bezierEquation[0] = qMin(qMin(figures[i][j][1], figures[i][nextIndex][1]), figures[i][nextNextIndex][1]);
                bezierEquation[1] = qMax(qMax(figures[i][j][1], figures[i][nextIndex][1]), figures[i][nextNextIndex][1]);

                bezierEquation[2] = figures[i][j][0] - 2 * figures[i][nextIndex][0] + figures[i][nextNextIndex][0];
                bezierEquation[3] = 2 * (figures[i][nextIndex][0] - figures[i][j][0]);
                bezierEquation[4] = figures[i][j][0];

                bezierEquation[5] = figures[i][j][1] - figures[i][nextIndex][1];
                bezierEquation[6] = figures[i][j][1] - 2 * figures[i][nextIndex][1] + figures[i][nextNextIndex][1];

                bezierEquation[7] = figures[i][j][1];
                bezierEquation[8] = figures[i][nextNextIndex][1] - figures[i][nextIndex][1];

                bezierEquations.append(bezierEquation);
            }
        }
    }
}

void Font::addXsFromBezier(int& y, QList<QVector<float>>& bezierEquations, QList<QVector<int>>& xs) {

    for (int i = 0; i < bezierEquations.size(); i++) {

        float& minY = bezierEquations[i][0];
        float& maxY = bezierEquations[i][1];

        float& P0minus2P1plusP2X = bezierEquations[i][2];
        float& twoP1minus2P0X = bezierEquations[i][3];
        float& P0X = bezierEquations[i][4];

        float& P0minusP1Y = bezierEquations[i][5];
        float& P0minus2P1plusP2Y = bezierEquations[i][6];

        float& P0Y = bezierEquations[i][7];
        float& P2minusP1Y = bezierEquations[i][8];

        if ((y < minY) || (y > maxY)) {
            continue;
        }
        float tFromY;
        QVector<int> x(2);

        if (P0minus2P1plusP2Y != 0) {

            tFromY = (P0minusP1Y + sqrt(P0minusP1Y * P0minusP1Y - P0minus2P1plusP2Y * (P0Y - y))) / P0minus2P1plusP2Y;
            if ((tFromY >= 0) && (tFromY <= 1)) {

                x[0] = roundf(tFromY * tFromY * P0minus2P1plusP2X + tFromY * twoP1minus2P0X + P0X);
                appendXFromBezier(y, tFromY, P0minusP1Y, P0Y, x, xs);
            }

            tFromY = (P0minusP1Y - sqrt(P0minusP1Y * P0minusP1Y - P0minus2P1plusP2Y * (P0Y - y))) / P0minus2P1plusP2Y;
            if ((tFromY >= 0) && (tFromY <= 1)) {

                x[0] = roundf(tFromY * tFromY * P0minus2P1plusP2X + tFromY * twoP1minus2P0X + P0X);
                appendXFromBezier(y, tFromY, P0minusP1Y, P0Y, x, xs);
            }
        } else if (P0minusP1Y != 0) {
            tFromY = (P0Y - y) / (2 * P0minusP1Y);

            x[0] = roundf(tFromY * tFromY * P0minus2P1plusP2X + tFromY * twoP1minus2P0X + P0X);
            appendXFromBezier(y, tFromY, P0minusP1Y, P0Y, x, xs);

        } else if (P2minusP1Y != 0){
            tFromY = sqrt((y - P0Y) / P2minusP1Y);

            x[0] = roundf(tFromY * tFromY * P0minus2P1plusP2X + tFromY * twoP1minus2P0X + P0X);
            appendXFromBezier(y, tFromY, P0minusP1Y, P0Y, x, xs);

        } else {
            x[0] = P0X;
            x[1] = 0;
            xs.append(x);

            x[0] = P0minus2P1plusP2X + twoP1minus2P0X + P0X;
            xs.append(x);
        }
    }
}

void Font::appendXFromBezier(int& y, float& tFromY, float& P0minusP1Y, float& P0Y,
                             QVector<int>& x, QList<QVector<int>>& xs) {

    int pointType = 0;

    if ((tFromY == 0) || (tFromY == 1)) {
        pointType = (y < - P0minusP1Y + P0Y) ? 1 : 2;
    }
    x[1] = (pointType == 1) ? 2 : 1;

    if ((pointType == 0) || !xs.contains(x)) {
        x[1] = pointType;
        xs.append(x);
    }
}

void Font::drawLine(int x1, int y1, int x2, int y2, QImage* pBackBuffer) {

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;
    setPixel(x2, y2, 0, 0, 0, pBackBuffer);
    int error2;

    while(x1 != x2 || y1 != y2) {

        setPixel(x1, y1, 0, 0, 0, pBackBuffer);
        error2 = error << 2;

        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void Font::drawBezier(int x0, int y0, int x1, int y1, int x2, int y2, QImage *pBackBuffer) {

    if ((x0 == x1) && (x1 == x2) && (y0 == y1) && (y1 == y2)) {
        setPixel(x0, y0, 0, 0, 0, pBackBuffer);
        return;
    }

    if (((x0 == x1) && (x1 == x2)) || ((y0 == y1) && (y1 == y2))) {
        drawLine(x0, y0, x2, y2, pBackBuffer);
        return;
    }

    int P0minus2P1plusP2X = x0 - 2 * x1 + x2;
    int P0minus2P1plusP2Y = y0 - 2 * y1 + y2;

    int P0minusP1X = x0 - x1;
    int P0minusP1Y = y0 - y1;

    int P12minusP0P2X = x1 * x1 - x0 * x2;
    int P12minusP0P2Y = y1 * y1 - y0 * y2;

    int P2minusP1X = x2 - x1;
    int P2minusP1Y = y2 - y1;

    int currentX = x0;
    int currentY = y0;

    int lastDirectionX = x1 - x0;
    int lastDirectionY = y1 - y0;

    if ((lastDirectionX == 0) && (lastDirectionY == 0)) {
        lastDirectionX = x2 - x0;
        lastDirectionY = y2 - y0;
    }

    float minError;
    float tryError;

    int currentDirectionX;
    int currentDirectionY;

    int tryX;
    int tryY;

    int tryDirectionX;
    int tryDirectionY;

    while (true) {

        setPixel(currentX, currentY, 0, 0, 0, pBackBuffer);
        minError = FLT_MAX;

        for (tryDirectionX = -1; tryDirectionX <= 1; tryDirectionX++) {
            for (tryDirectionY = -1; tryDirectionY <= 1; tryDirectionY++) {

                if (((tryDirectionX == 0) && (tryDirectionY == 0))
                        || (tryDirectionX * lastDirectionX + tryDirectionY * lastDirectionY <= 0)) {
                    continue;
                }

                tryX = currentX + tryDirectionX;
                tryY = currentY + tryDirectionY;

                if ((abs(tryX - x2) < 1) && (abs(tryY - y2) < 1)) {

                    setPixel(tryX, tryY, 0, 0, 0, pBackBuffer);
                    setPixel(x2, y2, 0, 0, 0, pBackBuffer);
                    return;
                }

                tryError = errorFunction(tryX, tryY, P0minus2P1plusP2X, P0minus2P1plusP2Y,
                                         P0minusP1X, P0minusP1Y, P12minusP0P2X, P12minusP0P2Y,
                                         P2minusP1X, P2minusP1Y, x0, y0);

                if (tryError < minError) {

                    minError = tryError;
                    currentDirectionX = tryDirectionX;
                    currentDirectionY = tryDirectionY;
                }
            }
        }
        lastDirectionX = currentDirectionX;
        lastDirectionY = currentDirectionY;

        currentX += currentDirectionX;
        currentY += currentDirectionY;
    }
}

float Font::errorFunction(float tryX, float tryY, int P0minus2P1plusP2X, int P0minus2P1plusP2Y,
                          int P0minusP1X, int P0minusP1Y, int P12minusP0P2X, int P12minusP0P2Y,
                          int P2minusP1X, int P2minusP1Y, int x0, int y0) {

    float tFromX;
    if (P0minus2P1plusP2X != 0) {

        tFromX = (P0minusP1X + sqrt(tryX * P0minus2P1plusP2X + P12minusP0P2X)) / P0minus2P1plusP2X;

        if ((tFromX < 0) || (tFromX > 1)) {
            tFromX = (P0minusP1X - sqrt(tryX * P0minus2P1plusP2X + P12minusP0P2X)) / P0minus2P1plusP2X;
        }
    } else if (P0minusP1X != 0) {
        tFromX = (x0 - tryX) / (2 * P0minusP1X);

    } else {
        tFromX = sqrt((tryX - x0) / P2minusP1X);
    }

    float tFromY;
    if (P0minus2P1plusP2Y != 0) {

        tFromY = (P0minusP1Y + sqrt(tryY * P0minus2P1plusP2Y + P12minusP0P2Y)) / P0minus2P1plusP2Y;

        if ((tFromY < 0) || (tFromY > 1)) {
            tFromY = (P0minusP1Y - sqrt(tryY * P0minus2P1plusP2Y + P12minusP0P2Y)) / P0minus2P1plusP2Y;
        }
    } else if (P0minusP1Y != 0) {
        tFromY = (y0 - tryY) / (2 * P0minusP1Y);

    } else {
        tFromY = sqrt((tryY - y0) / P2minusP1Y);

    }

    return fabs(tFromX - tFromY);
}

void Font::setPixel(int x, int y, int r, int g, int b, QImage* pBackBuffer) {

    int canvasX = (pBackBuffer->width() >> 1) + this->x + x;
    int canvasY = (pBackBuffer->height() >> 1) - this->y - y;

    if ((canvasX >= 0) && (canvasX < pBackBuffer->width())
            && (canvasY >= 0) && (canvasY < pBackBuffer->height())) {

        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3) = r % 256;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 1) = g % 256;
        *(pBackBuffer->bits() + canvasY * pBackBuffer->bytesPerLine() + canvasX * 3 + 2) = b % 256;
    }
}

void Font::setX(int value) {

    x = value;
}

void Font::setY(int value) {

    y = value;
}

void Font::setScale(int value) {

    scale = value;
    scaleFigures();
}

void Font::setFill(int value) {

    fill = value;
}

void Font::setOutline(int value) {

    outline = value;
}

void Font::setFigures(QList<QList<QVector<int>>>* value) {

    unscaledFigures = value;
    scaleFigures();
}

int Font::getX() const {

    return x;
}

int Font::getY() const {

    return y;
}

void Font::scaleFigures() {

    if (unscaledFigures == NULL) {
        return;
    }

    figures.clear();
    float scaleFactor = (scale <= 0) ? 1 + (((float) scale) / 1000) : 1 + (((float) scale) / 100);

    for (int i = 0; i < unscaledFigures->size(); i++) {
        QList<QVector<int>> figure;

        for (int j = 0; j < unscaledFigures->at(i).size(); j++) {
            QVector<int> point(3);

            point[0] = (*unscaledFigures)[i][j][0] * scaleFactor;
            point[1] = (*unscaledFigures)[i][j][1] * scaleFactor;
            point[2] = (*unscaledFigures)[i][j][2];

            figure.append(point);
        }
        figures.append(figure);
    }
}
