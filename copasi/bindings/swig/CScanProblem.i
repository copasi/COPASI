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

#include "copasi/scan/CScanProblem.h"

%}

%newobject CScanProblem::createScanItem(CScanProblem::Type type, unsigned C_INT32 steps = 5, const CDataObject* obj = NULL);

%ignore CScanProblem::getScanItemType(size_t index);
%ignore CScanProblem::getScanItem(size_t index) const;
%ignore CScanProblem::load;
%ignore CScanProblem::OutputTypeName;

%extend CScanProblem {
  %{
    using CScanProblem_OutputTypeName = decltype(CScanProblem::OutputTypeName);
    using CScanProblem_OutputTypeName_Map = CBidirectionalMap< CScanProblem_OutputTypeName::EnumType, CScanProblem_OutputTypeName::AnnotationType, CScanProblem_OutputTypeName::Size >;
    using CScanProblem_OutputTypeName_AnnotationType = CEnumAnnotation< CScanProblem_OutputTypeName_Map >;
  %}

  // 2. Define the getter function for SWIG using a clean macro string definition
  // We use RealAnnotationType const& so SWIG treats it as a non-owning read-only memory reference
  const CScanProblem_OutputTypeName_AnnotationType& getOutputTypeName() {
    return CScanProblem::OutputTypeName;
  }
}

#if (defined SWIGJAVA || defined SWIGCSHARP)
  %ignore CScanProblem::OutputType;
#endif // SWIGJAVA || SWIGCSHARP                      

%include "scan/CScanProblem.h"



