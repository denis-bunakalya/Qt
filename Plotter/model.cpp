#include <model.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSize>

Model::Model() {

    x1 = defaultX1;
    y1 = defaultY;

    x2 = defaultX2;
    y2 = defaultY;
}

void Model::receiveX1(int value) {

    if ((value >= minX) && (value <= maxX)) {
        x1 = value;
    }
    emit sendX1(x1);
}

void Model::receiveY1(int value) {

    if ((value >= minY) && (value <= maxY)) {
        y1 = value;
    }
    emit sendY1(y1);
}

void Model::receiveX2(int value) {

    if ((value >= minX) && (value <= maxX)) {
        x2 = value;
    }
    emit sendX2(x2);
}

void Model::receiveY2(int value) {

    if ((value >= minY) && (value <= maxY)) {
        y2 = value;
    }
    emit sendY2(y2);
}

int Model::getX1() const {

    return x1;
}
int Model::getY1() const {

    return y1;
}

int Model::getX2() const {

    return x2;
}
int Model::getY2() const {

    return y2;
}

QSize Model::loadFromFile(QString fileName) {

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject lemniscate = doc.object()["lemniscate"].toObject();

    QJsonObject focus1 = lemniscate["focus1"].toObject();
    QJsonObject focus2 = lemniscate["focus2"].toObject();

    receiveX1(focus1["x"].toInt());
    receiveY1(focus1["y"].toInt());

    receiveX2(focus2["x"].toInt());
    receiveY2(focus2["y"].toInt());

    QJsonObject panel = doc.object()["panel"].toObject();

    int width = panel["size"].toObject()["x"].toInt();
    int height = panel["size"].toObject()["y"].toInt();

    emit sendSize(width, height);
    return QSize(width, height);
}

void Model::saveToFile(QString fileName, QSize panelSize) {

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QJsonObject lemniscate;

    QJsonObject focus1;
    focus1["x"] = x1;
    focus1["y"] = y1;

    QJsonObject focus2;
    focus2["x"] = x2;
    focus2["y"] = y2;

    lemniscate["focus1"] = focus1;
    lemniscate["focus2"] = focus2;

    QJsonObject panel;
    QJsonObject size;

    size["x"] = panelSize.width();
    size["y"] = panelSize.height();
    panel["size"] = size;

    QJsonObject docObject;
    docObject["lemniscate"] = lemniscate;
    docObject["panel"] = panel;

    QJsonDocument doc(docObject);
    file.write(doc.toJson());
}

