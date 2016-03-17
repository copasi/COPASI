// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 






%{

#include "utilities/CUnit.h"
#include <assert.h>
%}

%ignore CUnit::getSymbolComponents() const;
