// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/undo/CData.h"
%}

%template(CDataStdVector) std::vector<CData>;

%include "copasi/undo/CData.h"



