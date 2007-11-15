# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/sbml.pro,v $ 
#   $Revision: 1.15 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/11/15 13:56:22 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = sbmlimport
SRC_TARGET = sbml

include(../lib.pri)
include(../common.pri)

contains(BUILD_OS, WIN32) {
  DEFINES += LIBSBML_STATIC
}

# Input
HEADERS += StdException.h \
           ConverterASTNode.h \
           SBMLImporter.h \
           SBMLIncompatibility.h \
           SBMLExporter.h \
           SBMLReference.h \
           SBMLUtils.h \
           UnitConversionFactory.hpp 
           
           
           
SOURCES += StdException.cpp \
           ConverterASTNode.cpp \
           SBMLImporter.cpp \
           SBMLIncompatibility.cpp \
           SBMLExporter.cpp \
           SBMLReference.cpp \
           SBMLUtils.cpp \
           UnitConversionFactory.cpp 


DISTFILES += sbml.dsp

