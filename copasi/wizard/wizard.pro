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

contains(BUILD_OS, Linux){
    libCOPASIGUI.target   = ../lib/libCOPASIGUI.a
    libCOPASIGUI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASIGUI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASIGUI

    POST_TARGETDEPS += ../lib/libCOPASIGUI.a
     
}

contains(BUILD_OS, Darwin){
    libCOPASIGUI.target   = ../lib/libCOPASIGUI.a
    libCOPASIGUI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASIGUI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASIGUI

    POST_TARGETDEPS += ../lib/libCOPASIGUI.a
        
}   

                   
DISTFILES += wizard.dsp \
             help_html/figures/*.jpg \
             help_html/*.html
