# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/commandline/commandline.pro,v $
#   $Revision: 1.14 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/12/18 17:25:09 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.14 $ $Author: shoops $ $Date: 2008/12/18 17:25:09 $
######################################################################

LIB = commandline

include(../lib.pri)
include(../common.pri)

#Input
HEADERS += CConfigurationFile.h \
           COptionParser.h \
           COptions.h

SOURCES += CConfigurationFile.cpp \
           COptionParser.cpp \
           COptions.cpp

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
             commandline.vcproj \
             COptionParser.xml
#The following line was inserted by qt3to4
QT +=  qt3support 
