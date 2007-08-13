# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/compareExpressions.pro,v $ 
#   $Revision: 1.5 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/08/13 07:41:17 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.5 $ $Author: gauges $ $Date: 2007/08/13 07:41:17 $  
######################################################################

LIB = compareExpressions


include(../lib.pri)
include(../common.pri)

QMAKE_EXTRA_UNIX_TARGETS += check
check.commands = cd unittests; $(QMAKE) $$(0);make

# Input
HEADERS +=  CNormalItem.h \
            CNormalItemPower.h\
            CNormalProduct.h \
	    CNormalSum.h \
	    CNormalLcm.h \
	    CNormalFraction.h \
	    CNormalBase.h \
	    CNormalChoiceLogical.h \
	    CNormalChoice.h \
	    CNormalLogical.h \
	    CNormalLogicalItem.h \
	    CNormalFunction.h \
            CNormalGeneralPower.h \
            CNormalTranslation.h\
            ConvertToCEvaluationNode.h \
            compare_utilities.h


	    
SOURCES +=  CNormalItem.cpp \
            CNormalItemPower.cpp \
            CNormalProduct.cpp \
	    CNormalSum.cpp \
	    CNormalLcm.cpp \
	    CNormalFraction.cpp \
            CNormalChoice.cpp \
            CNormalChoiceLogical.cpp \
	    CNormalLogical.cpp \
	    CNormalLogicalItem.cpp \
      	    CNormalFunction.cpp \
            CNormalGeneralPower.cpp \
            CNormalTranslation.cpp \
            CNormalBase.cpp \
            ConvertToCEvaluationNode.cpp \ 
            compare_utilities.cpp

