######################################################################
# $Revision: 1.3 $ $Author: shoops $ $Date: 2003/05/19 12:45:54 $  
######################################################################

include(../common.pri)

TEMPLATE = lib

CONFIG -= qt 
CONFIG += staticlib

DEPENDPATH += .. 
INCLUDEPATH += ..
OBJECTS_DIR = .
DESTDIR = ../lib
TARGET = $${LIB}
