#-------------------------------------------------
#
# Project created by QtCreator 2011-11-09T10:48:44
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ImageSpy
TEMPLATE = app


SOURCES += main.cpp       \
           mainwindow.cpp \
           histogram.cpp  \
           db.cpp \
    abstracthistcomparer.cpp \
    manhatanhistcomparer.cpp

HEADERS  += mainwindow.h \
            histogram.h  \
            db.h \
    abstracthistcomparer.h \
    manhatanhistcomparer.h \
    comparers.h

FORMS    += mainwindow.ui









