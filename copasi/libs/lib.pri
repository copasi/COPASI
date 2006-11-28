######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2006/11/28 14:49:42 $  
######################################################################

TEMPLATE = lib

CONFIG += staticlib

DESTDIR = ../../lib
TMPDIR = ../../tmp
TARGET = $$LIB


BuildLib.commands = \
  rm -rf $@; \
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
