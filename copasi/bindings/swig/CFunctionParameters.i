// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFunctionParameters.i,v $ 
//   $Revision: 1.4.24.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:18:48 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "function/CFunctionParameters.h"

%}


%ignore operator[](unsigned C_INT32);
%ignore operator[](unsigned C_INT32) const;
%ignore operator[](const std::string&);
%ignore operator[](const std::string&) const;
%ignore operator= (const CFunctionParameters&);
%ignore operator==(const CFunctionParameters &) const;
%ignore operator<<(std::ostream&, const CFunctionParameters&);

%include "function/CFunctionParameters.h"



