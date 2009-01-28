# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/libs/lib.pri,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2009/01/28 03:56:28 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.4 $ $Author: shoops $ $Date: 2009/01/28 03:56:28 $  
######################################################################

TEMPLATE = lib

CONFIG += staticlib

TMPDIR = ../../tmp
TARGET = $$LIB

win32 {
  debug {
    OBJECTS = $$join(COPASI_LIBS, ".lib ../../tmp/debug/", ../../tmp/debug/, .lib)
    DESTDIR = ../../lib/debug
  }

  release {
    OBJECTS = $$join(COPASI_LIBS, ".lib ../../tmp/release/", ../../tmp/release/, .lib)
    DESTDIR = ../../lib/release
  }
} else {
  DESTDIR = ../../lib
  BuildLib.commands = \
    rm -rf $@; \
    $(CHK_DIR_EXISTS) $$DESTDIR || $(MKDIR) $$DESTDIR; \
    $$join(COPASI_LIBS, ".a; $$QMAKE_AR $@ *.o; rm *.o; tar -xzf $$TMPDIR/lib", "tar -xzf $$TMPDIR/lib", ".a; $$QMAKE_AR $@ *.o; rm *.o");

  contains(BUILD_OS, Darwin) {
    BuildLib.commands += ranlib -s $@
  }

  BuildLib.target = $$DESTDIR/$(TARGET)
  BuildLib.depends = Makefile $$join(COPASI_LIBS, ".a $$TMPDIR/lib", $$TMPDIR/lib, .a)
  QMAKE_EXTRA_UNIX_TARGETS += BuildLib

  OBJECTS += Makefile
  TARGETDEPS += $$DESTDIR/$(TARGET)
  DESTDIR = .
}

!equals(TEMPLATE, subdirs) {
  # Copy the sources for the tar ball
  src_distribution.commands =   \
    $(CHK_DIR_EXISTS) ../../../copasi_src || $(MKDIR) ../../../copasi_src; \
    $(CHK_DIR_EXISTS) ../../../copasi_src/copasi || \
      $(MKDIR) ../../../copasi_src/copasi; \
    $(CHK_DIR_EXISTS) ../../../copasi_src/copasi/libs || \
      $(MKDIR) ../../../copasi_src/copasi/libs; \
    $(CHK_DIR_EXISTS) ../../../copasi_src/copasi/libs/$$SRC_TARGET || \
      $(MKDIR) ../../../copasi_src/copasi/libs/$$SRC_TARGET; \
    $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) \
      ../../../copasi_src/copasi/libs/$$SRC_TARGET/
}
