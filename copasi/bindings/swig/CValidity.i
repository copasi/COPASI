// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/utilities/CValidity.h"
%}

%ignore CIssue::operator bool;

%ignore CIssue::Success;
%ignore CIssue::Information;
%ignore CIssue::Warning;
%ignore CIssue::Error;

%ignore CIssue::eKind;
%ignore CIssue::eSeverity;


%ignore CIssue::kindNames;
%ignore CIssue::kindDescriptions;
%ignore CIssue::severityNames;

%extend CIssue {
  // 1. Hide the C++17 type deduction from SWIG, but expose it to the C++ wrapper compiler
  %{
    using CIssue_kindNames = decltype(CIssue::kindNames);
    using CIssue_kindNames_Map = CBidirectionalMap< CIssue_kindNames::EnumType, CIssue_kindNames::AnnotationType, CIssue_kindNames::Size >;
    using CIssue_kindNames_AnnotationType = CEnumAnnotation< CIssue_kindNames_Map >;

    using CIssue_kindDescriptions = decltype(CIssue::kindDescriptions);
    using CIssue_kindDescriptions_Map = CBidirectionalMap< CIssue_kindDescriptions::EnumType, CIssue_kindDescriptions::AnnotationType, CIssue_kindDescriptions::Size >;
    using CIssue_kindDescriptions_AnnotationType = CEnumAnnotation< CIssue_kindDescriptions_Map >;

    using CIssue_severityNames = decltype(CIssue::severityNames);
    using CIssue_severityNames_Map = CBidirectionalMap< CIssue_severityNames::EnumType, CIssue_severityNames::AnnotationType, CIssue_severityNames::Size >;
    using CIssue_severityNames_AnnotationType = CEnumAnnotation< CIssue_severityNames_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CIssue_kindNames_AnnotationType& getkindNames() {
    return CIssue::kindNames;
  }

  const CIssue_kindDescriptions_AnnotationType& getkindDescriptions() {
    return CIssue::kindDescriptions;
  }
  
  const CIssue_severityNames_AnnotationType& getseverityNames() {
    return CIssue::severityNames;
  }
}


%include "copasi/utilities/CValidity.h"



