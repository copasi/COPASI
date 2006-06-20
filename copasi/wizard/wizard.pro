LANGUAGE	= C++

LIB= wizard

include(../lib.pri)
include(../common.pri)

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
                   
DISTFILES += wizard.dsp \
             help_html/figures/*.jpg \
             help_html/*.html
