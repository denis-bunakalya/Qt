#include <mainwindow.h>
#include <model.h>
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    Model model;    

    if (argc < 3) {
        MainWindow mainWindow(&model);
        mainWindow.show();        

        model.loadFromFile("sphere.json");
        return a.exec();
    }

    QSize size = model.loadFromFile(argv[1]);
    QImage image(size.width(), size.height(), QImage::Format_RGB888);

    uchar* pubBuffer = image.bits();
    memset(pubBuffer, 255, image.byteCount());

    Sphere sphere(model.getX(), model.getY(), model.getScale(), model.getFilter());
    sphere.setImage(model.getImage());
    sphere.draw(&image);

    return !image.save(QString(argv[2]), "PNG");
}
