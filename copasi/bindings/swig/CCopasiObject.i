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
#include "copasi/core/CDataObject.h"
%}

%ignore CObjectInterface::getValidity() const;
%ignore CObjectInterface::getValuePointer;
%ignore UpdateMethod;
%ignore SpecificUpdateMethod;
%ignore Refresh;
%ignore operator<<;
%ignore CDataObject::setRenameHandler;
%ignore CDataObject::setRenameHandler;
%ignore CDataObject::getValuePointer;
%ignore CDataObject::print;
%ignore CDataObject::setUpdateMethod;
%ignore CDataObject::getUpdateMethod;
%ignore CDataObject::setRefresh;
%ignore CDataObject::getRefresh;
%ignore CDataObject::buildUpdateSequence;
%ignore CDataObject::getDirectDependencies;
%ignore CDataObject::setDirectDependencies;
%ignore CDataObject::getAllDependencies;

%include "report/CRenameHandler.h"
%include "report/CDataObject.h"

%extend CObjectInterface
{
public:
	CDataObject* toObject()
	{
		return dynamic_cast<CDataObject*>($self);
	}
  
  std::string printToString()
  {
    CDataObject* obj = dynamic_cast<CDataObject*>($self);
    if (obj == NULL)
      return "";
    std::stringstream str; 
    obj->print(&str);
    return str.str();
  }

}
