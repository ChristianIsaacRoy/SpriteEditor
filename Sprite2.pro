#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T13:19:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sprite2
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Cell.cpp \
    Model.cpp \
    ColorPreview.cpp \
    DrawingScene.cpp \
    FilmStripScene.cpp \
    FramePreview.cpp \
    DrawingGraphicsView.cpp \
    PreviewScene.cpp

HEADERS  += MainWindow.h \
    Cell.h \
    Model.h \
    ColorPreview.h \
    DrawingScene.h \
    FilmStripScene.h \
    FramePreview.h \
    DrawingGraphicsView.h \
    PreviewScene.h

FORMS    += \
    MainWindow.ui
