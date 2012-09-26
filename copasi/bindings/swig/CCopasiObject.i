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
#include "report/CRenameHandler.h"
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

%include "report/CRenameHandler.h"
%include "report/CCopasiObject.h"

%extend CObjectInterface
{
public:
	CCopasiObject* toObject()
	{
		return dynamic_cast<CCopasiObject*>($self);
	}
}
