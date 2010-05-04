// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CReaction.i,v $ 
//   $Revision: 1.13.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/04 15:56:42 $ 
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

#include "model/CReaction.h"

%}
    
%ignore CReaction::getSmallestCompartment() const; // not implemented
%ignore CReaction::getParameterMappings() const; 

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CReaction::getChemEq() const;
%ignore CReaction::getParameters() const;

#endif // SWIGJAVA

%catches(CCopasiException) CReaction::getLargestCompartment() const;

%include "model/CReaction.h"


