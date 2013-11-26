# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

LIB = sbmlunit
DISTFILES = sbmlunit.pro

# Input
HEADERS +=  CSBMLunitInterface.h \
            CSBMLunit.h \
            Expression2PresentationMML.h \
            Expression2PresentationMMLUnits.h

SOURCES +=  CSBMLunitInterface.cpp \
            CSBMLunit.cpp \
            Expression2PresentationMML.cpp \
            Expression2PresentationMMLUnits.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
