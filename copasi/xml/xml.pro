# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/xml.pro,v $
#   $Revision: 1.14.2.2 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/11/13 16:56:02 $
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
# $Revision: 1.14.2.2 $ $Author: shoops $ $Date: 2010/11/13 16:56:02 $
######################################################################

LIB = copasiXML
SRC_TARGET = xml
DISTFILES = xml.pro

# Input
HEADERS += CCopasiXML.h \
           CCopasiXMLInterface.h \
           CCopasiXMLVersion.h \
           CExpat.h \
           CFixLocalReactionParameters.h \
           CXMLHandler.h  \
           CCopasiXMLParser.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp \
           CFixLocalReactionParameters.cpp \
           CCopasiXMLParser.cpp


include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
