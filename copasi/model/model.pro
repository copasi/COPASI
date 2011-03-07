# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/model.pro,v $
#   $Revision: 1.35 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2011/03/07 19:30:51 $
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
# $Revision: 1.35 $ $Author: shoops $ $Date: 2011/03/07 19:30:51 $
######################################################################

LIB = model
DISTFILES = model.pro

# Input
HEADERS += CAnnotation.h \
           CChemEq.h \
           CChemEqElement.h \
           CChemEqInterface.h \
           CChemEqParser.h \
           CChemEqParser_yacc.h \
           CCompartment.h \
           CDotOutput.h \
           CEvent.h \
           CMathEvent.h \
           CMathModel.h \
           CMathTrigger.h \
           CMetab.h \
           CMetabNameInterface.h \
           CMMLOutput.h \
           CModel.h \
           CModelAnalyzer.h \
           CModelExpansion.h \
           CModelMerging.h \
           CModelValue.h \
           CMoiety.h \
           CObjectLists.h \
           CProcessQueue.h \
           CReaction.h \
           CReactionInterface.h \
           CState.h

SOURCES += CAnnotation.cpp \
           CChemEq.cpp \
           CChemEqElement.cpp \
           CChemEqInterface.cpp \
           CChemEqParser.cpp \
           CChemEqParser_lex.cpp \
           CChemEqParser_yacc.cpp \
           CCompartment.cpp \
           CDotOutput.cpp \
           CEvent.cpp \
           CMathEvent.cpp \
           CMathModel.cpp \
           CMathTrigger.cpp \
           CMetab.cpp \
           CMetabNameInterface.cpp \
           CMMLOutput.cpp \
           CModel.cpp \
           CModelAnalyzer.cpp \
           CModelExpansion.cpp \
           CModelMerging.cpp \
           CModelValue.cpp \
           CMoiety.cpp \
           CObjectLists.cpp \
           CProcessQueue.cpp \
           CReaction.cpp \
           CReactionInterface.cpp \
           CState.cpp


contains(BUILD_PARSER, yes) {
  YACCSOURCES += CChemEqParser.ypp
  SOURCES -= CChemEqParser_yacc.cpp

  LEXSOURCES += CChemEqParser.lpp
  SOURCES -= CChemEqParser_lex.cpp
}


DISTFILES += CChemEqParser_lex.cpp \
             CChemEqParser_yacc.cpp
             
include(../lib.pri)
include(../common.pri)
include(../srcDistribution.pri)
