# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/xml.pro,v $
#   $Revision: 1.17 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2012/05/25 12:13:29 $
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
# $Revision: 1.17 $ $Author: shoops $ $Date: 2012/05/25 12:13:29 $
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
           CCopasiXMLParser.h \
           ListOfModelParameterSets.h \
           ListOfUnsupportedAnnotations.h

SOURCES += CCopasiXML.cpp \
           CCopasiXMLInterface.cpp \
           CExpat.cpp \
           CFixLocalReactionParameters.cpp \
           CCopasiXMLParser.cpp \
           ListOfModelParameterSets.cpp \
           ListOfUnsupportedAnnotations.cpp


include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
