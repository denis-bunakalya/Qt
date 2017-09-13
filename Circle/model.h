#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject {

    Q_OBJECT

public:
    Model();

    int getX() const;
    int getY() const;
    int getR() const;

    static const int minX = -10000;
    static const int maxX = 10000;
    static const int defaultX = 0;

    static const int minY = -10000;
    static const int maxY = 10000;
    static const int defaultY = 0;

    static const int minR = 0;
    static const int maxR = 10000;
    static const int defaultR = 20;

    QSize loadFromFile(QString fileName);
    void saveToFile(QString fileName, QSize size);

signals:
    void sendX(int);
    void sendY(int);
    void sendR(int);

    void sendSize(int, int);

public slots:
    void receiveX(int value);
    void receiveY(int value);
    void receiveR(int value);

private:
    int x;
    int y;
    int r;
};

#endif // MODEL_H
