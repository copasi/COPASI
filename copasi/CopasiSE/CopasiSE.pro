# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiSE/CopasiSE.pro,v $
#   $Revision: 1.40.2.3 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/03/03 18:09:54 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.40.2.3 $ $Author: shoops $ $Date: 2010/03/03 18:09:54 $
######################################################################

TEMPLATE = app

SRC_TARGET = CopasiSE

CONFIG -= qt

DEPENDPATH += ..
INCLUDEPATH += ..

# Input
HEADERS +=

SOURCES += CopasiSE.cpp

include(../common.pri)
include(../app.pri)

COPASI_LIBS += $${COPASI_LIBS_SE}

contains(BUILD_OS, WIN32) {
  CONFIG += console

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)
  }

  
  LIBS += delayimp.lib
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
    dynamic_LIBS -= -lpthread
    dynamic.target   = CopasiSE-dynamic
    dynamic.depends  = $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${TARGETDEPS}
    dynamic.commands = \
      $(LINK) $${dynamic_LFLAGS} -L$(QTDIR)/lib -L/usr/X11R6/lib \
              -o $@ $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${dynamic_LIBS} \
              -Wl,--start-group -Wl,-Bstatic \
              -lm \
              -Wl,--end-group -Wl,-Bdynamic \
              -lpthread -ldl && \
              strip $@

    QMAKE_EXTRA_UNIX_TARGETS += dynamic

    contains(DYNAMIC, TRUE) {
      distribution.extra = make $${dynamic.target};
    }
  }
}

contains(BUILD_OS, SunOS) {
  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}
  LIBS += -lxnet -lnsl -ldl

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first

  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
}


release {
  distribution.path = .
  distribution.file = CopasiSE

  INSTALLS += distribution
}

#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
