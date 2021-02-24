// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%ignore real;


/**
 * Convert CModelParameter objects into the most specific type possible.
 */
%typemap(out) CModelParameter*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCModelParameter($1), 0);
}


/**
 * Convert CFitItem objects into the most specific type possible.
 */
%typemap(out) CFitItem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCFitItem($1), 0);
}

/**
 * Convert COptItem objects into the most specific type possible.
 */
%typemap(out) COptItem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptItem($1), 0);
}

/**
 * Convert CExperimentSet objects into the most specific type possible.
%typemap(out) CExperimentSet*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCExperimentSet($1), 0);
}
 */

/**
 * Convert CArrayInterface objects into the most specific type possible.
 */
%typemap(out) CArrayInterface*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCArrayInterface($1), 0);
}

/**
 * Convert CEvaluationTree objects into the most specific type possible.
 */
%typemap(out) CEvaluationTree*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCEvaluationTree($1), 0);
}

/**
 * Convert COptTask objects into the most specific type possible.
 */
%typemap(out) COptTask*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptTask($1), 0);
}


/**
 * Convert Task objects into the most specific type possible.
 */
%typemap(out) CCopasiTask*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForTask($1), 0);
}

/**
 * Convert COptProblem objects into the most specific type possible.
 */
%typemap(out) COptProblem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptProblem($1), 0);
}

/**
 * Convert Problem objects into the most specific type possible.
 */
%typemap(out) CCopasiProblem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForProblem($1), 0);
}

/**
 * Convert COptMethod objects into the most specific type possible.
 */
%typemap(out) COptMethod*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptMethod($1), 0);
}


/**
 * Convert Method objects into the most specific type possible.
 */
%typemap(out) CCopasiMethod*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForMethod($1), 0);
}

/**
 * Convert parametergroup objects into the most specific type possible.
 */
%typemap(out) CCopasiParameterGroup*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiParameterGroup($1), 0);
}


/**
 * Convert parameter objects into the most specific type possible.
 */
%typemap(out) CCopasiParameter*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiParameter($1), 0);
}

/**
 * Convert container objects into the most specific type possible.
 */
%typemap(out) CDataContainer*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCDataContainer($1), 0);
}

/**
 * Convert object objects into the most specific type possible.
 */
%typemap(out) CDataObject*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCDataObject($1), 0);
}


%include "../swig/copasi.i"

%{
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/COptions.h"
%}

%init %{

// Taken from CopasiSE.cpp

// Create the root container
CRootContainer::init(0,NULL,false);

%}

/*
%octavecode %{

TriUnspecified = -1
TriFalse = 0
TriTrue = 1

CRootContainer.init = _COPASI.CRootContainer_init
CRootContainer.destroy = _COPASI.CRootContainer_destroy
CRootContainer.getRoot = _COPASI.CRootContainer_getRoot
CRootContainer.getFunctionList = _COPASI.CRootContainer_getFunctionList
CRootContainer.getDatamodelList = _COPASI.CRootContainer_getDatamodelList
CRootContainer.addDatamodel = _COPASI.CRootContainer_addDatamodel
CRootContainer.getUndefinedFunction = _COPASI.CRootContainer_getUndefinedFunction
CRootContainer.getKeyFactory = _COPASI.CRootContainer_getKeyFactory
CRootContainer.removeDatamodel = _COPASI.CRootContainer_removeDatamodel
CRootContainer.removeDatamodelWithIndex = _COPASI.CRootContainer_removeDatamodelWithIndex

CCommonName.escape = _COPASI.CCommonName_escape
CCommonName.unescape = _COPASI.CCommonName_unescape

CCopasiMethod.TypeNameToEnum = _COPASI.CCopasiMethod_TypeNameToEnum

CEvaluationTree.create = _COPASI.CEvaluationTree_create
CEvaluationTree.copy = _COPASI.CEvaluationTree_copy

COutputAssistant.getListOfDefaultOutputDescriptions = _COPASI.COutputAssistant_getListOfDefaultOutputDescriptions
COutputAssistant.getDefaultReportIndex = _COPASI.COutputAssistant_getDefaultReportIndex
COutputAssistant.getItemName = _COPASI.COutputAssistant_getItemName
COutputAssistant.getItem = _COPASI.COutputAssistant_getItem
COutputAssistant.createDefaultOutput = _COPASI.COutputAssistant_createDefaultOutput

CCopasiMessage.peekFirstMessage = _COPASI.CCopasiMessage_peekFirstMessage
CCopasiMessage.peekLastMessage = _COPASI.CCopasiMessage_peekLastMessage
CCopasiMessage.getFirstMessage = _COPASI.CCopasiMessage_getFirstMessage
CCopasiMessage.getLastMessage = _COPASI.CCopasiMessage_getLastMessage
CCopasiMessage.getAllMessageText = _COPASI.CCopasiMessage_getAllMessageText
CCopasiMessage.clearDeque = _COPASI.CCopasiMessage_clearDeque
CCopasiMessage.getHighestSeverity = _COPASI.CCopasiMessage_getHighestSeverity
CCopasiMessage.checkForMessage = _COPASI.CCopasiMessage_checkForMessage
CCopasiMessage.size = _COPASI.CCopasiMessage_size

%}
*/

/*
%extend CCopasiParameter
{
  %octavecode
  %{

      def setValue(self,arg):
        result=False
        if(type(arg)==types.IntType):
           if((self.getType()==self.Type_INT) or (arg < 0)):
             result=self.setIntValue(arg)
           else:
             result=self.setUIntValue(arg) 
        elif(type(arg)==types.FloatType):
           result=self.setDblValue(arg) 
        elif(type(arg)==types.BooleanType):
           result=self.setBoolValue(arg) 
        elif(type(arg)==types.StringType):
           result=self.setStringValue(arg) 
        elif(arg.__class__==CRegisteredCommonName):
           result=self.setCNValue(arg) 
        elif(arg.__class__ == ParameterVector):
           result=self.setGroupValue(arg) 
        return result;

      def getValue(self):
        value=None
        if(self.getType()==CCopasiParameter.Type_DOUBLE):
          value=self.getDblValue()
        if(self.getType()==CCopasiParameter.Type_UDOUBLE):
          value=self.getUDblValue()
        if(self.getType()==CCopasiParameter.Type_INT):
          value=self.getIntValue()
        if(self.getType()==CCopasiParameter.Type_UINT):
          value=self.getUIntValue()
        if(self.getType()==CCopasiParameter.Type_BOOL):
          value=self.getBoolValue()
        if(self.getType()==CCopasiParameter.Type_GROUP):
          value=self.getGroupValue()
        if(self.getType()==CCopasiParameter.Type_STRING):
          value=self.getStringValue()
        if(self.getType()==CCopasiParameter.Type_KEY):
          value=self.getKeyValue()
        if(self.getType()==CCopasiParameter.Type_FILE):
          value=self.getFileValue()
        if(self.getType()==CCopasiParameter.Type_CN):
          value=self.getCNValue()
        return value            
  %}

}
*/


