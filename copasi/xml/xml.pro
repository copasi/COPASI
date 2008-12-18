# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/xml.pro,v $
#   $Revision: 1.12 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2008/12/18 19:21:26 $
# End CVS Header

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

######################################################################
# $Revision: 1.12 $ $Author: shoops $ $Date: 2008/12/18 19:21:26 $
######################################################################

LIB = xml

include(../lib.pri)
include(../common.pri)

TARGET = copasiXML

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


DISTFILES += copasi.xsd \
             copasiXML.vcproj
#The following line was inserted by qt3to4
QT +=  qt3support 
