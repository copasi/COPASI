// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/python/python.i,v $ 
//   $Revision: 1.28 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2012/03/05 18:09:32 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
 * Convert CCopasiAbstractArray objects into the most specific type possible.
 */
%typemap(out) CCopasiAbstractArray*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiAbstractArray($1), 0);
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
%typemap(out) CCopasiContainer*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiContainer($1), 0);
}

/**
 * Convert object objects into the most specific type possible.
 */
%typemap(out) CCopasiObject*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCCopasiObject($1), 0);
}



%pythoncode
%{
import types
%}

%include "../swig/copasi.i"

%{
#include "report/CCopasiRootContainer.h"
#include "commandline/COptions.h"
%}

%init %{

// Taken from CopasiSE.cpp

// Create the root container
CCopasiRootContainer::init(0,NULL,false);

%}

%pythoncode %{

TriUnspecified=-1
TriFalse=0
TriTrue=1

CCopasiRootContainer.init=_COPASI.CCopasiRootContainer_init
CCopasiRootContainer.destroy=_COPASI.CCopasiRootContainer_destroy
CCopasiRootContainer.getRoot=_COPASI.CCopasiRootContainer_getRoot
CCopasiRootContainer.getFunctionList=_COPASI.CCopasiRootContainer_getFunctionList
CCopasiRootContainer.getDatamodelList=_COPASI.CCopasiRootContainer_getDatamodelList
CCopasiRootContainer.addDatamodel=_COPASI.CCopasiRootContainer_addDatamodel
CCopasiRootContainer.getUndefinedFunction=_COPASI.CCopasiRootContainer_getUndefinedFunction
CCopasiRootContainer.getKeyFactory=_COPASI.CCopasiRootContainer_getKeyFactory
CCopasiRootContainer.removeDatamodel=_COPASI.CCopasiRootContainer_removeDatamodel
CCopasiRootContainer.removeDatamodelWithIndex=_COPASI.CCopasiRootContainer_removeDatamodelWithIndex

CCopasiObjectName.escape=_COPASI.CCopasiObjectName_escape
CCopasiObjectName.unescape=_COPASI.CCopasiObjectName_unescape

CCopasiMethod.TypeNameToEnum=_COPASI.CCopasiMethod_TypeNameToEnum

CEvaluationTree.create=_COPASI.CEvaluationTree_create
CEvaluationTree.copy=_COPASI.CEvaluationTree_copy

COutputAssistant.getListOfDefaultOutputDescriptions=_COPASI.COutputAssistant_getListOfDefaultOutputDescriptions
COutputAssistant.getDefaultReportIndex=_COPASI.COutputAssistant_getDefaultReportIndex
COutputAssistant.getItemName=_COPASI.COutputAssistant_getItemName
COutputAssistant.getItem=_COPASI.COutputAssistant_getItem
COutputAssistant.createDefaultOutput=_COPASI.COutputAssistant_createDefaultOutput

CCopasiMessage.peekFirstMessage=_COPASI.CCopasiMessage_peekFirstMessage
CCopasiMessage.peekLastMessage=_COPASI.CCopasiMessage_peekLastMessage
CCopasiMessage.getFirstMessage=_COPASI.CCopasiMessage_getFirstMessage
CCopasiMessage.getLastMessage=_COPASI.CCopasiMessage_getLastMessage
CCopasiMessage.getAllMessageText=_COPASI.CCopasiMessage_getAllMessageText
CCopasiMessage.clearDeque=_COPASI.CCopasiMessage_clearDeque
CCopasiMessage.getHighestSeverity=_COPASI.CCopasiMessage_getHighestSeverity
CCopasiMessage.checkForMessage=_COPASI.CCopasiMessage_checkForMessage
CCopasiMessage.size=_COPASI.CCopasiMessage_size

%}

