#include <mainwindow.h>
#include <QFileDialog>

MainWindow::MainWindow(Model* model) : model(model) {

    window = new QWidget();
    drawPanel = new DrawPanel();

    controlPanel = new ControlPanel();

    windowLayout = new QGridLayout();
    window->setLayout(windowLayout);

    windowLayout->addWidget(drawPanel,0,0);
    windowLayout->addWidget(controlPanel,0,1);
    setCentralWidget(window);

    menu = new QMenuBar(this);
    fileMenu = new QMenu("File");

    loadFileAction = new QAction("Load", this);
    saveFileAction = new QAction("Save", this);

    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(saveFileAction);

    menu->addMenu(fileMenu);
    windowLayout->setMenuBar(menu);

    resize(800, 600);

    QObject::connect(controlPanel, SIGNAL(sendX1(int)), model, SLOT(receiveX1(int)));
    QObject::connect(controlPanel, SIGNAL(sendY1(int)), model, SLOT(receiveY1(int)));
    QObject::connect(controlPanel, SIGNAL(sendX2(int)), model, SLOT(receiveX2(int)));
    QObject::connect(controlPanel, SIGNAL(sendY2(int)), model, SLOT(receiveY2(int)));

    QObject::connect(model, SIGNAL(sendX1(int)), drawPanel, SLOT(receiveX1(int)));
    QObject::connect(model, SIGNAL(sendY1(int)), drawPanel, SLOT(receiveY1(int)));
    QObject::connect(model, SIGNAL(sendX2(int)), drawPanel, SLOT(receiveX2(int)));
    QObject::connect(model, SIGNAL(sendY2(int)), drawPanel, SLOT(receiveY2(int)));

    QObject::connect(model, SIGNAL(sendX1(int)), controlPanel, SLOT(setX1(int)));
    QObject::connect(model, SIGNAL(sendY1(int)), controlPanel, SLOT(setY1(int)));
    QObject::connect(model, SIGNAL(sendX2(int)), controlPanel, SLOT(setX2(int)));
    QObject::connect(model, SIGNAL(sendY2(int)), controlPanel, SLOT(setY2(int)));

    QObject::connect(model, SIGNAL(sendSize(int, int)), this, SLOT(receiveSize(int, int)));

    QObject::connect(loadFileAction, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow() {

    delete saveFileAction;
    delete loadFileAction;
    delete fileMenu;
    delete menu;

    delete controlPanel;
    delete drawPanel;
    delete windowLayout;
    delete window;
}

void MainWindow::loadFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Files (*.*)");
    if (fileName != NULL) {
        model->loadFromFile(fileName);
    }
}

void MainWindow::saveFile() {

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Files (*.*)");
    if (fileName != NULL) {
        model->saveToFile(fileName, drawPanel->getCanvasSize());
    }
}

void MainWindow::receiveSize(int width, int height) {

    resize(width + this->width() - drawPanel->getCanvasSize().width(),
           height + this->height() - drawPanel->getCanvasSize().height());
}
