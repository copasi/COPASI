# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/commandline.pro,v $
#   $Revision: 1.16.2.1 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/10/20 15:14:21 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.16.2.1 $ $Author: shoops $ $Date: 2010/10/20 15:14:21 $
######################################################################

LIB = commandline

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
    clo.commands = C:\cygwin\bin\bash ../../admin/clo++.sh $$clo.depends
    QMAKE_EXTRA_WIN_TARGETS += clo
  } else {
    clo.commands = ../../admin/clo++.sh $$clo.depends
    QMAKE_EXTRA_UNIX_TARGETS += clo
  }
}


DISTFILES += \
             COptionParser.xml
