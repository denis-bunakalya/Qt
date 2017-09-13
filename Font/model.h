#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject {

    Q_OBJECT

public:
    Model();

    int getX() const;
    int getY() const;
    int getScale() const;

    bool getFill() const;
    bool getOutline() const;
    QList<QList<QVector<int>>>* getFigures();

    static const int minX = -1000;
    static const int maxX = 1000;
    static const int defaultX = 0;

    static const int minY = -1000;
    static const int maxY = 1000;
    static const int defaultY = 0;

    static const int minScale = -1000;
    static const int maxScale = 1000;
    static const int defaultScale = 0;

    static const bool defaultFill = true;
    static const bool defaultOutline = true;

    QSize loadFromFile(QString fileName);
    void saveToFile(QString fileName, QSize size);

signals:
    void sendX(int);
    void sendY(int);
    void sendScale(int);

    void sendFill(bool);
    void sendOutline(bool);

    void sendFigures(QList<QList<QVector<int>>>*);
    void sendSize(int, int);

public slots:
    void receiveX(int value);
    void receiveY(int value);
    void receiveScale(int value);

    void receiveFill(bool value);
    void receiveOutline(bool value);

private:
    int x;
    int y;
    int scale;

    bool fill;
    bool outline;
    QList<QList<QVector<int>>> figures;
};

#endif // MODEL_H
