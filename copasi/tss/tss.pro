# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/tss.pro,v $
#   $Revision: 1.10 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/07/08 16:06:26 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.10 $ $Author: shoops $ $Date: 2008/07/08 16:06:26 $
######################################################################

LIB = tss

include(../lib.pri)
include(../common.pri)

# Input
contains(DEFINES, COPASI_TSS) {
  HEADERS += CTSSMethod.h
  HEADERS += CTSSProblem.h
  HEADERS += CTSSTask.h

  SOURCES += CTSSMethod.cpp
  SOURCES += CTSSProblem.cpp
  SOURCES += CTSSTask.cpp
}

HEADERS += CODEExporter.h
HEADERS += CODEExporterC.h
HEADERS += CODEExporterBM.h
HEADERS += CODEExporterXPPAUT.h

SOURCES += CODEExporter.cpp
SOURCES += CODEExporterC.cpp
SOURCES += CODEExporterBM.cpp
SOURCES += CODEExporterXPPAUT.cpp


DISTFILES += tss.vcproj
