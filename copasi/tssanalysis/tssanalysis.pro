# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $ 
#   $Revision: 1.3 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2008/01/02 11:49:59 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.3 $ $Author: ssahle $ $Date: 2008/01/02 11:49:59 $  
######################################################################

LIB = tssanalysis

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CILDMMethod.h \
           #CILDMModifiedMethod.h \
           CCSPMethod.h \
	   CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h

SOURCES += CILDMMethod.cpp \
           #CILDMModifiedMethod.cpp \
           CCSPMethod.cpp \
	   CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp


DISTFILES += tssanalysis.dsp
