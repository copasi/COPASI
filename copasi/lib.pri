include(../common.pri)

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. 
INCLUDEPATH += ..
OBJECTS_DIR = .
DESTDIR = ../lib
TARGET = $${LIB}
