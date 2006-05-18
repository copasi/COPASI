######################################################################
# $Revision: 1.5.16.1 $ $Author: shoops $ $Date: 2006/05/18 15:43:50 $  
######################################################################

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. 
INCLUDEPATH += ..
OBJECTS_DIR = .
DESTDIR = ../lib
TARGET = $$LIB

isEmpty(SRC_TARGET) {
  SRC_TARGET = $$LIB
}

