# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/CopasiUI.pro,v $
#   $Revision: 1.156 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2012/03/15 19:06:46 $
# End CVS Header

# Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
# $Revision: 1.156 $ $Author: shoops $ $Date: 2012/03/15 19:06:46 $
######################################################################

TEMPLATE = app
SRC_TARGET = CopasiUI
DISTFILES = CopasiUI.pro

CONFIG += qt

# Input
HEADERS += resource.h

SOURCES += main.cpp

DISTFILES += CopasiUI.rc

include(../common.pri)
include(../app.pri)

DEPENDPATH += ..
INCLUDEPATH += ..

COPASI_LIBS += $${COPASI_LIBS_UI}
COPASI_LIBS += $${COPASI_LIBS_SE}

contains(BUILD_OS, WIN32) {
  RC_FILE = CopasiUI.rc

  debug {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
    POST_TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/debug/", ../lib/debug/, .lib)
  }

  release {
    LIBS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)
    POST_TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/release/", ../lib/release/, .lib)

    distribution.extra = C:\cygwin\bin\bash ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

contains(BUILD_OS, Linux) {
  CONFIG += opengl

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  QMAKE_LFLAGS -= -static

#  linux-icc {
#    OBJECTS += $(QTDIR)//src/corelib/.obj/release-static/qvariant.o
#  }

  release {
    dynamic_LFLAGS  = $${QMAKE_LFLAGS}
    dynamic_LFLAGS -= -static

    dynamic_LIBS  = -Wl,-Bstatic $${LIBS} -Wl,-Bdynamic
    dynamic_LIBS -= -lpthread

    dynamic_LIBS += -lQt3Support \
                    -lQtWebKit \
                    -lQtSvg \
                    -lQtSql \
                    -lQtNetwork \
                    -lQtXml \
                    -lQtOpenGL \
                    -lQtGui \
                    -lQtCore

    dynamic_LIBS += -lGLU \
                    -lGL \
                    -Wl,--start-group \
                      -lfreetype \
                      -lXrender \
                      -lfontconfig \
                      -lXext \
                      -lX11 \
                      -lSM \
                      -lICE \
                    -Wl,--end-group \
                    -lz \
                    -lm \
                    -lrt \
                    -lpthread \
                    -ldl

    dynamic.target   = CopasiUI-dynamic
    dynamic.depends  = $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${POST_TARGETDEPS}
    dynamic.commands = \
      $(LINK) $${dynamic_LFLAGS} -L$(QTDIR)/lib -L/usr/lib \
              -o $@ $(OBJECTS) $(OBJMOC) $(OBJCOMP) $${dynamic_LIBS} && \
              strip $@

    QMAKE_EXTRA_TARGETS += dynamic

    contains(DYNAMIC, TRUE) {
      distribution.extra = make $${dynamic.target} &&
    }

    distribution.extra += ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

contains(BUILD_OS, SunOS) {
  QMAKE_LFLAGS += -z rescan

  LIBS = -L../lib \
         $$join(COPASI_LIBS, " -l", -l) \
         $${LIBS}

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

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

  POST_TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)

  release {
    distribution.extra = ../../admin/mkbuild.sh $${BUILD_OS}
  }
}

release {
  distribution.path = .
  distribution.file = CopasiUI

  INSTALLS += distribution
}

include(../srcDistribution.pri)
