// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/undo/CUndoData.h"
%}

%ignore CUndoData::TypeName;

%extend CUndoData {
  %{
    using CUndoData_TypeName = decltype(CUndoData::TypeName);
    using CUndoData_TypeName_Map = CBidirectionalMap< CUndoData_TypeName::EnumType, CUndoData_TypeName::AnnotationType, CUndoData_TypeName::Size >;
    using CUndoData_TypeName_AnnotationType = CEnumAnnotation< CUndoData_TypeName_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CUndoData_TypeName_AnnotationType& getTypeName() {
    return CUndoData::TypeName;
  }
}


%include "copasi/undo/CUndoData.h"



