// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiVector.i,v $ 
//   $Revision: 1.27.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/07/27 09:02:55 $ 
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

%{

#include "utilities/CCopasiVector.h"
#include <layout/CLBase.h>
#include <layout/CLCurve.h>

%}

%ignore operator<< ;
//%ignore operator<< <>;

// for now we ignore the resize method since it uses the copy constructor of
// the item, which is not implemented for most items
// actually it is best to disable all methods that use resize as well
%ignore CCopasiVector::resize;
%ignore CCopasiVector::deepCopy;
%ignore CCopasiVector::deepCopy;
%ignore CCopasiVectorS::load;
%ignore CCopasiVectorNS::load;
%ignore CCopasiVector::CCopasiVector;

#ifdef SWIGJAVA
// disable some operator for Java to get rid of the warnings

%ignore CCopasiVector::operator [];
%ignore CCopasiVector::operator =;
%ignore CCopasiVectorN::operator =;
%ignore CCopasiVectorN::operator [];
%ignore CCopasiVector::begin();
%ignore CCopasiVector::begin() const;
%ignore CCopasiVector::end();
%ignore CCopasiVector::end() const;
#endif // SWIGJAVA


%rename(addCopy) CCopasiVector::add(const CType&);


%include "utilities/CCopasiVector.h"

// this extension makes the assumption hat only instances of classes
// that are derived from CCopasiObject are stored in a CCopasiVector
// This is not necessarily true, but right now this is the easiest way to maybe
// get a pointer to the correct type
%extend CCopasiVector
{
  virtual CCopasiObject* get(unsigned C_INT32 index)
  {
      return (CCopasiObject*)((*self)[index]);
  }

  // this method is needed because I haven't found out how to disown 
  // objects from java
  // Calling the parameter DISOWN should activate the DISOWN typemap
  // and pass ownership to the C++ side
  virtual bool addAndOwn(CType *DISOWN)
  {
      return self->add(DISOWN,true);
  }

#ifdef SWIGPYTHON
 size_t __len__() const
 {
    return self->size();
 }
#endif // SWIGPYTHON

}



// this extension makes the assumption hat only instances of classes
// that are derived from CCopasiObject are stored in a CCopasiVectorN
// This is not necessarily true, but right now this is the easiest way to maybe
// get a pointer to the correct type
%extend CCopasiVectorN
{
  virtual CCopasiObject* getByName(const std::string& name)
  {
      return (CCopasiObject*)((*self)[name]);
  }
}

%rename(removeObject) CCopasiVector<CEvent>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CEvent>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CEvent>::getIndex(const std::string& name) const;

%template(EventStdVector) std::vector<CEvent*>;
%template(EventVector) CCopasiVector<CEvent>;
%template(EventVectorN) CCopasiVectorN<CEvent>;

%rename(removeObject) CCopasiVector<CEventAssignment>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CEventAssignment>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CEventAssignment>::getIndex(const std::string& name) const;

%template(EventAssignmentStdVector) std::vector<CEventAssignment*>;
%template(EventAssignmentVector) CCopasiVector<CEventAssignment>;
%template(EventAssignmentVectorN) CCopasiVectorN<CEventAssignment>;

%rename(removeObject) CCopasiVector<CCopasiTask>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CCopasiTask>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CCopasiTask>::getIndex(const std::string& name) const;

%template(TaskStdVector) std::vector<CCopasiTask*>;
%template(TaskVector) CCopasiVector<CCopasiTask>;
%template(TaskVectorN) CCopasiVectorN<CCopasiTask>;

%rename(removeObject) CCopasiVector<CModelValue>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CModelValue>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CModelValue>::getIndex(const std::string& name) const;

%template(ModelValueStdVector) std::vector<CModelValue*>;
%template(ModelValueVector) CCopasiVector<CModelValue>;
%template(ModelValueVectorN) CCopasiVectorN<CModelValue>;

%rename(removeObject) CCopasiVector<CReportDefinition>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CReportDefinition>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CReportDefinition>::getIndex(const std::string& name) const;

%template(ReportDefinitionStdVector) std::vector<CReportDefinition*>;
%template(ReportDefinitionVector) CCopasiVector<CReportDefinition>;
%template(ReportDefinitionVectorN) CCopasiVectorN<CReportDefinition>;

%rename(removeObject) CCopasiVector<CMoiety>::remove(CCopasiObject* pObject);

%template(MoietyStdVector) std::vector<CMoiety*>;
%template(MoietyVector) CCopasiVector<CMoiety>;

%rename(removeObject) CCopasiVector<CMetab>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CMetab>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CMetab>::getIndex(const std::string& name) const;

%template(MetabStdVector) std::vector<CMetab*>;
%template(MetabVector) CCopasiVector<CMetab>;
%template(MetabVectorN) CCopasiVectorN<CMetab>;
%template(MetabVectorNS) CCopasiVectorNS<CMetab>;

