#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject {

    Q_OBJECT

public:
    Model();

    int getX1() const;
    int getY1() const;

    int getX2() const;
    int getY2() const;

    static const int minX = -10000;
    static const int maxX = 10000;

    static const int defaultX1 = -100;
    static const int defaultX2 = 100;

    static const int minY = -10000;
    static const int maxY = 10000;
    static const int defaultY = 0;

    QSize loadFromFile(QString fileName);
    void saveToFile(QString fileName, QSize size);

signals:
    void sendX1(int);
    void sendY1(int);

    void sendX2(int);
    void sendY2(int);

    void sendSize(int, int);

public slots:
    void receiveX1(int value);
    void receiveY1(int value);

    void receiveX2(int value);
    void receiveY2(int value);

private:
    int x1;
    int y1;

    int x2;
    int y2;
};

#endif // MODEL_H
