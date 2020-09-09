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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%include "local-contrib.i"


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
%typemap(out) CFitItem*, CFitItem&
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCFitItem($1), 0);
}

/**
 * Convert COptItem objects into the most specific type possible.
 */
%typemap(out) COptItem*, COptItem&
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCOptItem($1), 0);
}

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

/**
 * Convert CObjectInterface objects into the most specific type possible.
 */
%typemap(out) CObjectInterface*
{
  $result = SWIG_NewPointerObj($1, GetDowncastSwigTypeForCObjectInterface($1), 0);
}



%pythoncode
%{
import types
import sys 
%}

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

%pythoncode %{

TriUnspecified=-1
TriFalse=0
TriTrue=1

CRootContainer.init=_COPASI.CRootContainer_init
CRootContainer.destroy=_COPASI.CRootContainer_destroy
CRootContainer.getRoot=_COPASI.CRootContainer_getRoot
CRootContainer.getFunctionList=_COPASI.CRootContainer_getFunctionList
CRootContainer.getDatamodelList=_COPASI.CRootContainer_getDatamodelList
CRootContainer.addDatamodel=_COPASI.CRootContainer_addDatamodel
CRootContainer.getUndefinedFunction=_COPASI.CRootContainer_getUndefinedFunction
CRootContainer.getKeyFactory=_COPASI.CRootContainer_getKeyFactory
CRootContainer.removeDatamodel=_COPASI.CRootContainer_removeDatamodel
CRootContainer.removeDatamodelWithIndex=_COPASI.CRootContainer_removeDatamodelWithIndex

CCommonName.escape=_COPASI.CCommonName_escape
CCommonName.unescape=_COPASI.CCommonName_unescape

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

%extend CCommonName
{
  %pythoncode
  %{
      def __str__(self):
        return self.getString();
      def __repr__(self):
        return self.getString();
  %}
}

%extend CRegisteredCommonName
{
  %pythoncode
  %{
      def __str__(self):
        return self.getString();
      def __repr__(self):
        return self.getString();
  %}
}

%extend CCopasiParameter
{
  %pythoncode
  %{

      def setValue(self,arg):
        if sys.version_info >= (3, 0): 
          return self.setValueV3(arg)
        return self.setValueV2(arg);
        
      def setValueV3(self,arg):
        result=False
        if(type(arg)==int):
           if((self.getType()==CCopasiParameter.Type_INT) or (arg < 0)):
             result=self.setIntValue(arg)
           else:
             result=self.setUIntValue(arg) 
        elif(type(arg)==float):
           result=self.setDblValue(arg) 
        elif(type(arg)==bool):
           result=self.setBoolValue(arg) 
        elif(type(arg)==bytes):
           result=self.setStringValue(arg) 
        elif(arg.__class__==CRegisteredCommonName):
           result=self.setCNValue(arg) 
        elif(arg.__class__ == ParameterVector):
           result=self.setGroupValue(arg) 
        return result;

      def setValueV2(self,arg):
        result=False
        if(type(arg)==types.IntType):
           if((self.getType()==CCopasiParameter.Type_INT) or (arg < 0)):
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

        The object argument must be an instance of CDataObject, otherwise an AttributeError is raised. 
        """
        if not isinstance(object,CDataObject):
            raise AttributeError("object argument to getConcentrationDataForObject must be an instance of CDataObject")
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
        
        The object argument must be an instance of CDataObject, otherwise an AttributeError is raised. 
        """
        if not isinstance(object,CDataObject):
            raise AttributeError("object argument to getConcentrationDataForObject must be an instance of CDataObject")
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


%pythoncode
%{

class _VectorIterator:
    def __init__(self, vector):
        #type: (COPASI.MetabVector) -> None
        self.current = 0
        self.high = vector.size() - 1
        self.vector = vector

    def __iter__(self):
        return self

    def __next__(self):
        return self.next()

    def next(self):
        if self.current > self.high:
            raise StopIteration
        else:
            self.current += 1
            return self.vector.get(self.current - 1)

def __add_iterator(self):
    return _VectorIterator(self)


BiologicalDescriptionVector.__iter__ = __add_iterator
CChemEqElementVector.__iter__ = __add_iterator
CDataObjectVector.__iter__ = __add_iterator
CEvaluationTreeVector.__iter__ = __add_iterator
CEvaluationTreeVectorN.__iter__ = __add_iterator
CFunctionVector.__iter__ = __add_iterator
CFunctionVectorN.__iter__ = __add_iterator
CFunctionVectorNS.__iter__ = __add_iterator
CLRelAbsVector.__iter__ = __add_iterator
COutputDefinitionVector.__iter__ = __add_iterator
CReportDefinitionVector.__iter__ = __add_iterator
ColorDefinitionVector.__iter__ = __add_iterator
CompartmentGlyphVector.__iter__ = __add_iterator
CompartmentVector.__iter__ = __add_iterator
CompartmentVectorN.__iter__ = __add_iterator
CompartmentVectorNS.__iter__ = __add_iterator
CreatorVector.__iter__ = __add_iterator
DataModelVector.__iter__ = __add_iterator
EventAssignmentVector.__iter__ = __add_iterator
EventAssignmentVectorN.__iter__ = __add_iterator
EventVector.__iter__ = __add_iterator
EventVectorN.__iter__ = __add_iterator
FittingPointVector.__iter__ = __add_iterator
FloatCVector.__iter__ = __add_iterator
FloatVector.__iter__ = __add_iterator
FloatVectorCore.__iter__ = __add_iterator
GeneralGlyphVector.__iter__ = __add_iterator
GlobalRenderInformationVector.__iter__ = __add_iterator
GlobalStyleVector.__iter__ = __add_iterator
GradientBaseVector.__iter__ = __add_iterator
GradientStopVector.__iter__ = __add_iterator
GraphicalObjectVector.__iter__ = __add_iterator
LayoutVector.__iter__ = __add_iterator
LayoutVectorN.__iter__ = __add_iterator
LineEndingVector.__iter__ = __add_iterator
LocalStyleVector.__iter__ = __add_iterator
MetabGlyphVector.__iter__ = __add_iterator
MetabReferenceGlyphVector.__iter__ = __add_iterator
MetabVector.__iter__ = __add_iterator
MetabVectorN.__iter__ = __add_iterator
MetabVectorNS.__iter__ = __add_iterator
MethodSubTypeVector.__iter__ = __add_iterator
ModelParameterSetVector.__iter__ = __add_iterator
ModelParameterSetVectorN.__iter__ = __add_iterator
ModelValueVector.__iter__ = __add_iterator
ModelValueVectorN.__iter__ = __add_iterator
ModificationVector.__iter__ = __add_iterator
MoietyVector.__iter__ = __add_iterator
ObjectVector.__iter__ = __add_iterator
ObjectVectorCore.__iter__ = __add_iterator
OutputDefinitionVector.__iter__ = __add_iterator
OutputDefinitionVectorN.__iter__ = __add_iterator
ParameterVector.__iter__ = __add_iterator
PlotItemVector.__iter__ = __add_iterator
PlotItemVectorN.__iter__ = __add_iterator
ReactionGlyphVector.__iter__ = __add_iterator
ReactionVector.__iter__ = __add_iterator
ReactionVectorN.__iter__ = __add_iterator
ReactionVectorNS.__iter__ = __add_iterator
ReferenceGlyphVector.__iter__ = __add_iterator
ReferenceVector.__iter__ = __add_iterator
ReportDefinitionVector.__iter__ = __add_iterator
ReportDefinitionVectorN.__iter__ = __add_iterator
ReportItemVector.__iter__ = __add_iterator
SizeTVector.__iter__ = __add_iterator
SizeTVectorCore.__iter__ = __add_iterator
TaskSubTypeVector.__iter__ = __add_iterator
TaskVector.__iter__ = __add_iterator
TaskVectorN.__iter__ = __add_iterator
TextGlyphVector.__iter__ = __add_iterator
VectorOfStringVectors.__iter__ = __add_iterator


%}
