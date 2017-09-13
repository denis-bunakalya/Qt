#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <controlwidget.h>
#include <QGroupBox>
#include <QCheckBox>

class ControlPanel : public QWidget {

    Q_OBJECT

public:
    ControlPanel();
    ~ControlPanel();

signals:
    void sendX(int);
    void sendY(int);
    void sendScale(int);

    void sendFill(bool);
    void sendOutline(bool);

public slots:    
    void emitX(int value);
    void emitY(int value);
    void emitScale(int value);

    void emitFill(int value);
    void emitOutline(int value);

    void setX(int value);
    void setY(int value);
    void setScale(int value);

    void setFill(bool value);
    void setOutline(bool value);

private:
    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;

    ControlWidget* controlX;
    ControlWidget* controlY;
    ControlWidget* controlScale;

    QCheckBox* checkBoxFill;
    QCheckBox* checkBoxOutline;
};

#endif // CONTROLPANEL_H
