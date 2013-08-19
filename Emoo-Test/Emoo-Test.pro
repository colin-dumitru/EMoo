#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T16:39:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testoperation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    testEntry.cpp \
    cpu/addtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    cpu/addtest.h
