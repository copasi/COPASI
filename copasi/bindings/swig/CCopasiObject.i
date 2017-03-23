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
#include "report/CRenameHandler.h"
#include "report/CCopasiObject.h"
%}

%ignore CObjectInterface::getValidity() const;
%ignore CObjectInterface::getValuePointer;
%ignore UpdateMethod;
%ignore SpecificUpdateMethod;
%ignore Refresh;
%ignore operator<<;
%ignore CCopasiObject::setRenameHandler;
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
  
  std::string printToString()
  {
    CCopasiObject* obj = dynamic_cast<CCopasiObject*>($self);
    if (obj == NULL)
      return "";
    std::stringstream str; 
    obj->print(&str);
    return str.str();
  }

}
