// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// 1. Inject headers safely into the C++ compiler's scope
%{
#include "copasi/core/CEnumAnnotation.h"
%}

// 4. Process the main header
%include "copasi/core/CEnumAnnotation.h"
