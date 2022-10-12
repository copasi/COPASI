// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 



%ignore CDataVector::remove(const size_t & index);

%{

#include "copasi/core/CDataVector.h"
#include "copasi/plot/CPlotSpecification.h"
#include <copasi/elementaryFluxModes/CFluxMode.h>
#include <copasi/layout/CLBase.h>
#include <copasi/layout/CLCurve.h>
#include <copasi/model/CObjectLists.h>

%}

%ignore operator<< ;
//%ignore operator<< <>;

// for now we ignore the resize method since it uses the copy constructor of
// the item, which is not implemented for most items
// actually it is best to disable all methods that use resize as well
%ignore CDataVector::resize;
%ignore CDataVector::deepCopy;
%ignore CDataVector::deepCopy;
%ignore CDataVectorS::load;
%ignore CDataVectorNS::load;
%ignore CDataVector::CDataVector;
%ignore CObjectLists::ListTypeName;
%ignore CObjectLists::getListOfObjects;
%ignore CObjectLists::getListOfConstObjects;
%ignore CObjectLists::getEventTargets;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// disable some operator for Java to get rid of the warnings

%ignore CDataVector::operator [];
%ignore CDataVector::operator =;
%ignore CDataVectorN::operator =;
%ignore CDataVectorN::operator [];
%ignore CDataVector::begin();
%ignore CDataVector::begin() const;
%ignore CDataVector::end();
%ignore CDataVector::end() const;
#endif // SWIGJAVA || CSHARP


%rename(addCopy) CDataVector::add(const CType&);


%include "copasi/core/CDataVector.h"

// this extension makes the assumption hat only instances of classes
// that are derived from CDataObject are stored in a CDataVector
// This is not necessarily true, but right now this is the easiest way to maybe
// get a pointer to the correct type
%extend CDataVector
{
  virtual void remove(unsigned C_INT32 index)
  {
   if (self == NULL ||  self->size() == 0) return;
   try
   {
     self->remove(index);
   }
   catch(...)
   {
   }
  }
  
  virtual CDataObject* get(unsigned C_INT32 index)
  {
    try
    {
        return (CDataObject*)&((*self)[index]);
    }
    catch(...)
    {
      return NULL;
    }
  }

  // this method is needed because I haven't found out how to disown
  // objects from java
  // Calling the parameter DISOWN should activate the DISOWN typemap
  // and pass ownership to the C++ side
  virtual bool addAndOwn(CType *DISOWN)
  {
      return self->add(DISOWN,true);
  }

  virtual bool removeObject(CDataObject * pObject)
  {
    try 
    {
      return self->remove(pObject);
    }
    catch(...)
    {
      return false;
    }
  }

#ifdef SWIGPYTHON
 size_t __len__() const
 {
    return self->size();
 }

 CDataObject* __getitem__(unsigned int index) 
 {
    try
    {
        return (CDataObject*)&((*self)[index]);
    }
    catch(...)
    {
      return NULL;
    }

 }

#endif // SWIGPYTHON

}



// this extension makes the assumption hat only instances of classes
// that are derived from CDataObject are stored in a CDataVectorN
// This is not necessarily true, but right now this is the easiest way to maybe
// get a pointer to the correct type
%extend CDataVectorN
{
  virtual CDataObject* getByName(const std::string& name)
  {
  try
    {
      return (CDataObject*)&((*self)[name]);
    }
    catch(...)
    {
      return NULL;
    }
  }

  virtual bool removeByName(const std::string& name)
  {
    try
    {
      self->remove(name);
      return true;
    }
    catch(...)
    {
      return false;
    }
  }

  virtual size_t getIndexByName(const std::string &name) const
  {
    try
    {
      return self->getIndex(name);
    }
    catch(...)
    {
      return C_INVALID_INDEX;
    }
  }
  
#ifdef SWIGPYTHON 

 CDataObject* __getitem__(const std::string& name) 
 {
  try
    {
      return (CDataObject*)&((*self)[name]);
    }
    catch(...)
    {
      return NULL;
    }
 }

 CDataObject* __getitem__(unsigned int index) 
 {
    try
    {
        return (CDataObject*)&((*self)[index]);
    }
    catch(...)
    {
      return NULL;
    }
 }

#endif // SWIGPYTHON

}

%rename(removeObject) CDataVector<CEvent>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CEvent>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CEvent>::getIndex(const std::string& name) const;

