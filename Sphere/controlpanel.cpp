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

    comboBoxFilter = new QComboBox();
    comboBoxFilter->addItem("nearest");
    comboBoxFilter->addItem("bilinear");

    groupBoxLayout->addWidget(comboBoxFilter);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);

    QObject::connect(controlX, SIGNAL(valueChanged(int)), this, SLOT(emitX(int)));
    QObject::connect(controlY, SIGNAL(valueChanged(int)), this, SLOT(emitY(int)));

    QObject::connect(controlScale, SIGNAL(valueChanged(int)), this, SLOT(emitScale(int)));
    QObject::connect(comboBoxFilter, SIGNAL(currentIndexChanged(int)), this, SLOT(emitFilter(int)));
}

ControlPanel::~ControlPanel() {

    delete controlX;
    delete controlY;

    delete controlScale;
    delete comboBoxFilter;

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

void ControlPanel::emitFilter(int value) {

    emit sendFilter(value);
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

void ControlPanel::setFilter(int value) {

    comboBoxFilter->setCurrentIndex(value);
}
