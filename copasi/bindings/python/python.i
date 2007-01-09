

/**
 * Convert CEvaluationTree objects into the most specific type possible.
 */
%typemap(out) CEvaluationTree*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCEvaluationTree($1), 0);
}

/**
 * Convert Task objects into the most specific type possible.
 */
%typemap(out) CCopasiTask*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForTask($1), 0);
}

/**
 * Convert Problem objects into the most specific type possible.
 */
%typemap(out) CCopasiProblem*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForProblem($1), 0);
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

%init %{

#include "report/CCopasiContainer.h"
// Taken from CopasiSE.cpp

// Create the root container
CCopasiContainer::init();

// Create the global data model
CCopasiDataModel::Global = new CCopasiDataModel;

%}

%pythoncode %{

TriUnspecified=-1
TriFalse=0
TriTrue=1

CCopasiDataModel.GLOBAL=_COPASI.CCopasiDataModel_Global_get()

CCopasiObjectName.escape=_COPASI.CCopasiObjectName_escape
CCopasiObjectName.unescape=_COPASI.CCopasiObjectName_unescape

CCopasiMethod.TypeNameToEnum=_COPASI.CCopasiMethod_TypeNameToEnum

CCopasiContainer.ObjectFromName=_COPASI.CCopasiContainer_ObjectFromName

CEvaluationTree.create=_COPASI.CEvaluationTree_create
CEvaluationTree.copy=_COPASI.CEvaluationTree_copy

COutputAssistant.getListOfDefaultOutputDescriptions=_COPASI.COutputAssistant_getListOfDefaultOutputDescriptions
COutputAssistant.getDefaultReportIndex=_COPASI.COutputAssistant_getDefaultReportIndex
COutputAssistant.getItemName=_COPASI.COutputAssistant_getItemName
COutputAssistant.getItem=_COPASI.COutputAssistant_getItem
COutputAssistant.createDefaultOutput=_COPASI.COutputAssistant_createDefaultOutput

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


