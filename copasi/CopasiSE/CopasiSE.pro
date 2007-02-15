# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiSE/CopasiSE.pro,v $ 
#   $Revision: 1.35 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2007/02/15 17:08:54 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.35 $ $Author: shoops $ $Date: 2007/02/15 17:08:54 $  
######################################################################

TEMPLATE = app

SRC_TARGET = CopasiSE

CONFIG -= qt

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

COPASI_LIBS += COPASISE

contains(BUILD_OS, WIN32) {
  CONFIG += console

  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
}

contains(BUILD_OS, Linux) {
  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
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
  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
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
