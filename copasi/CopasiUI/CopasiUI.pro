# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/CopasiUI.pro,v $
#   $Revision: 1.149 $
#   $Name:  $
#   $Author: pwilly $
#   $Date: 2009/06/22 21:00:08 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.149 $ $Author: pwilly $ $Date: 2009/06/22 21:00:08 $
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

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)
    TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)

    distribution.extra = C:\cygwin\bin\bash ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

contains(BUILD_OS, Linux) {
  CONFIG += opengl

  LIBS += -lfreetype

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  contains(QMAKE_LFLAGS, -static) {
   LIBS += -Wl,-lqt-mt \
           -Wl,-lGL \
           -Wl,-lXxf86vm \
           -Wl,-lXcursor \
           -Wl,-lXft \
           -Wl,-lfontconfig \
           -Wl,-lpthread
  }

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
              -Wl,--start-group \
              -lqt-mt -lXrender -lXrandr -lXcursor -lXinerama -lXft \
              -lfreetype -lfontconfig -lSM -lICE -lXext -lX11 -lm \
              -Wl,--end-group \
              -ldl -lpthread && \
              strip $@

    QMAKE_EXTRA_UNIX_TARGETS += dynamic

#    distribution.extra = make $${dynamic.target}; \
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}

  }
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  LIBS += -lGLU -lICE -ldl

  release {
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

contains(BUILD_OS, Darwin){
  QMAKE_LFLAGS += -Wl,-search_paths_first

  CONFIG += opengl

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

DISTFILES += CopasiUI.vcproj \
             CopasiUI.rc

#The following line was inserted by qt3to4
QT += xml  opengl qt3support 

#The following line is for implementing QtSvg module
QT += svg

