# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/tssanalysis.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2008/01/09 14:53:43 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.5 $ $Author: shoops $ $Date: 2008/01/09 14:53:43 $  
######################################################################

LIB = tssanalysis

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CILDMMethod.h \
           CILDMModifiedMethod.h \
           CCSPMethod.h \
	       CTSSAMethod.h \
           CTSSAProblem.h \
           CTSSATask.h

SOURCES += CILDMMethod.cpp \
           CILDMModifiedMethod.cpp \
           CCSPMethod.cpp \
	       CTSSAMethod.cpp \
           CTSSAProblem.cpp \
           CTSSATask.cpp


DISTFILES += tssanalysis.dsp
