#ifndef CANVAS_H
#define CANVAS_H

#include <lemniscate.h>
#include <QWidget>

class Canvas : public QWidget {

public:
    Canvas(Lemniscate* lemniscate);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent*);

private:
    Lemniscate* lemniscate;
};

#endif // CANVAS_H
