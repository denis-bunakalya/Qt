#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>

class Model : public QObject {

    Q_OBJECT

public:
    Model();

    int getX() const;
    int getY() const;

    int getScale() const;
    int getFilter() const;

    QImage* getImage();

    static const int minX = -1000;
    static const int maxX = 1000;
    static const int defaultX = 0;

    static const int minY = -1000;
    static const int maxY = 1000;
    static const int defaultY = 0;

    static const int minScale = -1000;
    static const int maxScale = 1000;
    static const int defaultScale = 0;

    static const bool defaultFilter = 0;

    QSize loadFromFile(QString fileName);
    void saveToFile(QString fileName, QSize size);

    void loadImage(QString fileName);

signals:
    void sendX(int);
    void sendY(int);

    void sendScale(int);
    void sendFilter(int);

    void sendImage(QImage*);
    void sendSize(int, int);

public slots:
    void receiveX(int value);
    void receiveY(int value);

    void receiveScale(int value);
    void receiveFilter(int value);

private:
    int x;
    int y;

    int scale;    
    int filter;

    QImage image;
    QString source;
};

#endif // MODEL_H
