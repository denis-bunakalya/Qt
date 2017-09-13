#include <drawpanel.h>
#include <font.h>
#include <model.h>
#include <QVBoxLayout>

DrawPanel::DrawPanel() {

    font = new Font(Model::defaultX, Model::defaultY, Model::defaultScale,
                    Model::defaultFill, Model::defaultOutline);

    groupBox = new QGroupBox("Draw Panel");
    groupBox->setStyleSheet("QGroupBox { border: 5px solid gray; border-radius: 10px; padding: 15px; } ");
    groupBoxLayout = new QVBoxLayout();

    canvas = new Canvas(font);
    QObject::connect(canvas, SIGNAL(sendXY(int, int)), this, SLOT(receiveXYFromCanvas(int,int)));

    groupBoxLayout->addWidget(canvas);
    groupBox->setLayout(groupBoxLayout);

    layout = new QVBoxLayout();
    layout->addWidget(groupBox);
    this->setLayout(layout);
}

DrawPanel::~DrawPanel() {

    delete font;
    delete canvas;

    delete groupBoxLayout;
    delete groupBox;
    delete layout;
}

QSize DrawPanel::getCanvasSize() {

    return canvas->size();
}

void DrawPanel::receiveX(int value) {

    font->setX(value);
    canvas->repaint();
}

void DrawPanel::receiveY(int value) {

    font->setY(value);
    canvas->repaint();
}

void DrawPanel::receiveScale(int value) {

    font->setScale(value);
    canvas->repaint();
}

void DrawPanel::receiveFill(bool value) {

    font->setFill(value);
    canvas->repaint();
}

void DrawPanel::receiveOutline(bool value) {

    font->setOutline(value);
    canvas->repaint();
}

void DrawPanel::receiveFigures(QList<QList<QVector<int>>>* value) {

    font->setFigures(value);
    canvas->repaint();
}

void DrawPanel::receiveXYFromCanvas(int x, int y) {

    emit sendX(x);
    emit sendY(y);
}