%template(EventStdVector) std::vector<CEvent*>;
%template(EventVector) CDataVector<CEvent>;
%template(EventVectorN) CDataVectorN<CEvent>;

%rename(removeObject) CDataVector<CEventAssignment>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CEventAssignment>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CEventAssignment>::getIndex(const std::string& name) const;

%template(EventAssignmentStdVector) std::vector<CEventAssignment*>;
%template(EventAssignmentVector) CDataVector<CEventAssignment>;
%template(EventAssignmentVectorN) CDataVectorN<CEventAssignment>;

%rename(removeObject) CDataVector<CCopasiTask>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CCopasiTask>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CCopasiTask>::getIndex(const std::string& name) const;

%template(TaskStdVector) std::vector<CCopasiTask*>;
%template(TaskVector) CDataVector<CCopasiTask>;
%template(TaskVectorN) CDataVectorN<CCopasiTask>;

%rename(removeObject) CDataVector<CModelValue>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CModelValue>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CModelValue>::getIndex(const std::string& name) const;

%template(FluxModeStdVector) std::vector<CFluxMode*>;


%template(ModelValueStdVector) std::vector<CModelValue*>;
%template(ModelValueVector) CDataVector<CModelValue>;
%template(ModelValueVectorN) CDataVectorN<CModelValue>;

%rename(removeObject) CDataVector<CReportDefinition>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CReportDefinition>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CReportDefinition>::getIndex(const std::string& name) const;

%template(ReportDefinitionStdVector) std::vector<CReportDefinition*>;
%template(ReportDefinitionVector) CDataVector<CReportDefinition>;
%template(ReportDefinitionVectorN) CDataVectorN<CReportDefinition>;

%rename(removeObject) CDataVector<CPlotSpecification>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CPlotSpecification>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CPlotSpecification>::getIndex(const std::string& name) const;

%template(OutputDefinitionStdVector) std::vector<CPlotSpecification*>;
%template(PlotDataChannelSpecStdVector) std::vector<CPlotDataChannelSpec>;
%template(OutputDefinitionVector) CDataVector<CPlotSpecification>;
%template(OutputDefinitionVectorN) CDataVectorN<CPlotSpecification>;

%rename(removeObject) CDataVector<CPlotItem>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CPlotItem>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CPlotItem>::getIndex(const std::string& name) const;

%template(PlotItemVector) CDataVector<CPlotItem>;
%template(PlotItemVectorN) CDataVectorN<CPlotItem>;


%rename(removeObject) CDataVector<CMoiety>::remove(CDataObject* pObject);

%template(MoietyStdVector) std::vector<CMoiety*>;
%template(MoietyVector) CDataVector<CMoiety>;

%rename(removeObject) CDataVector<CMetab>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CMetab>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CMetab>::getIndex(const std::string& name) const;

%template(MetabStdVector) std::vector<CMetab*>;
%template(MetabVector) CDataVector<CMetab>;
%template(MetabVectorN) CDataVectorN<CMetab>;
%template(MetabVectorNS) CDataVectorNS<CMetab>;

%rename(removeObject) CDataVector<CCompartment>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CCompartment>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CCompartment>::getIndex(const std::string& name) const;

%template(CompartmentStdVector) std::vector<CCompartment*>;
%template(CompartmentVector) CDataVector<CCompartment>;
%template(CompartmentVectorN) CDataVectorN<CCompartment>;
%template(CompartmentVectorNS) CDataVectorNS<CCompartment>;

%rename(removeObject) CDataVector<CModelParameterSet>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CModelParameterSet>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CModelParameterSet>::getIndex(const std::string& name) const;
%template(ModelParameterSetVector) CDataVector<CModelParameterSet>;
%template(ModelParameterSetVectorN) CDataVectorN<CModelParameterSet>;


%rename(removeObject) CDataVector<CReaction>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CReaction>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CReaction>::getIndex(const std::string& name) const;

%template(ReactionStdVector) std::vector<CReaction*>;
%template(ReactionVector) CDataVector<CReaction>;
%template(ReactionVectorN) CDataVectorN<CReaction>;
%template(ReactionVectorNS) CDataVectorNS<CReaction>;

%template(ReportItemVector) std::vector<CRegisteredCommonName>;

%template(CFunctionStdVector) std::vector<CFunction*>;
%template(CFunctionVector) CDataVector<CFunction>;
%template(CFunctionVectorN) CDataVectorN<CFunction>;
%template(CFunctionVectorNS) CDataVectorNS<CFunction>;

