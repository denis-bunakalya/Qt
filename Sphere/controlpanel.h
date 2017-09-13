#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <controlwidget.h>
#include <QGroupBox>
#include <QComboBox>

class ControlPanel : public QWidget {

    Q_OBJECT

public:
    ControlPanel();
    ~ControlPanel();

signals:
    void sendX(int);
    void sendY(int);

    void sendScale(int);
    void sendFilter(int);

public slots:    
    void emitX(int value);
    void emitY(int value);

    void emitScale(int value);
    void emitFilter(int value);

    void setX(int value);
    void setY(int value);

    void setScale(int value);
    void setFilter(int value);

private:
    QGroupBox* groupBox;
    QLayout* groupBoxLayout;
    QLayout* layout;

    ControlWidget* controlX;
    ControlWidget* controlY;

    ControlWidget* controlScale;
    QComboBox* comboBoxFilter;
};

#endif // CONTROLPANEL_H
