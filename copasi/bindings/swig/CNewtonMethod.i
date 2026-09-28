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

#include "copasi/steadystate/CNewtonMethod.h"

%}

%ignore CNewtonMethod::load;
%ignore CNewtonMethod::TargetCriterion;

%extend CNewtonMethod {
  %{
    using CNewtonMethod_TargetCriterion = decltype(CNewtonMethod::TargetCriterion);
    using CNewtonMethod_TargetCriterion_Map = CBidirectionalMap< CNewtonMethod_TargetCriterion::EnumType, CNewtonMethod_TargetCriterion::AnnotationType, CNewtonMethod_TargetCriterion::Size >;
    using CNewtonMethod_TargetCriterion_AnnotationType = CEnumAnnotation< CNewtonMethod_TargetCriterion_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CNewtonMethod_TargetCriterion_AnnotationType& getTargetCriterion() {
    return CNewtonMethod::TargetCriterion;
  }
}

%include "copasi/steadystate/CNewtonMethod.h"


