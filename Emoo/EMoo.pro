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

QMAKE_CXX = emcc
QMAKE_CC = emcc
QMAKE_LINK = emcc
QMAKE_CXXFLAGS += -O2 -std=c++0x -emit-llvm -c
QMAKE_LFLAGS += ASM_JS=1 -s TOTAL_MEMORY=50000000 -o EMoo.html

SOURCES += main.cpp \
    cpu/cpu.cpp \
    mem/ram.cpp \
    mem/register16.cpp \
    machine.cpp \
    common.cpp \
    cpu/interpreter.cpp \
    cpu/decoder.cpp \
    cpu/instruction.cpp

HEADERS += \
    cpu/cpu.h \
    mem/ram.h \
    config.h \
    mem/register16.h \
    machine.h\
    common.h \
    cpu/interpreter.h \
    cpu/decoder.h \
    cpu/instruction.h
