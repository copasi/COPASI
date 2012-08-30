# Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.18 $ $Author: shoops $ $Date: 2011/05/25 15:12:18 $
######################################################################

LIB = commandline
DISTFILES = commandline.pro

#Input
HEADERS += CConfigurationFile.h \
           CLocaleString.h \
           COptionParser.h \
           COptions.h

SOURCES += CConfigurationFile.cpp \
           CLocaleString.cpp \
           COptionParser.cpp \
           COptions.cpp

include(../lib.pri)
include(../common.pri)

contains(BUILD_PARSER, yes) {
  clo.target = COptionParser.cpp
  clo.depends = COptionParser.xml
  win32:{
    clo.commands = C:/cygwin/bin/bash ../../admin/clo++.sh $$clo.depends
    QMAKE_EXTRA_WIN_TARGETS += clo
  } else {
    clo.commands = ../../admin/clo++.sh $$clo.depends
    QMAKE_EXTRA_TARGETS += clo
  }
}


DISTFILES += \
             COptionParser.xml

include(../srcDistribution.pri)
