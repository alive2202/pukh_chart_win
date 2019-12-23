#-------------------------------------------------
#
# Project created by QtCreator 2019-12-23T09:52:51
#
#-------------------------------------------------

QT       += core gui
QT+=opengl
LIBS += -lopengl32
QT+=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chart_win
TEMPLATE = app


SOURCES += main.cpp\
        chartshow.cpp \
    ChartGL.cpp \
    mousefilter.cpp \
    tthread.cpp

HEADERS  += chartshow.h \
    ChartGL.h \
    mousefilter.h \
    tthread.h

FORMS    += chartshow.ui

RESOURCES += \
    resources.qrc
