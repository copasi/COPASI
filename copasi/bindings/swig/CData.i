// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/undo/CData.h"
%}

%ignore CData::PropertyName;
%template(CDataStdVector) std::vector<CData>;

%extend CData {
  // 1. Hide the C++17 type deduction from SWIG, but expose it to the C++ wrapper compiler
  %{
    using CData_PropertyName = decltype(CData::PropertyName);
    using CData_PropertyName_Map = CBidirectionalMap< CData_PropertyName::EnumType, CData_PropertyName::AnnotationType, CData_PropertyName::Size >;
    using CData_PropertyName_AnnotationType = CEnumAnnotation< CData_PropertyName_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CData_PropertyName_AnnotationType& getPropertyName() {
    return CData::PropertyName;
  }
}


%include "copasi/undo/CData.h"



