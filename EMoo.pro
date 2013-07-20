#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T22:43:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = EMoo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cpu/cpu.cpp \
    mem/ram.cpp \
    mem/register16.cpp \
    common.cpp \
    machine.cpp

HEADERS += \
    cpu/cpu.h \
    mem/ram.h \
    config.h \
    mem/register16.h \
    machine.h
