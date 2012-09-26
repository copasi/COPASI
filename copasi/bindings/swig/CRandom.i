// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.


%{

#include "randomGenerator/CRandom.h"

%}

%newobject CRandom::createGenerator(CRandom::Type type = CRandom::mt19937, unsigned C_INT32 seed = 0);
%ignore CRandom::varp;
%ignore CRandom::vare;
%ignore CRandom::XMLType;
%ignore CRandom::TypeName;

// suppress warnings on nested structures
%warnfilter(325) PoissonVars;
%warnfilter(325) ExpVars;


%include "randomGenerator/CRandom.h"



