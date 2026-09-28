// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/core/CCore.h"
%}

%ignore CCore::FrameworkNames;

%extend CCore {
  // 1. Hide the C++17 type deduction from SWIG, but expose it to the C++ wrapper compiler
  %{
    using CCore_FrameworkNames = decltype(CCore::FrameworkNames);
    using CCore_FrameworkNames_Map = CBidirectionalMap< CCore_FrameworkNames::EnumType, CCore_FrameworkNames::AnnotationType, CCore_FrameworkNames::Size >;
    using CCore_FrameworkNames_AnnotationType = CEnumAnnotation< CCore_FrameworkNames_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CCore_FrameworkNames_AnnotationType& getFrameworkNames() {
    return CCore::FrameworkNames;
  }
}


%include "copasi/core/CCore.h"



