# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAM/MIRIAM.pro,v $ 
#   $Revision: 1.1 $ 
#   $Name:  $ 
#   $Author: aekamal $ 
#   $Date: 2007/10/27 01:45:50 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

LIB = MIRIAM

include(../lib.pri)
include(../common.pri)

CONFIG += qt

DEPENDPATH += .. 
INCLUDEPATH += ..

# Input
HEADERS += \
           CAuthor.h \
           CModelMIRIAMInfo.h


SOURCES += \
           CAuthor.cpp \
           CModelMIRIAMInfo.cpp
