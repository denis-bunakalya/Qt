#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <controlwidget.h>
#include <QGroupBox>

class ControlPanel : public QWidget {

    Q_OBJECT

public:
    ControlPanel();
    ~ControlPanel();

signals:
    void sendX1(int);
    void sendY1(int);

    void sendX2(int);
    void sendY2(int);

public slots:    
    void emitX1(int x1);
    void emitY1(int y1);

    void emitX2(int x2);
    void emitY2(int y2);

    void setX1(int x1);
    void setY1(int y1);

    void setX2(int x2);
    void setY2(int y2);

private:
    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;

    ControlWidget* controlX1;
    ControlWidget* controlY1;

    ControlWidget* controlX2;
    ControlWidget* controlY2;
};

#endif // CONTROLPANEL_H
