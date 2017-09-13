#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <lemniscate.h>
#include <canvas.h>
#include <QGroupBox>

class DrawPanel : public QWidget {

    Q_OBJECT

public:
    DrawPanel();
    ~DrawPanel();

    QSize getCanvasSize();

public slots:
    void receiveX1(int x1);
    void receiveY1(int y1);

    void receiveX2(int x2);
    void receiveY2(int y2);

private:
    Lemniscate* lemniscate;
    Canvas* canvas;

    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;
};

#endif // DRAWPANEL_H
