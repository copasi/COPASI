// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CState.i,v $ 
//   $Revision: 1.6.16.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
// End CVS Header 

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

#include "model/CState.h"

%}


%ignore CState::getEntities() const;
%ignore CState::beginIndependent() const;
%ignore CState::endIndependent() const;
%ignore CState::beginDependent() const;
%ignore CState::endDependent() const;
%ignore CState::beginFixed() const;
%ignore CState::endFixed() const;
    
%ignore CState::check; // not implemented

%include "model/CState.h"



