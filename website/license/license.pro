######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2006/12/20 19:57:27 $  
######################################################################

CONFIG -= qt

#Input
HEADERS += COptions.h

SOURCES += COptions.cpp \
           license.cpp

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
