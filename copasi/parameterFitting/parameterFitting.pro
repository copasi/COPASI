# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/parameterFitting.pro,v $ 
#   $Revision: 1.7 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/07/08 16:06:31 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.7 $ $Author: shoops $ $Date: 2008/07/08 16:06:31 $
######################################################################

LIB = fitting
SRC_TARGET = parameterFitting

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CExperiment.h \
           CExperimentSet.h \
           CExperimentObjectMap.h \
           CExperimentFileInfo.h \
           CFitItem.h \
           CFitMethod.h \
           CFitProblem.h \
           CFitTask.h

SOURCES += CExperiment.cpp \
           CExperimentSet.cpp  \
           CExperimentObjectMap.cpp \
           CExperimentFileInfo.cpp \
           CFitItem.cpp \
           CFitMethod.cpp \
           CFitProblem.cpp \
           CFitTask.cpp


DISTFILES += fitting.vcproj
