#include <controlpanel.h>
#include <controlwidget.h>
#include <model.h>

ControlPanel::ControlPanel() {

    this->setMaximumWidth(300);
    this->setMinimumWidth(300);

    groupBox = new QGroupBox("Control Panel");
    groupBox->setStyleSheet("QGroupBox { border: 5px solid gray; border-radius: 10px; padding: 15px } ");

    groupBoxLayout = new QVBoxLayout();
    groupBox->setLayout(groupBoxLayout);

    controlX1 = new ControlWidget("Position X1", Model::minX, Model::maxX, Model::defaultX1);
    controlY1 = new ControlWidget("Position Y1", Model::minY, Model::maxY, Model::defaultY);
    controlX2 = new ControlWidget("Position X2", Model::minX, Model::maxX, Model::defaultX2);
    controlY2 = new ControlWidget("Position Y2", Model::minY, Model::maxY, Model::defaultY);

    groupBoxLayout->addWidget(controlX1);
    groupBoxLayout->addWidget(controlY1);
    groupBoxLayout->addWidget(controlX2);
    groupBoxLayout->addWidget(controlY2);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);

    QObject::connect(controlX1, SIGNAL(valueChanged(int)), this, SLOT(emitX1(int)));
    QObject::connect(controlY1, SIGNAL(valueChanged(int)), this, SLOT(emitY1(int)));
    QObject::connect(controlX2, SIGNAL(valueChanged(int)), this, SLOT(emitX2(int)));
    QObject::connect(controlY2, SIGNAL(valueChanged(int)), this, SLOT(emitY2(int)));
}

ControlPanel::~ControlPanel() {

    delete controlX1;
    delete controlY1;
    delete controlX2;
    delete controlY2;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

void ControlPanel::emitX1(int x1) {

    emit sendX1(x1);
}

void ControlPanel::emitY1(int y1) {

    emit sendY1(y1);
}

void ControlPanel::emitX2(int x2) {

    emit sendX2(x2);
}

void ControlPanel::emitY2(int y2) {

    emit sendY2(y2);
}

void ControlPanel::setX1(int x1) {

    controlX1->setValue(x1);
}

void ControlPanel::setY1(int y1) {

    controlY1->setValue(y1);
}

void ControlPanel::setX2(int x2) {

    controlX2->setValue(x2);
}

void ControlPanel::setY2(int y2) {

    controlY2->setValue(y2);
}


