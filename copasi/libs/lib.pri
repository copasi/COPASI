######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2006/12/13 18:26:54 $  
######################################################################

TEMPLATE = lib

CONFIG += staticlib

DESTDIR = ../../lib
TMPDIR = ../../tmp
TARGET = $$LIB

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


contains(BUILD_OS, WIN32) {
  OBJECTS += $$join(COPASI_LIBS, ".lib ..\..\tmp\", ..\..\tmp\, .lib)
}

!contains(BUILD_OS, WIN32) {
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
