######################################################################
# $Revision: 1.2 $ $Author: shoops $ $Date: 2003/05/19 00:39:42 $  
######################################################################

LIB = commandline
include(../lib.pri)

# Input
HEADERS += COptionParser.h \
           COptions.h

SOURCES += COptionParser.cpp \
           COptions.cpp

CLOPP = $$system(which clo++)
count(CLOPP, 1) {
  1.target = COptionParser.cpp
  1.depends = COptionParser.xml
  1.commands = \
        -@rm $@ $*.h; \
        -clo++ -o c++ $< && \
        cat $@ | \
        sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
            > $@.tmp && \
        mv $@.tmp $@; \
        ../cvs_admin/c++style $@; \
        ../cvs_admin/c++style $*.h
        
  QMAKE_EXTRA_UNIX_TARGETS += 1
}


