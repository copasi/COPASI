# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/plot.pro,v $ 
#   $Revision: 1.23.10.1 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2009/02/24 19:34:08 $ 
# End CVS Header 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

######################################################################
# $Revision: 1.23.10.1 $ $Author: shoops $ $Date: 2009/02/24 19:34:08 $
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

CONFIG -= qt

HEADERS += CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h

SOURCES += CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \

DISTFILES += plot.vcproj
