######################################################################
# $Revision: 1.6 $ $Author: gauges $ $Date: 2006/10/15 06:17:50 $  
######################################################################

TEMPLATE = app

CONFIG -= qt

include(../copasi/common.pri)

DEPENDPATH += ../copasi/ 
INCLUDEPATH += ../copasi/

COPASI_LIBS += copasiDM 
COPASI_LIBS += copasiXML 
COPASI_LIBS += commandline 
COPASI_LIBS += elementaryFluxModes 
COPASI_LIBS += fitting 
COPASI_LIBS += function 
COPASI_LIBS += lyap 
COPASI_LIBS += optimization 
COPASI_LIBS += plot 
COPASI_LIBS += randomGenerator 
COPASI_LIBS += report 
COPASI_LIBS += sbmlimport 
COPASI_LIBS += scan 
COPASI_LIBS += steadystate 
COPASI_LIBS += trajectory 
COPASI_LIBS += tss 
COPASI_LIBS += odepack++ 
COPASI_LIBS += utilities                   

contains(DEFINES, COPASI_SENS) {
  COPASI_LIBS += sensitivities
}

COPASI_LIBS += model


contains(BUILD_OS, WIN32) {
  LIBS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../copasi/lib/", ../copasi/lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../copasi/lib \
         -Wl,--start-group \
         $$join(COPASI_LIBS, " -l", -l) \
         -Wl,--end-group \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../copasi/lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  COPASI_LIBS += randomGenerator
  COPASI_LIBS += function
  
  LIBS = $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a) \
         $${LIBS}
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../copasi/lib/lib", ../copasi/lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += copasi_wrapper.cpp
