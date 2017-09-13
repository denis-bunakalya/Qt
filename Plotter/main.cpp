#include <mainwindow.h>
#include <model.h>
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Model model;

    if (argc < 3) {

        MainWindow mainWindow(&model);
        mainWindow.show();
        return a.exec();
    }

    QSize size = model.loadFromFile(argv[1]);
    QImage image(size.width(), size.height(), QImage::Format_RGB888);

    uchar* pubBuffer = image.bits();
    memset(pubBuffer, 255, image.byteCount());

    Lemniscate lemniscate(model.getX1(), model.getY1(), model.getX2(), model.getY2());
    lemniscate.draw(&image);

    return !image.save(QString(argv[2]), "PNG");
}
