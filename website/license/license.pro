# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/website/license/Attic/license.pro,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/05/25 15:12:14 $ 
# End CVS Header 

# Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2011/05/25 15:12:14 $  
######################################################################

CONFIG -= qt
CONFIG += exceptions
CONFIG += debug

QMAKE_QMAKE = $(QTDIR)/bin/qmake

DEFINES += LICENSE_CREATE
INCLUDEPATH += ../../copasi/commercial

# unix:QMAKE_LFLAGS += -static

#Input
HEADERS += COptions.h \
           ../../copasi/commercial/FlexibleInt.h \
           ../../copasi/commercial/BigInt.h \
           ../../copasi/commercial/GenericDecode.h

SOURCES += license.cpp \
           COptions.cpp \
           ../../copasi/commercial/FlexibleInt.c \
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
      
  QMAKE_EXTRA_TARGETS += 1
}
