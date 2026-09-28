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


%{

#include "copasi/sensitivities/CSensProblem.h"

%}

%ignore CSensItem::operator==;
%ignore CSensItem::operator!=;

%ignore CSensProblem::SubTaskName;
%ignore CSensProblem::XMLSubTask;

%ignore CSensProblem::printResult;
%ignore CSensProblem::print;
%ignore CSensProblem::getResult() const;
%ignore CSensProblem::getResultAnnotated() const;
%ignore CSensProblem::getScaledResult() const;
%ignore CSensProblem::getScaledResultAnnotated() const;
%ignore CSensProblem::getCollapsedResult() const;
%ignore CSensProblem::getCollapsedResultAnnotated() const;

%ignore operator<<(std::ostream&,const CSensProblem&);
%ignore CSensProblem::SubTaskTypeToTask;

%extend CSensProblem {
  %{
    using CSensProblem_SubTaskTypeToTask = decltype(CSensProblem::SubTaskTypeToTask);
    using CSensProblem_SubTaskTypeToTask_Map = CBidirectionalMap< CSensProblem_SubTaskTypeToTask::EnumType, CSensProblem_SubTaskTypeToTask::AnnotationType, CSensProblem_SubTaskTypeToTask::Size >;
    using CSensProblem_SubTaskTypeToTask_AnnotationType = CEnumAnnotation< CSensProblem_SubTaskTypeToTask_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CSensProblem_SubTaskTypeToTask_AnnotationType& getSubTaskTypeToTask() {
    return CSensProblem::SubTaskTypeToTask;
  }
}

%include "sensitivities/CSensProblem.h"


