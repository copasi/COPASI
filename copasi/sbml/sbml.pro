# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/sbml.pro,v $ 
#   $Revision: 1.13 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/02/13 16:46:18 $ 
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
           SBMLExporter.h \
           SBMLReference.h \
           UnitConversionFactory.hpp \
           SBMLUtils.h
           
           
           
SOURCES += StdException.cpp \
           ConverterASTNode.cpp \
           SBMLImporter.cpp \
           SBMLExporter.cpp \
           SBMLReference.cpp \
           UnitConversionFactory.cpp \
           SBMLUtils.cpp


DISTFILES += sbml.dsp

