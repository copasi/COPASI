# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/plot.pro,v $ 
#   $Revision: 1.29 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2012/05/02 23:40:07 $ 
# End CVS Header 

# Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.29 $ $Author: ssahle $ $Date: 2012/05/02 23:40:07 $
######################################################################

LIB = plot
DISTFILES = plot.pro

CONFIG -= qt

HEADERS += CPlotColors.h \
           CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h

SOURCES += CPlotColors.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
