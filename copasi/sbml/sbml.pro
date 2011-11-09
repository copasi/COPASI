# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/sbml.pro,v $
#   $Revision: 1.25 $
#   $Name:  $
#   $Author: gauges $
#   $Date: 2011/11/09 15:03:25 $
# End CVS Header

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

LIB = sbmlimport
SRC_TARGET = sbml
DISTFILES = sbml.pro

# Input
HEADERS += StdException.h \
           CSBMLExporter.h \
           ConverterASTNode.h \
           SBMLImporter.h \
           SBMLIncompatibility.h \
           SBMLReference.h \
           SBMLUtils.h \
           UnitConversionFactory.hpp \
           incompatibilities.h



SOURCES += StdException.cpp \
           CSBMLExporter.cpp \
           ConverterASTNode.cpp \
           SBMLImporter.cpp \
           SBMLIncompatibility.cpp \
           SBMLReference.cpp \
           SBMLUtils.cpp \
           UnitConversionFactory.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)

contains(DEFINES,CELLDESIGNER_IMPORT) {           
  HEADERS += CCellDesignerImporter.h
}


contains(DEFINES,CELLDESIGNER_IMPORT) {           
  SOURCES += CCellDesignerImporter.cpp
}


contains(BUILD_OS, WIN32) {
  DEFINES += LIBSBML_STATIC
}
