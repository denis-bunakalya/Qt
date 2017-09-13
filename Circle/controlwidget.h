#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>

class ControlWidget : public QWidget {

    Q_OBJECT

public:
    ControlWidget(QString title, int min, int max, int defaultValue);
    ~ControlWidget();

    void setValue(int value);

signals:
    void valueChanged(int);

private:
    QGridLayout* layout;
    QLabel* label;
    QSlider* slider;
    QSpinBox* spinBox;
};

#endif // CONTROLWIDGET_H
