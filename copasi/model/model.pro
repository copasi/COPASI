# Begin CVS Header 
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/model.pro,v $ 
#   $Revision: 1.24 $ 
#   $Name:  $ 
#   $Author: ssahle $ 
#   $Date: 2007/08/22 16:53:54 $ 
# End CVS Header 

# Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc. and EML Research, gGmbH. 
# All rights reserved. 

######################################################################
# $Revision: 1.24 $ $Author: ssahle $ $Date: 2007/08/22 16:53:54 $  
######################################################################

LIB = model

include(../lib.pri)
include(../common.pri)

# Input
HEADERS += CChemEq.h \
           CChemEqElement.h \
           CChemEqInterface.h \
           CChemEqParser.h \
           CChemEqParser_yacc.h \
           CCompartment.h \
           CDotOutput.h \
           CMetab.h \
           CMetabNameInterface.h \
           CMMLOutput.h \
           CModel.h \
           CModelAnalyzer.h \
           CModelValue.h \
           CMoiety.h \
           CObjectLists.h \
           CReaction.h \
           CReactionInterface.h \
           CState.h
           
SOURCES += CChemEq.cpp \
           CChemEqElement.cpp \
           CChemEqInterface.cpp \
           CChemEqParser.cpp \
           CChemEqParser_lex.cpp \
           CChemEqParser_yacc.cpp \
           CCompartment.cpp \
           CDotOutput.cpp \
           CMetab.cpp \
           CMetabNameInterface.cpp \
           CMMLOutput.cpp \
           CModel.cpp \
           CModelAnalyzer.cpp \
           CModelValue.cpp \
           CMoiety.cpp \
           CObjectLists.cpp \
           CReaction.cpp \
           CReactionInterface.cpp \
           CState.cpp


contains(BUILD_PARSER, yes) {
  YACCSOURCES += CChemEqParser.ypp
  SOURCES -= CChemEqParser_yacc.cpp

  LEXSOURCES += CChemEqParser.lpp  
  SOURCES -= CChemEqParser_lex.cpp
}


DISTFILES += model.dsp \
             CChemEqParser_lex.cpp \
             CChemEqParser_yacc.cpp
