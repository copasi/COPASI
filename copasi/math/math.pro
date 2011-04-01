# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/math.pro,v $ 
#   $Revision: 1.2 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/04/01 17:34:31 $ 
# End CVS Header 

# Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

LIB = math
SRC_TARGET = math
DISTFILES = math.pro

# Input
HEADERS += CMathDependencyGraph.h
HEADERS += CMathDependencyNode.h
HEADERS += CMathExpression.h
HEADERS += CMathContainer.h
HEADERS += CMathEnum.h
HEADERS += CMathEvent.h
HEADERS += CMathObject.h
HEADERS += CMathTrigger.h

SOURCES += CMathDependencyGraph.cpp
SOURCES += CMathDependencyNode.cpp
SOURCES += CMathExpression.cpp
SOURCES += CMathContainer.cpp
SOURCES += CMathEvent.cpp
SOURCES += CMathObject.cpp
SOURCES += CMathTrigger.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
