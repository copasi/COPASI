#TEMPLATE	= app
LANGUAGE	= C++

include(../lib.pri)

LIB= wizard
CONFIG	+= qt 

contains(BUILD_OS, Darwin) {
  INCLUDEPATH += /System/Library/Frameworks/Carbon.framework/Headers
}

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
                   


