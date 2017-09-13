#include <model.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSize>
#include <QVector>
#include <QJsonArray>

Model::Model() {

    x = defaultX;
    y = defaultY;

    scale = defaultScale;
    filter = defaultFilter;
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

void Model::receiveScale(int value) {

    if ((value >= minScale) && (value <= maxScale)) {
        scale = value;
    }
    emit sendScale(scale);
}

void Model::receiveFilter(int value) {

    filter = value;
    emit sendFilter(filter);
}

int Model::getX() const {

    return x;
}

int Model::getY() const {

    return y;
}

int Model::getScale() const {

    return scale;
}

int Model::getFilter() const {

    return filter;
}

QImage* Model::getImage() {

    return &image;
}

void Model::loadImage(QString fileName) {

    image = QImage(fileName);
    emit sendImage(&image);
}

QSize Model::loadFromFile(QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject position = doc.object()["position"].toObject();

    receiveX(position["x"].toInt());
    receiveY(position["y"].toInt());
    receiveScale(doc.object()["scale"].toInt());

    QString filterType = doc.object()["filter"].toString();
    int type = (filterType == "bilinear") ? 1 : 0;
    receiveFilter(type);

    source = doc.object()["source"].toString();
    loadImage(source);

    QJsonObject panel = doc.object()["panel"].toObject();

    int width = panel["size"].toObject()["x"].toInt();
    if (width == 0) {
        width = 400;
    }
    int height = panel["size"].toObject()["y"].toInt();
    if (height == 0) {
        height = 485;
    }

    emit sendSize(width, height);
    return QSize(width, height);
}

void Model::saveToFile(QString fileName, QSize panelSize) {

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QJsonObject docObject;

    QJsonObject position;
    position["x"] = x;
    position["y"] = y;

    docObject["position"] = position;
    docObject["scale"] = scale;

    if (filter) {
        docObject["filter"] = "bilinear";
    } else {
        docObject["filter"] = "nearest";
    }

    docObject["source"] = source;

    QJsonObject panel;
    QJsonObject size;

    size["x"] = panelSize.width();
    size["y"] = panelSize.height();
    panel["size"] = size;

    docObject["panel"] = panel;

    QJsonDocument doc(docObject);
    file.write(doc.toJson());
}
