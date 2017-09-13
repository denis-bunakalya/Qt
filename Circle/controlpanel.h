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
    void sendX(int);
    void sendY(int);
    void sendR(int);

public slots:    
    void emitX(int x);
    void emitY(int y);
    void emitR(int r);

    void setX(int x);
    void setY(int y);
    void setR(int r);

private:
    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;

    ControlWidget* controlX;
    ControlWidget* controlY;
    ControlWidget* controlR;
};

#endif // CONTROLPANEL_H
