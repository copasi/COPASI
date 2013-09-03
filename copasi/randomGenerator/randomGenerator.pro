# Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.12 $ $Author: shoops $ $Date: 2011/03/07 19:32:39 $
######################################################################

LIB = randomGenerator
DISTFILES = randomGenerator.pro

# Input
HEADERS += Cmt19937.h \
           Cr250.h \
           CPermutation.h \
           CRandom.h

SOURCES += Cmt19937.cpp \
           Cr250.cpp \
           CPermutation.cpp \
           CRandom.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
