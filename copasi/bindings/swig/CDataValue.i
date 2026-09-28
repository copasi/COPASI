// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/undo/CDataValue.h"
%}

%ignore CDataValue::TypeName;
%ignore CDataValue::CDataValue(const CDataValue::Type &);
%ignore CDataValue::CDataValue(const Type &);
%template(CDataValueStdVector) std::vector<CDataValue>;

%extend CDataValue {
  // 1. Hide the C++17 type deduction from SWIG, but expose it to the C++ wrapper compiler
  %{
    using CDataValue_TypeName = decltype(CDataValue::TypeName);
    using CDataValue_TypeName_Map = CBidirectionalMap< CDataValue_TypeName::EnumType, CDataValue_TypeName::AnnotationType, CDataValue_TypeName::Size >;
    using CDataValue_TypeName_AnnotationType = CEnumAnnotation< CDataValue_TypeName_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CDataValue_TypeName_AnnotationType& getTypeName() {
    return CDataValue::TypeName;
  }
}


%include "copasi/undo/CDataValue.h"



