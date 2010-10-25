# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/wizard/wizard.pro,v $
#   $Revision: 1.16.2.1 $
#   $Name:  $
#   $Author: aekamal $
#   $Date: 2010/10/25 16:12:48 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

LANGUAGE	= C++

LIB= wizard

HEADERS = wizard.h

SOURCES = wizard.cpp

FORMS = wizard.ui

DISTFILES += help_html/figures/*.png \
             help_html/*.html
             
include(../lib.pri)

CONFIG += qt 

include(../common.pri)
