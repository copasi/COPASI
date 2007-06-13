// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CEigen.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/13 12:42:15 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "steadystate/CEigen.h"

%}

%ignore CEigen::print(std::ostream * ostream) const;
%ignore &operator<<(std::ostream &os, const CEigen &A);

%include "steadystate/CEigen.h"


