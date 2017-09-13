#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <model.h>
#include <controlpanel.h>
#include <drawpanel.h>
#include <QMainWindow>
#include <QLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(Model * model);
    ~MainWindow();

public slots:
    void loadFile(void);
    void saveFile(void);
    void receiveSize(int width, int height);

private:
    QWidget* window;
    DrawPanel* drawPanel;
    ControlPanel* controlPanel;

    QGridLayout* windowLayout;
    Model* model;

    QMenuBar* menu;
    QMenu* fileMenu;
    QAction* saveFileAction;
    QAction* loadFileAction;
};

#endif // MAINWINDOW_H
