LANGUAGE	= C++

include(../lib.pri)
include(../common.pri)

LIB= wizard
CONFIG	+= qt 

unix {
  UI_DIR = .
  MOC_DIR = .
  OBJECTS_DIR = .
}

# FORMS	= wizard.ui

HEADERS += \
           wizard.h \
           wizard.ui.h
           
SOURCES += \
           wizard.cpp
                   


