#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T16:39:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = EMooTest
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    testEntry.cpp \
    cpu/addtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    cpu/addtest.h

unix:!macx: LIBS += -L"$$PWD/../build-EMoo-Desktop_Qt_5_0_2_GCC_64bit-Debug/" -lEMoo

INCLUDEPATH += $$PWD/../EMoo
DEPENDPATH += $$PWD/../EMoo
