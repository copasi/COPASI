// Copyright (C) 2024 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "copasi/sbml/SBMLUnitSupport.h"

%}

%ignore SBMLUnitSupport::unitKindToString(UnitKind_t kind);

#if (defined SWIGJAVA || defined SWIGCSHARP)
  %ignore SBMLUnitSupport::UnitType;
#endif // SWIGJAVA || SWIGCSHARP                      

%include "sbml/SBMLUnitSupport.h"



