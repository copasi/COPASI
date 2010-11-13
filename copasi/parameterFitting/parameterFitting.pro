# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/parameterFitting.pro,v $ 
#   $Revision: 1.10.2.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/11/13 14:53:13 $ 
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
# $Revision: 1.10.2.1 $ $Author: shoops $ $Date: 2010/11/13 14:53:13 $
######################################################################

LIB = fitting
SRC_TARGET = parameterFitting

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

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
