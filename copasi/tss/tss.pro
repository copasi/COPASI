# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/tss.pro,v $
#   $Revision: 1.15 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2011/10/17 19:54:31 $
# End CVS Header

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
# and The University of Manchester. 
# All rights reserved. 

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.15 $ $Author: shoops $ $Date: 2011/10/17 19:54:31 $
######################################################################

LIB = tss
DISTFILES = tss.pro

# Input
HEADERS += CODEExporter.h
HEADERS += CODEExporterC.h
HEADERS += CODEExporterBM.h
HEADERS += CODEExporterXPPAUT.h

SOURCES += CODEExporter.cpp
SOURCES += CODEExporterC.cpp
SOURCES += CODEExporterBM.cpp
SOURCES += CODEExporterXPPAUT.cpp

include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
