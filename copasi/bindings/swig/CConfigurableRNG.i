// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 



%{

#include "copasi/randomGenerator/CConfigurableRNG.h"

%}

%newobject CConfigurableRNG::create(CConfigurableRNG::Type type = CConfigurableRNG::Type::MersenneTwister, unsigned C_INT32 seed = 0);


%include "randomGenerator/CConfigurableRNG.h"



