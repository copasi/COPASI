######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2006/12/21 18:28:55 $  
######################################################################

CONFIG -= qt
CONFIG += exceptions
CONFIG += debug

QMAKE_QMAKE = $(QTDIR)/bin/qmake

#Input
HEADERS += COptions.h \
           ../../copasi/commercial/BigInt.h \
           ../../copasi/commercial/GenericDecode.h

SOURCES += COptions.cpp \
           license.cpp \
           ../../copasi/commercial/BigInt.c \
           ../../copasi/commercial/GenericDecode.c

CLOPP = $$system(which clo++)

count(CLOPP, 1) {
  1.target = COptions.cpp
  1.depends = COptions.xml
  1.commands = \
        rm $@ $*.h; \
        clo++ -o c++ $< && \
        cat $@ | \
        sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
            > $@.tmp && \
        mv $@.tmp $@; \
        ../../cvs_admin/c++style $@; \
        ../../cvs_admin/c++style $*.h
      
  QMAKE_EXTRA_UNIX_TARGETS += 1
}
