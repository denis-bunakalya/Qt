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

    fill = defaultFill;
    outline = defaultOutline;
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

void Model::receiveFill(bool value) {

    fill = value;
    emit sendFill(fill);
}

void Model::receiveOutline(bool value) {

    outline = value;
    emit sendOutline(outline);
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

bool Model::getFill() const {

    return fill;
}

bool Model::getOutline() const {

    return outline;
}

QList<QList<QVector<int>>>* Model::getFigures() {

    return &figures;
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

    receiveFill(doc.object()["fill"].toBool());
    receiveOutline(doc.object()["outline"].toBool());

    QJsonArray glyphs = doc.object()["glyphs"].toArray();
    figures.clear();

    for (auto figure : glyphs) {
        QList<QVector<int>> points;

        for (auto point : figure.toArray()) {
            QVector<int> newPoint(3);

            newPoint[0] = point.toObject()["position"].toObject()["x"].toInt();
            newPoint[1] = point.toObject()["position"].toObject()["y"].toInt();
            newPoint[2] = point.toObject()["oncurve"].toBool();

            points.append(newPoint);
        }
        figures.append(points);
    }
    emit sendFigures(&figures);

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
    docObject["fill"] = fill;
    docObject["outline"] = outline;

    QJsonArray glyphs;

    for (int i = 0; i < figures.size(); i++) {
        QJsonArray glyph;

        for (int j = 0; j < figures.at(i).size(); j++) {
            QJsonObject glyphPoint;

            QJsonObject pointPosition;
            pointPosition["x"] = /*(int) (*/figures[i][j][0]/* / scaleFactor)*/;
            pointPosition["y"] = /*(int) (*/figures[i][j][1]/* / scaleFactor)*/;

            glyphPoint["position"] = pointPosition;

            glyphPoint["oncurve"] = (bool) figures[i][j][2];
            glyph.append(glyphPoint);
        }
        glyphs.append(glyph);
    }

    docObject["glyphs"] = glyphs;

    QJsonObject panel;
    QJsonObject size;

    size["x"] = panelSize.width();
    size["y"] = panelSize.height();
    panel["size"] = size;

    docObject["panel"] = panel;

    QJsonDocument doc(docObject);
    file.write(doc.toJson());
}
