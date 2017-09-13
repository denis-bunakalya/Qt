#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T03:09:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Plotter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlpanel.cpp \
    drawpanel.cpp \
    lemniscate.cpp \
    controlwidget.cpp \
    canvas.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    drawpanel.h \
    lemniscate.h \
    controlwidget.h \
    controlpanel.h \
    canvas.h \
    model.h

FORMS    +=

CONFIG += c++11
