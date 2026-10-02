// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{
#include "copasi/undo/CDataValue.h"
%}

%ignore CDataValue::CDataValue(const CDataValue::Type &);
%ignore CDataValue::CDataValue(const Type &);
%template(CDataValueStdVector) std::vector<CDataValue>;

%include "copasi/undo/CDataValue.h"



