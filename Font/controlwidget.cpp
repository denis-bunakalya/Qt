#include <controlwidget.h>

ControlWidget::ControlWidget(QString title, int min, int max, int defaultValue) {

    layout = new QGridLayout();
    label = new QLabel(title);

    spinBox = new QSpinBox();
    spinBox->setRange(min, max);
    spinBox->setValue(defaultValue);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(min, max);
    slider->setValue(defaultValue);

    layout->addWidget(label,0,0);
    layout->addWidget(spinBox,0,1);
    layout->addWidget(slider,1,0,1,2);

    this->setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

ControlWidget::~ControlWidget() {

    delete layout;
    delete label;
    delete slider;
    delete spinBox;
}

void ControlWidget::setValue(int value) {

    slider->setValue(value);
    spinBox->setValue(value);
}

