#-------------------------------------------------
#
# Project created by QtCreator 2011-11-09T10:48:44
#
#-------------------------------------------------

QT       += core gui sql

TARGET = ImageSpy
TEMPLATE = app


SOURCES  += main.cpp                    \
            mainwindow.cpp              \
            histogram.cpp               \
            db.cpp \
    comparers.cpp \
    image_record.cpp

HEADERS  += mainwindow.h                \
            histogram.h                 \
            db.h                        \
            comparers.h \
    image_record.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.txt























