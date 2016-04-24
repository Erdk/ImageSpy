#-------------------------------------------------
#
# Project created by QtCreator 2011-11-09T10:48:44
#
#-------------------------------------------------

QT       += core sql widgets

TARGET = ImageSpy
TEMPLATE = app


SOURCES  += main.cpp                    \
            mainwindow.cpp              \
            histogram.cpp               \
            img_db.cpp                  \
            comparers.cpp

HEADERS  += mainwindow.hpp              \
            histogram.hpp               \
            img_db.hpp                  \
            comparers.hpp               \
            image_record.hpp

FORMS    += mainwindow.ui

OTHER_FILES += \
            README.md
