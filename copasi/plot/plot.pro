# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/plot.pro,v $ 
#   $Revision: 1.27.2.1 $ 
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
# $Revision: 1.27.2.1 $ $Author: shoops $ $Date: 2010/11/13 14:53:13 $
######################################################################

LIB = plot

CONFIG -= qt

HEADERS += CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h

SOURCES += CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
