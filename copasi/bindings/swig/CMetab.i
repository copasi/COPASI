// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "model/CMetab.h"
#include "model/CMetabNameInterface.h"
%}

%ignore CMetab::load;
%ignore CMetabOld::load;
%ignore CMetab::getValuePointer;
%ignore CMetab::getDeletedObjects;
%ignore CConcentrationReference::getApplyInitialValueRefresh;
%ignore CConcentrationReference::getDirectDependencies;
%ignore CParticleReference::getDirectDependencies;

//ignore the constructors for the CConcentrationReference because we
//don't need to create instances of it
%ignore CConcentrationReference::CConcentrationReference;
%ignore CParticleReference::CParticleReference;



#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CMetab::operator =;

#endif // SWIGJAVA || CSHARP


%include "model/CMetab.h"

%include <std_pair.i>
%include <std_string.i>
%template(StringPair) std::pair<std::string,std::string>;
%include "model/CMetabNameInterface.h"

