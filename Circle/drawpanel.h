#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <circle.h>
#include <canvas.h>
#include <QGroupBox>

class DrawPanel : public QWidget {

    Q_OBJECT

public:
    DrawPanel();
    ~DrawPanel();

    QSize getCanvasSize();

public slots:
    void receiveX(int x);
    void receiveY(int y);
    void receiveR(int r);    

private:
    Circle* circle;
    Canvas* canvas;

    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;
};

#endif // DRAWPANEL_H
