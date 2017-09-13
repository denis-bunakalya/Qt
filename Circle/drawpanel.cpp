#include <drawpanel.h>
#include <circle.h>
#include <model.h>
#include <QVBoxLayout>

DrawPanel::DrawPanel() {

    circle = new Circle(Model::defaultX, Model::defaultY, Model::defaultR);

    groupBox = new QGroupBox("Draw Panel");
    groupBox->setStyleSheet("QGroupBox { border: 5px solid gray; border-radius: 10px; padding: 15px; } ");
    groupBoxLayout = new QVBoxLayout();

    canvas = new Canvas(circle);
    groupBoxLayout->addWidget(canvas);
    groupBox->setLayout(groupBoxLayout);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);
}

DrawPanel::~DrawPanel() {

    delete circle;
    delete canvas;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

QSize DrawPanel::getCanvasSize() {

    return canvas->size();
}

void DrawPanel::receiveX(int x) {

    circle->setX(x);
    canvas->repaint();
}

void DrawPanel::receiveY(int y) {

    circle->setY(y);
    canvas->repaint();
}

void DrawPanel::receiveR(int r) {

    circle->setR(r);
    canvas->repaint();
}
