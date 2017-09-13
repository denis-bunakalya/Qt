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

    QObject::connect(controlPanel, SIGNAL(sendX(int)), model, SLOT(receiveX(int)));
    QObject::connect(controlPanel, SIGNAL(sendY(int)), model, SLOT(receiveY(int)));

    QObject::connect(controlPanel, SIGNAL(sendScale(int)), model, SLOT(receiveScale(int)));
    QObject::connect(controlPanel, SIGNAL(sendFilter(int)), model, SLOT(receiveFilter(int)));

    QObject::connect(drawPanel, SIGNAL(sendX(int)), model, SLOT(receiveX(int)));
    QObject::connect(drawPanel, SIGNAL(sendY(int)), model, SLOT(receiveY(int)));

    QObject::connect(model, SIGNAL(sendX(int)), drawPanel, SLOT(receiveX(int)));
    QObject::connect(model, SIGNAL(sendY(int)), drawPanel, SLOT(receiveY(int)));

    QObject::connect(model, SIGNAL(sendScale(int)), drawPanel, SLOT(receiveScale(int)));
    QObject::connect(model, SIGNAL(sendFilter(int)), drawPanel, SLOT(receiveFilter(int)));

    QObject::connect(model, SIGNAL(sendX(int)), controlPanel, SLOT(setX(int)));
    QObject::connect(model, SIGNAL(sendY(int)), controlPanel, SLOT(setY(int)));

    QObject::connect(model, SIGNAL(sendScale(int)), controlPanel, SLOT(setScale(int)));
    QObject::connect(model, SIGNAL(sendFilter(int)), controlPanel, SLOT(setFilter(int)));

    QObject::connect(model, SIGNAL(sendImage(QImage*)),
                     drawPanel, SLOT(receiveImage(QImage*)));

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
