# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/CopasiUI.pro,v $ 
#   $Revision: 1.137 $ 
#   $Name:  $ 
#   $Author: urost $ 
#   $Date: 2007/02/26 10:31:09 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.137 $ $Author: urost $ $Date: 2007/02/26 10:31:09 $  
######################################################################

TEMPLATE = app

SRC_TARGET = CopasiUI

include(../common.pri)

DEPENDPATH += .. 
INCLUDEPATH += ..

COPASI_LIBS += COPASIUI
COPASI_LIBS += COPASISE

contains(BUILD_OS, WIN32) {
  RC_FILE = CopasiUI.rc
  
  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)

  release {
    distribution.extra = bash ../../admin/mkbuild.sh $${BUILD_OS}
  }
} 

contains(BUILD_OS, Linux) {
contains(DEFINES, WITH_LAYOUT) {
  CONFIG += opengl
  LIBS += -lfreetype -lglut
}
  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  LIBS += -Wl,-lqt-mt \
          -Wl,-lXcursor \
          -Wl,-lXft \
          -Wl,-lfontconfig \
          -Wl,-lpthread

  release {
    dynamic_LFLAGS = $${QMAKE_LFLAGS}
    dynamic_LFLAGS -= -static

    dynamic_LIBS = -Wl,-Bstatic $${LIBS} -Wl,-Bdynamic 
    dynamic_LIBS -= -Wl,-lqt-mt
    dynamic_LIBS -= -Wl,-lXcursor
    dynamic_LIBS -= -Wl,-lXft
    dynamic_LIBS -= -Wl,-lfontconfig
    dynamic_LIBS -= -Wl,-lpthread
 
    dynamic.target   = CopasiUI-dynamic
    dynamic.depends  = $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${TARGETDEPS}
    dynamic.commands = \
      $(LINK) $${dynamic_LFLAGS} -L$(QTDIR)/lib -L/usr/X11R6/lib \
              -o $@ $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${dynamic_LIBS} \
              -Wl,--start-group -Wl,-Bstatic \
              -lqt-mt -lXrender -lXrandr -lXcursor -lXinerama -lXft \ 
              -lfreetype -lfontconfig -lSM -lICE -lXext -lX11 -lm \
              -Wl,--end-group -Wl,-Bdynamic \
              -ldl -lpthread && \
              strip $@

    QMAKE_EXTRA_UNIX_TARGETS += dynamic

    distribution.extra = make $${dynamic.target}; \
                         ../../admin/mkbuild.sh $${BUILD_OS}

  }
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  LIBS += -lICE -ldl

  release {
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }
}  

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first
  
  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
         $$LIBS
  
  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  release {
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

# Input
HEADERS += resource.h 

SOURCES += main.cpp

release {
  distribution.path = .
  distribution.file = CopasiUI

  INSTALLS += distribution
}

DISTFILES += CopasiUI.dsp \
             CopasiUI.rc

