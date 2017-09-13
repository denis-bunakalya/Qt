#include <model.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSize>

Model::Model() {

    x = defaultX;
    y = defaultY;
    r = defaultR;
}

void Model::receiveX(int value) {

    if ((value >= minX) && (value <= maxX)) {
        x = value;
    }
    emit sendX(x);
}

void Model::receiveY(int value) {

    if ((value >= minY) && (value <= maxY)) {
        y = value;
    }
    emit sendY(y);
}

void Model::receiveR(int value) {

    if ((value >= minR) && (value <= maxR)) {
        r = value;
    }
    emit sendR(r);
}

int Model::getR() const {

    return r;
}

int Model::getY() const {

    return y;
}

int Model::getX() const {

    return x;
}

QSize Model::loadFromFile(QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject circle = doc.object()["circle"].toObject();

    receiveR(circle["R"].toInt());
    receiveX(circle["position"].toObject()["x"].toInt());
    receiveY(circle["position"].toObject()["y"].toInt());

    QJsonObject panel = doc.object()["panel"].toObject();

    int width = panel["size"].toObject()["x"].toInt();
    int height = panel["size"].toObject()["y"].toInt();

    emit sendSize(width, height);
    return QSize(width, height);
}

void Model::saveToFile(QString fileName, QSize panelSize) {

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QJsonObject circle;
    circle["R"] = r;

    QJsonObject position;
    position["x"] = x;
    position["y"] = y;

    circle["position"] = position;

    QJsonObject panel;
    QJsonObject size;

    size["x"] = panelSize.width();
    size["y"] = panelSize.height();
    panel["size"] = size;

    QJsonObject docObject;
    docObject["circle"] = circle;
    docObject["panel"] = panel;

    QJsonDocument doc(docObject);
    file.write(doc.toJson());
}

