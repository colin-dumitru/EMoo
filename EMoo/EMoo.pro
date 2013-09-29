#-------------------------------------------------
#
# Project created by QtCreator 2013-07-11T22:43:39
#
#-------------------------------------------------

emcc {
    message(Building for ASM.JS)
    include(EMoo-ASM.pri)

    OTHER_FILES += \
        EMoo-ASM.pri
}

QT       += core

QT       -= gui

TARGET = EMoo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    cpu/cpu.cpp \
    mem/ram.cpp \
    mem/register16.cpp \
    machine.cpp \
    common.cpp \
    cpu/interpreter.cpp \
    cpu/decoder.cpp \
    cpu/instruction.cpp \
    cpu/interrupthandler.cpp \
    io/porthandler.cpp \
    io/keyboard.cpp \
    io/ppi.cpp

HEADERS += \
    cpu/cpu.h \
    mem/ram.h \
    config.h \
    mem/register16.h \
    machine.h\
    common.h \
    cpu/interpreter.h \
    cpu/decoder.h \
    cpu/instruction.h \
    cpu/interrupthandler.h \
    io/porthandler.h \
    io/keyboard.h \
    io/ppi.h
