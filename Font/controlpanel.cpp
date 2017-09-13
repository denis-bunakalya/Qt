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
    controlScale = new ControlWidget("Scale", Model::minScale, Model::maxScale, Model::defaultScale);

    groupBoxLayout->addWidget(controlX);
    groupBoxLayout->addWidget(controlY);
    groupBoxLayout->addWidget(controlScale);

    checkBoxFill = new QCheckBox("Fill", this);
    checkBoxOutline = new QCheckBox("Outline", this);

    groupBoxLayout->addWidget(checkBoxFill);
    groupBoxLayout->addWidget(checkBoxOutline);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);

    QObject::connect(controlX, SIGNAL(valueChanged(int)), this, SLOT(emitX(int)));
    QObject::connect(controlY, SIGNAL(valueChanged(int)), this, SLOT(emitY(int)));
    QObject::connect(controlScale, SIGNAL(valueChanged(int)), this, SLOT(emitScale(int)));

    QObject::connect(checkBoxFill, SIGNAL(stateChanged(int)), this, SLOT(emitFill(int)));
    QObject::connect(checkBoxOutline, SIGNAL(stateChanged(int)), this, SLOT(emitOutline(int)));
}

ControlPanel::~ControlPanel() {

    delete controlX;
    delete controlY;
    delete controlScale;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

void ControlPanel::emitX(int value) {

    emit sendX(value);
}

void ControlPanel::emitY(int value) {

    emit sendY(value);
}

void ControlPanel::emitScale(int value) {

    emit sendScale(value);
}

void ControlPanel::emitFill(int value) {

    emit sendFill((bool) value);
}

void ControlPanel::emitOutline(int value) {

    emit sendOutline((bool) value);
}

void ControlPanel::setX(int value) {

    controlX->setValue(value);
}

void ControlPanel::setY(int value) {

    controlY->setValue(value);
}

void ControlPanel::setScale(int value) {

    controlScale->setValue(value);
}

void ControlPanel::setFill(bool value) {

    checkBoxFill->setCheckState((Qt::CheckState) (value * 2));
}

void ControlPanel::setOutline(bool value) {

    checkBoxOutline->setCheckState((Qt::CheckState) (value * 2));
}
