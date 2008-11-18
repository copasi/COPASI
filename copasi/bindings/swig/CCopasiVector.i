// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiVector.i,v $ 
//   $Revision: 1.21.6.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/18 09:43:24 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CCopasiVector.h"

%}

%ignore operator<< ;
%ignore operator<< <>;

%rename(addCopy) CCopasiVector::add(const CType&);

%include "utilities/CCopasiVector.h"

%extend CCopasiVector
{
  virtual value_type& get(unsigned C_INT32 index)
  {
      return (*self)[index];
  }

}



%extend CCopasiVectorN
{
  virtual value_type& getByName(const std::string& name)
  {
      return (*self)[name];
  }
}

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

%rename(removeObject) CCopasiVector<CEvaluationTree>::remove(CCopasiObject* pObject);
%rename(removeByName) CCopasiVectorN<CEvaluationTree>::remove(const std::string& name);
%rename(getIndexByName) CCopasiVectorN<CEvaluationTree>::getIndex(const std::string& name) const;

%template(CEvaluationTreeStdVector) std::vector<CEvaluationTree*>;
%template(CEvaluationTreeVector) CCopasiVector<CEvaluationTree>;
%template(CEvaluationTreeVectorN) CCopasiVectorN<CEvaluationTree>;

%rename(removeObject) CCopasiVector<CChemEqElement>::remove(CCopasiObject* pObject);

%template(CChemEqElementStdVector) std::vector<CChemEqElement*>;
%template(CChemEqElementVector) CCopasiVector<CChemEqElement>;

%template(ParameterVector) std::vector<CCopasiParameter*>;

%template(IntStdVector) std::vector<C_INT32>;

%template(StringStdVector) std::vector<std::string>;
%template(VectorOfStringVectors) std::vector<std::vector<std::string> >;

%template(FloatStdVector) std::vector<C_FLOAT64>;

%template(OptItemStdVector) std::vector<COptItem*>;

%template(ContainerStdVector) std::vector<CCopasiContainer*>;

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

typedef std::vector<CFunction> CFunctionStdVector;

typedef CCopasiVector<CChemEqElement> CChemEqElementVector;

typedef std::vector<C_INT32> IntStdVector;

typedef std::vector<C_FLOAT64> FloatStdVector;

typedef std::vector<COptItem*> OptItemStdVector;

typedef std::vector<std::string> StringStdVector;
typedef std::vector<std::vector<std::string> > VectorOfStringVectors;

typedef std::vector<CCopasiContainer*> ContainerStdVector;

