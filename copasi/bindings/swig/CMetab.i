// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMetab.i,v $ 
//   $Revision: 1.7 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

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

%{

#include "model/CMetab.h"

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



#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CMetab::operator =;

#endif // SWIGJAVA


%include "model/CMetab.h"


