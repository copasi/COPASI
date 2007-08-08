# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/compareExpressions/compareExpressions.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: gauges $ 
#   $Date: 2007/08/08 10:27:29 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.2 $ $Author: gauges $ $Date: 2007/08/08 10:27:29 $  
######################################################################

LIB = compareExpressions


#TEMPLATE = lib

#CONFIG -= qt

include(../lib.pri)
include(../common.pri)

#DEPENDPATH += .. 
#INCLUDEPATH += ..
#
#COPASI_LIBS = COPASISE
#
#contains(BUILD_OS, WIN32) {
#  LIBS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
#
#  TARGETDEPS += $$join(COPASI_LIBS, ".lib  ../lib/", ../lib/, .lib)
#}
#
#contains(BUILD_OS, Linux) {
#  LIBS = -L../lib \
#         $$join(COPASI_LIBS, " -l", -l) \
#         $${LIBS}
#
#  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
#  
#  INCLUDEPATH += $${CPPUNIT_PATH}/include
#
#
#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
#}
#
#contains(BUILD_OS, SunOS) {
#  QMAKE_LFLAGS += -z rescan
#
#  LIBS = -L../lib \
#         $$join(COPASI_LIBS, " -l", -l) \
#         $${LIBS}
#
#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
#}  
#
#contains(BUILD_OS, Darwin){
#  QMAKE_LFLAGS += -Wl,-search_paths_first
#  
#
#  LIBS = $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a) \
#         $${LIBS}
#
#  LIBS += -L$${CPPUNIT_PATH}/lib -lcppunit
#  
#  INCLUDEPATH += $${CPPUNIT_PATH}/include
#
#  TARGETDEPS += $$join(COPASI_LIBS, ".a  ../lib/lib", ../lib/lib, .a)
#}


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

