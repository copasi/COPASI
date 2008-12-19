// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CReaction.i,v $ 
//   $Revision: 1.12.6.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/18 10:37:24 $ 
// End CVS Header 

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

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CReaction::getChemEq() const;
%ignore CReaction::getParameters() const;

#endif // SWIGJAVA


%include "model/CReaction.h"


