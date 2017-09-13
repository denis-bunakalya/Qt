#ifndef FONT_H
#define FONT_H

#include <QImage>

class Font {

public:
    Font(int x, int y, int scale, bool fill, bool outline);
    void draw(QImage* pBackBuffer);

    void setX(int value);
    void setY(int value);
    void setScale(int value);

    void setFill(int value);
    void setOutline(int value);
    void setFigures(QList<QList<QVector<int>>>* value);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
    int scale;

    bool fill;
    bool outline;

    QList<QList<QVector<int>>>* unscaledFigures;
    QList<QList<QVector<int>>> figures;

    void scaleFigures();
    void setPixel(int x, int y, int r, int g, int b, QImage* pBackBuffer);

    void drawOutline(QImage* pBackBuffer);
    void drawFill(QImage *pBackBuffer);

    void prepareLinesEquations(QList<QVector<float>>& linesEquations);
    void addXsFromLines(int& y, QList<QVector<float>>& linesEquations, QList<QVector<int>>& xs);

    void prepareBezierEquations(QList<QVector<float>>& bezierEquations);
    void addXsFromBezier(int& y, QList<QVector<float>>& bezierEquations, QList<QVector<int>>& xs);

    void appendXFromBezier(int& y, float& tFromY, float& P0minusP1Y, float& P0Y,
                           QVector<int>& x, QList<QVector<int>>& xs);

    void drawLine(int x1, int y1, int x2, int y2, QImage* pBackBuffer);
    void drawBezier(int x0, int y0, int x1, int y1, int x2, int y2,  QImage* pBackBuffer);

    float errorFunction(float tryX, float tryY, int P0minus2P1plusP2X, int P0minus2P1plusP2Y,
                        int P0minusP1X, int P0minusP1Y, int P12minusP0P2X, int P12minusP0P2Y,
                        int P2minusP1X, int P2minusP1Y, int x0, int y0);    
};

#endif // FONT_H
