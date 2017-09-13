#include <mainwindow.h>
#include <model.h>
#include <QApplication>
#include <QTime>
#include <string.h>
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Model model;

    if (argc < 2) {

        MainWindow mainWindow(&model);
        mainWindow.show();
        return a.exec();

    } else if (strcmp(argv[1], "compare") == 0) {

        int numberOfCircles = atoi(argv[2]);
        QImage image(800, 600, QImage::Format_RGB888);
        Circle circle(0, 0, 20);

        qsrand(QTime::currentTime().msecsSinceStartOfDay());
        QTime timer;
        timer.start();

        for (int i = 0; i < numberOfCircles; i++) {

            circle.setX(qrand() % 20001 - 10000);
            circle.setY(qrand() % 20001 - 10000);
            circle.setR(qrand() % 10001);

            circle.draw(&image);
        }
        std::cout << "draw - " << timer.elapsed() << " ms \n";

        timer.restart();

        for (int i = 0; i < numberOfCircles; i++) {

            circle.setX(qrand() % 20001 - 10000);
            circle.setY(qrand() % 20001 - 10000);
            circle.setR(qrand() % 10001);

            circle.drawFromLines(&image);
        }
        std::cout << "drawFromLines - " << timer.elapsed() << " ms \n";
        std::cout.flush();
        return 0;
    }

    QSize size = model.loadFromFile(argv[1]);
    QImage image(size.width(), size.height(), QImage::Format_RGB888);

    uchar* pubBuffer = image.bits();
    memset(pubBuffer, 255, image.byteCount());

    Circle circle(model.getX(), model.getY(), model.getR());
    circle.draw(&image);

    return !image.save("image.png");
}