%extend CCopasiParameter
{
  %pythoncode
  %{

      def setValue(self,arg):
        result=False
        if(type(arg)==types.IntType):
           if((self.getType()==self.INT) or (arg < 0)):
             result=self.setIntValue(arg)
           else:
             result=self.setUIntValue(arg) 
        elif(type(arg)==types.FloatType):
           result=self.setDblValue(arg) 
        elif(type(arg)==types.BooleanType):
           result=self.setBoolValue(arg) 
        elif(type(arg)==types.StringType):
           result=self.setStringValue(arg) 
        elif(arg.__class__==CRegisteredObjectName):
           result=self.setCNValue(arg) 
        elif(arg.__class__ == ParameterVector):
           result=self.setGroupValue(arg) 
        return result;

      def getValue(self):
        value=None
        if(self.getType()==CCopasiParameter.DOUBLE):
          value=self.getDblValue()
        if(self.getType()==CCopasiParameter.UDOUBLE):
          value=self.getUDblValue()
        if(self.getType()==CCopasiParameter.INT):
          value=self.getIntValue()
        if(self.getType()==CCopasiParameter.UINT):
          value=self.getUIntValue()
        if(self.getType()==CCopasiParameter.BOOL):
          value=self.getBoolValue()
        if(self.getType()==CCopasiParameter.GROUP):
          value=self.getGroupValue()
        if(self.getType()==CCopasiParameter.STRING):
          value=self.getStringValue()
        if(self.getType()==CCopasiParameter.KEY):
          value=self.getKeyValue()
        if(self.getType()==CCopasiParameter.FILE):
          value=self.getFileValue()
        if(self.getType()==CCopasiParameter.CN):
          value=self.getCNValue()
        return value            
  %}

}

%extend CTimeSeries
{
  %pythoncode
  %{

      def getTitles(self):
        """Returns the titles of the variables in the time series
        as a python list.
        If the time series contains no variables, an empty list is returned.
        """
        result=[]
        x=self.getNumVariables();
        for index in range(0,x):
            result.append(self.getTitle(index))
        return result;

      def getDataForIndex(self,index):
        """Returns the complete time course particle number data for the variable with the given index.
        The index has to be an integer type, otherwise an AttributeError is raised.

        If the given index is invalid, None is returned.
        """
        if type(index) != types.IntType:
            raise AttributeError("index argument to getConcentrationDataForIndex must be an int")
        result=None
        x=self.getNumVariables()
        if (index >= 0) and (index < x):
          result=[]
          y=self.getRecordedSteps()
          for step in range(0,y):
            result.append(self.getData(step,index))
        return result;

      def getConcentrationDataForIndex(self,index):
        """Returns the complete time course concentration data for the variable with the given index.
        The index has to be an integer type, otherwise an AttributeError is raised.

        If the given index is invalid, None is returned.
        """
        if type(index) != types.IntType:
            raise AttributeError("index argument to getConcentrationDataForIndex must be an int")
        result=None
        x=self.getNumVariables()
        if (index >= 0) and (index < x):
          result=[]
          y=self.getRecordedSteps()
          for step in range(0,y):
            result.append(self.getConcentrationData(step,index))
        return result;

      def getDataForObject(self,object):
        """Returns the complete time course particle number data for the variable corresponding to the given object.
        The key of the object must match the key of one of the variables of the time course as returned by the getKey method.

        If no fitting key is found, None is returned.

        The object argument must be an instance of CCopasiObject, otherwise an AttributeError is raised. 
        """
        if not isinstance(object,CCopasiObject):
            raise AttributeError("object argument to getConcentrationDataForObject must be an instance of CCopasiObject")
        result=None
        x=self.getNumVariables()
        for v in range(0,x):
            if self.getKey(v) == object.getKey():
                break
        if v != x:
            result=self.getDataForIndex(v)
        return result;

      def getConcentrationDataForObject(self,object):
        """Returns the complete time course concentration data for the variable corresponding to the given object.
        The key of the object must match the key of one of the variables of the time course as returned by the getKey method.

        If no fitting key is found, None is returned.
        
        The object argument must be an instance of CCopasiObject, otherwise an AttributeError is raised. 
        """
        if not isinstance(object,CCopasiObject):
            raise AttributeError("object argument to getConcentrationDataForObject must be an instance of CCopasiObject")
        result=None
        x=self.getNumVariables()
        for v in range(0,x):
            if self.getKey(v) == object.getKey():
                break
        if v != x:
            result=self.getConcentrationDataForIndex(v)
        return result;

  %}
}