%rename(removeObject) CDataVector<CEvaluationTree>::remove(CDataObject* pObject);
%rename(removeByName) CDataVectorN<CEvaluationTree>::remove(const std::string& name);
%rename(getIndexByName) CDataVectorN<CEvaluationTree>::getIndex(const std::string& name) const;

%template(CEvaluationTreeStdVector) std::vector<CEvaluationTree*>;
%template(CEvaluationTreeVector) CDataVector<CEvaluationTree>;
%template(CEvaluationTreeVectorN) CDataVectorN<CEvaluationTree>;

%rename(removeObject) CDataVector<CChemEqElement>::remove(CDataObject* pObject);

%template(CChemEqElementStdVector) std::vector<CChemEqElement*>;
%template(CChemEqElementVector) CDataVector<CChemEqElement>;

%template(DataModelVector) CDataVector<CDataModel>;

%template(ParameterVector) std::vector<CCopasiParameter*>;

%template(IntStdVector) std::vector<C_INT32>;

#if !SWIGPYTHON && !SWIGR && !SWIGOCTAVE
%template(UIntStdVector) std::vector<unsigned int>;
#endif

#if !SWIGR
%template(SizeTStdVector) std::vector<size_t>;
#endif

%template(StringStdVector) std::vector<std::string>;
%template(VectorOfStringVectors) std::vector<std::vector<std::string> >;

%template(FloatStdVector) std::vector<C_FLOAT64>;

%template(OptItemStdVector) std::vector<COptItem*>;

%template(ContainerStdVector) std::vector<CDataContainer*>;

%template(PointStdVector) std::vector<CLPoint>;

%template(LineSegmentStdVector) std::vector<CLLineSegment>;

%template(FittingPointVector) CDataVector<CFittingPoint>;

%template(BiologicalDescriptionVector) CDataVector<CBiologicalDescription>;
%template(CreatorVector) CDataVector<CCreator>;
%template(ReferenceVector) CDataVector<CReference>;
%template(ModificationVector) CDataVector<CModification>;

%template(ObjectListTypeStdVector) std::vector<CObjectLists::ListType>;

typedef CDataVectorN<CEvent> EventVectorN;

typedef CDataVectorN<CEventAssignment> EventAssignmentVectorN;

typedef CDataVectorN<CCopasiTask> TaskVectorN;

typedef CDataVectorN<CModelValue> ModelValueVectorN;

typedef CDataVector<CMoiety> MoietyVector;

typedef CDataVector<CMetab> MetabVector;
typedef CDataVectorNS<CMetab> MetabVectorNS;

typedef CDataVectorNS<CCompartment> CompartmentVectorNS;

typedef CDataVectorNS<CReaction> ReactionVectorNS;

typedef std::vector<CRegisteredCommonName> ReportItemVector;
typedef std::vector<CCopasiParameter*> ParameterVector;

typedef CDataVectorN<CEvaluationTree> CEvaluationTreeVectorN;

typedef std::vector<CFunction*> CFunctionStdVector;
typedef CDataVector<CFunction> CFunctionVector;
typedef CDataVectorN<CFunction> CFunctionVectorN;

typedef CDataVector<CChemEqElement> CChemEqElementVector;

typedef CDataVector<CDataModel> DataModelVector;

#if !SWIGPYTHON && !SWIGR
typedef std::vector<C_INT32> IntStdVector;
typedef std::vector<unsigned int> UIntStdVector;
#endif
typedef std::vector<size_t> SizeTStdVector;
typedef std::vector<C_FLOAT64> FloatStdVector;

typedef std::vector<COptItem*> OptItemStdVector;

typedef std::vector<std::string> StringStdVector;
typedef std::vector<std::vector<std::string> > VectorOfStringVectors;

typedef std::vector<CDataContainer*> ContainerStdVector;

typedef std::vector<CLPoint> PointStdVector;

typedef std::vector<CLLineSegment> LineSegmentStdVector;

typedef CDataVector<CFittingPoint> FittingPointVector;

typedef CDataVector<CBiologicalDescription> BiologicalDescriptionVector;
typedef CDataVector<CCreator> CreatorVector;
typedef CDataVector<CReference> ReferenceVector;
typedef CDataVector<CModification> ModificationVector;

typedef std::vector<CObjectLists::ListType> ObjectListTypeStdVector;