%rename(removeObject) CCopasiVector<CCompartment>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CCompartment>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CCompartment>::getIndex(const std::string& name) const;

%template(CompartmentStdVector) std::vector<CCompartment*>;
%template(CompartmentVector) CCopasiVector<CCompartment>;
%template(CompartmentVectorN) CCopasiVectorN<CCompartment>;
%template(CompartmentVectorNS) CCopasiVectorNS<CCompartment>;

%rename(removeObject) CCopasiVector<CReaction>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CReaction>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CReaction>::getIndex(const std::string& name) const;

%template(ReactionStdVector) std::vector<CReaction*>;
%template(ReactionVector) CCopasiVector<CReaction>;
%template(ReactionVectorN) CCopasiVectorN<CReaction>;
%template(ReactionVectorNS) CCopasiVectorNS<CReaction>;

%template(ReportItemVector) std::vector<CRegisteredObjectName>;

%template(CFunctionStdVector) std::vector<CFunction*>;
%template(CFunctionVector) CCopasiVector<CFunction>;
%template(CFunctionVectorN) CCopasiVectorN<CFunction>;

%rename(removeObject) CCopasiVector<CEvaluationTree>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CEvaluationTree>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CEvaluationTree>::getIndex(const std::string& name) const;

%template(CEvaluationTreeStdVector) std::vector<CEvaluationTree*>;
%template(CEvaluationTreeVector) CCopasiVector<CEvaluationTree>;
%template(CEvaluationTreeVectorN) CCopasiVectorN<CEvaluationTree>;

%rename(removeObject) CCopasiVector<CChemEqElement>::remove(CCopasiObject* pObject);

%template(CChemEqElementStdVector) std::vector<CChemEqElement*>;
%template(CChemEqElementVector) CCopasiVector<CChemEqElement>;

%template(DataModelVector) CCopasiVector<CCopasiDataModel>;

%template(ParameterVector) std::vector<CCopasiParameter*>;

%template(IntStdVector) std::vector<C_INT32>;
%template(UIntStdVector) std::vector<unsigned int>;

%template(StringStdVector) std::vector<std::string>;
%template(VectorOfStringVectors) std::vector<std::vector<std::string> >;

%template(FloatStdVector) std::vector<C_FLOAT64>;

%template(OptItemStdVector) std::vector<COptItem*>;

%template(ContainerStdVector) std::vector<CCopasiContainer*>;

%template(PointStdVector) std::vector<CLPoint>;

%template(LineSegmentStdVector) std::vector<CLLineSegment>;

%template(FittingPointVector) CCopasiVector<CFittingPoint>;

%template(BiologicalDescriptionVector) CCopasiVector<CBiologicalDescription>;
%template(CreatorVector) CCopasiVector<CCreator>;
%template(ReferenceVector) CCopasiVector<CReference>;
%template(ModificationVector) CCopasiVector<CModification>;

typedef CCopasiVectorN<CEvent> EventVectorN;

typedef CCopasiVectorN<CEventAssignment> EventAssignmentVectorN;

typedef CCopasiVectorN<CCopasiTask> TaskVectorN;

typedef CCopasiVectorN<CModelValue> ModelValueVectorN;

typedef CCopasiVector<CMoiety> MoietyVector;

typedef CCopasiVector<CMetab> MetabVector;
typedef CCopasiVectorNS<CMetab> MetabVectorNS;

typedef CCopasiVectorNS<CCompartment> CompartmentVectorNS;

typedef CCopasiVectorNS<CReaction> ReactionVectorNS;

typedef std::vector<CRegisteredObjectName> ReportItemVector;
typedef std::vector<CCopasiParameter*> ParameterVector;

typedef CCopasiVectorN<CEvaluationTree> CEvaluationTreeVectorN;

typedef std::vector<CFunction*> CFunctionStdVector;
typedef CCopasiVector<CFunction> CFunctionVector;
typedef CCopasiVectorN<CFunction> CFunctionVectorN;

typedef CCopasiVector<CChemEqElement> CChemEqElementVector;

typedef CCopasiVector<CCopasiDataModel> DataModelVector;

typedef std::vector<C_INT32> IntStdVector;
typedef std::vector<unsigned int> UIntStdVector;

typedef std::vector<C_FLOAT64> FloatStdVector;

typedef std::vector<COptItem*> OptItemStdVector;

typedef std::vector<std::string> StringStdVector;
typedef std::vector<std::vector<std::string> > VectorOfStringVectors;

typedef std::vector<CCopasiContainer*> ContainerStdVector;

typedef std::vector<CLPoint> PointStdVector;

typedef std::vector<CLLineSegment> LineSegmentStdVector;

typedef CCopasiVector<CFittingPoint> FittingPointVector;

typedef CCopasiVector<CBiologicalDescription> BiologicalDescriptionVector;
typedef CCopasiVector<CCreator> CreatorVector;
typedef CCopasiVector<CReference> ReferenceVector;
typedef CCopasiVector<CModification> ModificationVector;

