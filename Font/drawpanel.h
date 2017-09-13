#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <font.h>
#include <canvas.h>
#include <QGroupBox>

class DrawPanel : public QWidget {

    Q_OBJECT

public:
    DrawPanel();
    ~DrawPanel();

    QSize getCanvasSize();

signals:
    void sendX(int);
    void sendY(int);

public slots:
    void receiveX(int value);
    void receiveY(int value);
    void receiveScale(int value);

    void receiveFill(bool value);
    void receiveOutline(bool value);
    void receiveFigures(QList<QList<QVector<int>>>* value);

    void receiveXYFromCanvas(int x, int y);

private:
    Font* font;
    Canvas* canvas;

    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;
};

#endif // DRAWPANEL_H
