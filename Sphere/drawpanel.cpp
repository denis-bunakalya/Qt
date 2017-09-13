#include <drawpanel.h>
#include <sphere.h>
#include <model.h>
#include <QVBoxLayout>

DrawPanel::DrawPanel() {

    sphere = new Sphere(Model::defaultX, Model::defaultY, Model::defaultScale, Model::defaultFilter);

    groupBox = new QGroupBox("Draw Panel");
    groupBox->setStyleSheet("QGroupBox { border: 5px solid gray; border-radius: 10px; padding: 15px; } ");
    groupBoxLayout = new QVBoxLayout();

    canvas = new Canvas(sphere);
    QObject::connect(canvas, SIGNAL(sendXY(int, int)), this, SLOT(receiveXYFromCanvas(int,int)));

    groupBoxLayout->addWidget(canvas);
    groupBox->setLayout(groupBoxLayout);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);
}

DrawPanel::~DrawPanel() {

    delete sphere;
    delete canvas;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

QSize DrawPanel::getCanvasSize() {

    return canvas->size();
}

void DrawPanel::receiveX(int value) {

    sphere->setX(value);
    canvas->repaint();
}

void DrawPanel::receiveY(int value) {

    sphere->setY(value);
    canvas->repaint();
}

void DrawPanel::receiveScale(int value) {

    sphere->setScale(value);
    canvas->repaint();
}

void DrawPanel::receiveImage(QImage* value) {

    sphere->setImage(value);
    canvas->repaint();
}

void DrawPanel::receiveFilter(int value) {

    sphere->setFilter(value);
    canvas->repaint();
}

void DrawPanel::receiveXYFromCanvas(int x, int y) {

    emit sendX(x);
    emit sendY(y);
}
