# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/miase.pro,v $ 
#   $Revision: 1.4 $ 
#   $Name:  $ 
#   $Author: akoenig $ 
#   $Date: 2008/03/20 18:33:37 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LIB = miase
SRC_TARGET = miase

include(../lib.pri)
include(../common.pri)


# Input
HEADERS +=  CMiaseParser.h \
			CMiaseBase.h \
			CMiaseSimulation.h \
			CMiaseModel.h \
			CMiaseTask.h \
			CMiaseOutput.h \
			CMiaseML.h
           
           
SOURCES +=  CMiaseParser.cpp \
			CMiaseBase.cpp \
			CMiaseSimulation.cpp \
			CMiaseModel.cpp \
			CMiaseTask.cpp \
			CMiaseOutput.cpp \
			CMiaseML.cpp



