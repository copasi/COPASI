// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/randomGenerator/CConfigurableRNG.h"
%}

%ignore CConfigurableRNG::TypeAnnotation;
%ignore CConfigurableRNG::Conversion;

%extend CConfigurableRNG {
  // 1. Hide the C++17 type deduction from SWIG, but expose it to the C++ wrapper compiler
  %{
    using CConfigurableRNG_TypeAnnotation = decltype(CConfigurableRNG::TypeAnnotation);
    using CConfigurableRNG_TypeAnnotation_Map = CBidirectionalMap< CConfigurableRNG_TypeAnnotation::EnumType, CConfigurableRNG_TypeAnnotation::AnnotationType, CConfigurableRNG_TypeAnnotation::Size >;
    using CConfigurableRNG_TypeAnnotation_AnnotationType = CEnumAnnotation< CConfigurableRNG_TypeAnnotation_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CConfigurableRNG_TypeAnnotation_AnnotationType& getTypeAnnotation() {
    return CConfigurableRNG::TypeAnnotation;
  }
}


%include "copasi/randomGenerator/CConfigurableRNG.h"



