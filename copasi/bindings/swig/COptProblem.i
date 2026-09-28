// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/optimization/COptProblem.h"

%}

%ignore COptProblem::ValidSubtasks;

%extend COptProblem {
  %{
    using COptProblem_ValidSubtasks = decltype(COptProblem::ValidSubtasks);
    using COptProblem_ValidSubtasks_Map = CBidirectionalMap< COptProblem_ValidSubtasks::EnumType, COptProblem_ValidSubtasks::AnnotationType, COptProblem_ValidSubtasks::Size >;
    using COptProblem_ValidSubtasks_AnnotationType = CEnumAnnotation< COptProblem_ValidSubtasks_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const COptProblem_ValidSubtasks_AnnotationType& getValidSubtasks() {
    return COptProblem::ValidSubtasks;
  }

  COptItem & addOptItem(const CCommonName & objectCN)
  {
    return $self->addOptItem(CRegisteredCommonName(objectCN));
  }
  
  COptItem & addOptItem(const std::string & objectCN)
  {
    return $self->addOptItem(CRegisteredCommonName(objectCN));
  }

  COptItem& addOptConstraint(const CCommonName & objectCN)
  {
    return $self->addOptConstraint(CRegisteredCommonName(objectCN));
  }

  COptItem& addOptConstraint(const std::string & objectCN)
  {
    return $self->addOptConstraint(CRegisteredCommonName(objectCN));
  }
}

typedef std::vector<COptItem*> OptItemStdVector;

%ignore operator<<(std::ostream& os, const COptProblem& o);

%ignore COptProblem::getVariableSize() const;
//%ignore COptProblem::setCallBack;
%ignore COptProblem::getCalculateVariableUpdateMethods;

%template(FloatCVector) CVector<C_FLOAT64>;

%include "optimization/COptProblem.h"

