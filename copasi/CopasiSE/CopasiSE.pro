######################################################################
# $Revision: 1.29.2.4 $ $Author: shoops $ $Date: 2007/01/05 18:32:15 $  
######################################################################

TEMPLATE = app

SRC_TARGET = CopasiSE

# CONFIG -= qt

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

contains(DEFINES, COPASI_LICENSE_COM) {
  COPASI_LIBS += commercial
}

COPASI_LIBS += copasiDM
COPASI_LIBS += copasiXML
COPASI_LIBS += commandline
COPASI_LIBS += elementaryFluxModes
COPASI_LIBS += fitting
COPASI_LIBS += function
COPASI_LIBS += lyap
COPASI_LIBS += model
COPASI_LIBS += optimization
COPASI_LIBS += plot
COPASI_LIBS += randomGenerator
COPASI_LIBS += report
COPASI_LIBS += sbmlimport
COPASI_LIBS += scan
contains(DEFINES, COPASI_SENS) {
  COPASI_LIBS += sensitivities
}
COPASI_LIBS += steadystate
COPASI_LIBS += trajectory
COPASI_LIBS += tss
COPASI_LIBS += odepack++
COPASI_LIBS += utilities                   

contains(BUILD_OS, WIN32) {
  CONFIG += console

  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../lib \
         -Wl,--start-group \
         $$join(COPASI_LIBS, " -l", -l) \
         -Wl,--end-group \
         $${LIBS} \
         -lexpat

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  release {
    dynamic_LFLAGS = $${QMAKE_LFLAGS}
    dynamic_LFLAGS -= -static

    dynamic_LIBS = -Wl,-Bstatic $${LIBS} -Wl,-Bdynamic 
    dynamic.target   = CopasiSE-dynamic
    dynamic.depends  = $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${TARGETDEPS}
    dynamic.commands = \
      $(LINK) $${dynamic_LFLAGS} -L$(QTDIR)/lib -L/usr/X11R6/lib \
              -o $@ $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${dynamic_LIBS} \
              -Wl,--start-group -Wl,-Bstatic \
              -lm \
              -Wl,--end-group -Wl,-Bdynamic \
              -ldl -lpthread && \
              strip $@

    QMAKE_EXTRA_UNIX_TARGETS += dynamic

    distribution.extra = make $${dynamic.target};
  }
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
  
  COPASI_LIBS += randomGenerator
  COPASI_LIBS += function
  
  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}


# Input
HEADERS += 

SOURCES += CopasiSE.cpp

release {
  distribution.path = .
  distribution.file = CopasiSE

  INSTALLS += distribution
}

DISTFILES += CopasiSE.dsp
