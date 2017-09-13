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

    controlX = new ControlWidget("Position X", Model::minX, Model::maxX, Model::defaultX);
    controlY = new ControlWidget("Position Y", Model::minY, Model::maxY, Model::defaultY);
    controlR = new ControlWidget("R", Model::minR, Model::maxR, Model::defaultR);

    groupBoxLayout->addWidget(controlX);
    groupBoxLayout->addWidget(controlY);
    groupBoxLayout->addWidget(controlR);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);

    QObject::connect(controlX, SIGNAL(valueChanged(int)), this, SLOT(emitX(int)));
    QObject::connect(controlY, SIGNAL(valueChanged(int)), this, SLOT(emitY(int)));
    QObject::connect(controlR, SIGNAL(valueChanged(int)), this, SLOT(emitR(int)));
}

ControlPanel::~ControlPanel() {

    delete controlX;
    delete controlY;
    delete controlR;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

void ControlPanel::emitX(int x) {

    emit sendX(x);
}

void ControlPanel::emitY(int y) {

    emit sendY(y);
}

void ControlPanel::emitR(int r) {

    emit sendR(r);
}

void ControlPanel::setX(int x) {

    controlX->setValue(x);
}

void ControlPanel::setY(int y) {

    controlY->setValue(y);
}

void ControlPanel::setR(int r) {

    controlR->setValue(r);
}


