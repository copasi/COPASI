// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CCopasiObject.i,v $ 
//   $Revision: 1.8 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:26 $ 
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

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CCopasiObject.h"
%}

%ignore UpdateMethod;
%ignore SpecificUpdateMethod;
%ignore Refresh;
%ignore operator<<;
%ignore CCopasiObject::getObjectDataModel() const;
%ignore CCopasiObject::setRenameHandler;
%ignore CCopasiObject::getValuePointer;
%ignore CCopasiObject::print;
%ignore CCopasiObject::setUpdateMethod;
%ignore CCopasiObject::getUpdateMethod;
%ignore CCopasiObject::setRefresh;
%ignore CCopasiObject::getRefresh;
%ignore CCopasiObject::buildUpdateSequence;
%ignore CCopasiObject::getDirectDependencies;
%ignore CCopasiObject::setDirectDependencies;
%ignore CCopasiObject::getAllDependencies;
%ignore CCopasiObject::dependsOn;
%ignore CCopasiObject::hasCircularDependencies;


%include "report/CCopasiObject.h"

