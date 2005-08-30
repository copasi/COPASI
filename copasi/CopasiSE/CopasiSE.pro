######################################################################
# $Revision: 1.21 $ $Author: shoops $ $Date: 2005/08/30 15:39:33 $  
######################################################################

TEMPLATE = app

# CONFIG -= qt

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
         tss \
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
