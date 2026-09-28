// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/utilities/CTaskEnum.h"
%}

%ignore CTaskEnum::TaskName;
%ignore CTaskEnum::TaskXML;
%ignore CTaskEnum::MethodName;
%ignore CTaskEnum::MethodXML;

%extend CTaskEnum {
  %{
    using CTaskEnum_TaskName = decltype(CTaskEnum::TaskName);
    using CTaskEnum_TaskName_Map = CBidirectionalMap< CTaskEnum_TaskName::EnumType, CTaskEnum_TaskName::AnnotationType, CTaskEnum_TaskName::Size >;
    using CTaskEnum_TaskName_AnnotationType = CEnumAnnotation< CTaskEnum_TaskName_Map >;

    using CTaskEnum_MethodName = decltype(CTaskEnum::MethodName);
    using CTaskEnum_MethodName_Map = CBidirectionalMap< CTaskEnum_MethodName::EnumType, CTaskEnum_MethodName::AnnotationType, CTaskEnum_MethodName::Size >;
    using CTaskEnum_MethodName_AnnotationType = CEnumAnnotation< CTaskEnum_MethodName_Map >;
  %}

  const CTaskEnum_TaskName_AnnotationType& getTaskName() {
    return CTaskEnum::TaskName;
  }

  const CTaskEnum_MethodName_AnnotationType& getMethodName() {
    return CTaskEnum::MethodName;
  }
}

%include "copasi/utilities/CTaskEnum.h"



