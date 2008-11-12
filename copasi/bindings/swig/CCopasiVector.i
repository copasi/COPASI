// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiVector.i,v $ 
//   $Revision: 1.21.6.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
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

%ignore operator<< <>;

%include "utilities/CCopasiVector.h"


%rename(removeObject) remove(CCopasiObject* pObject);

%extend CCopasiVector
{
  virtual value_type& get(unsigned C_INT32 index)
  {
      return (*self)[index];
  }

}



%rename(removeByName) remove(const std::string& name);
%rename(getIndexByName) getIndex(const std::string& name) const;

%extend CCopasiVectorN
{
  virtual value_type& getByName(const std::string& name)
  {
      return (*self)[name];
  }
}


%template(TaskStdVector) std::vector<CCopasiTask*>;
%template(TaskVector) CCopasiVector<CCopasiTask>;
%template(TaskVectorN) CCopasiVectorN<CCopasiTask>;

%template(ModelValueStdVector) std::vector<CModelValue*>;
%template(ModelValueVector) CCopasiVector<CModelValue>;
%template(ModelValueVectorN) CCopasiVectorN<CModelValue>;

%template(ReportDefinitionStdVector) std::vector<CReportDefinition*>;
%template(ReportDefinitionVector) CCopasiVector<CReportDefinition>;
%template(ReportDefinitionVectorN) CCopasiVectorN<CReportDefinition>;

%template(MoietyStdVector) std::vector<CMoiety*>;
%template(MoietyVector) CCopasiVector<CMoiety>;

%template(MetabStdVector) std::vector<CMetab*>;
%template(MetabVector) CCopasiVector<CMetab>;
%template(MetabVectorN) CCopasiVectorN<CMetab>;
%template(MetabVectorNS) CCopasiVectorNS<CMetab>;

%template(CompartmentStdVector) std::vector<CCompartment*>;
%template(CompartmentVector) CCopasiVector<CCompartment>;
%template(CompartmentVectorN) CCopasiVectorN<CCompartment>;
%template(CompartmentVectorNS) CCopasiVectorNS<CCompartment>;

%template(ReactionStdVector) std::vector<CReaction*>;
%template(ReactionVector) CCopasiVector<CReaction>;
%template(ReactionVectorN) CCopasiVectorN<CReaction>;
%template(ReactionVectorNS) CCopasiVectorNS<CReaction>;

%template(ReportItemVector) std::vector<CRegisteredObjectName>;

%template(CFunctionStdVector) std::vector<CFunction*>;

%template(CEvaluationTreeStdVector) std::vector<CEvaluationTree*>;
%template(CEvaluationTreeVector) CCopasiVector<CEvaluationTree>;
%template(CEvaluationTreeVectorN) CCopasiVectorN<CEvaluationTree>;

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

