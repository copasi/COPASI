# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/math/math.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2011/03/21 15:45:57 $ 
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
HEADRES += CMathEnum.h
HEADERS += CMathObject.h

SOURCES += CMathDependencyGraph.cpp
SOURCES += CMathDependencyNode.cpp
SOURCES += CMathExpression.cpp
SOURCES += CMathContainer.cpp
SOURCES += CMathObject.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
