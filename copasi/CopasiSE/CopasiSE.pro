######################################################################
# $Revision: 1.16 $ $Author: shoops $ $Date: 2005/03/01 18:02:43 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

COPASI_LIBS = \
         commandline \
         copasiDM \
         copasiXML \
         elementaryFluxModes \
         function \
         mathmodel \
         model \
         optimization \
         plot \
         randomGenerator \
         report \
         sbmlimport \
         scan \
         steadystate \
         trajectory \
         utilities
         
          

contains(BUILD_OS, WIN32) {
  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../lib \
         -Wl,--start-group \
         $$join(COPASI_LIBS, " -l", -l) \
         -Wl,--end-group \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
         $$LIBS
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += CopasiSE.cpp
