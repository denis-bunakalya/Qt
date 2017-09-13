#include <drawpanel.h>
#include <lemniscate.h>
#include <model.h>
#include <QVBoxLayout>

DrawPanel::DrawPanel() {

    lemniscate = new Lemniscate(Model::defaultX1, Model::defaultY, Model::defaultX2, Model::defaultY);

    groupBox = new QGroupBox("Draw Panel");
    groupBox->setStyleSheet("QGroupBox { border: 5px solid gray; border-radius: 10px; padding: 15px; } ");
    groupBoxLayout = new QVBoxLayout();

    canvas = new Canvas(lemniscate);
    groupBoxLayout->addWidget(canvas);
    groupBox->setLayout(groupBoxLayout);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);
}

DrawPanel::~DrawPanel() {

    delete lemniscate;
    delete canvas;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

QSize DrawPanel::getCanvasSize() {

    return canvas->size();
}

void DrawPanel::receiveX1(int x1) {

    lemniscate->setX1(x1);
    canvas->repaint();
}

void DrawPanel::receiveY1(int y1) {

    lemniscate->setY1(y1);
    canvas->repaint();
}

void DrawPanel::receiveX2(int x2) {

    lemniscate->setX2(x2);
    canvas->repaint();
}

void DrawPanel::receiveY2(int y2) {

    lemniscate->setY2(y2);
    canvas->repaint();
}
