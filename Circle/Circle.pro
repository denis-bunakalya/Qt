#-------------------------------------------------
#
# Project created by QtCreator 2015-02-15T03:09:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Circle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controlpanel.cpp \
    drawpanel.cpp \
    circle.cpp \
    controlwidget.cpp \
    canvas.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    drawpanel.h \
    circle.h \
    controlwidget.h \
    controlpanel.h \
    canvas.h \
    model.h

FORMS    +=

CONFIG += c++11
