// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiObject.i,v $ 
//   $Revision: 1.7 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/03/04 19:22:40 $ 
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

#include "report/CCopasiObject.h"
%}

%ignore UpdateMethod;
%ignore SpecificUpdateMethod;
%ignore Refresh;
%ignore operator<<(std::ostream& os,const CCopasiObject& o);
%ignore CCopasiObject::getObjectDataModel() const;

%rename (output) print(std::ostream*) const;

%include "report/CCopasiObject.h"

