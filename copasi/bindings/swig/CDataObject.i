// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 










%{
#include "copasi/core/CRegisteredCommonName.h"
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
%ignore CDataObject::destruct;
%ignore CDataObject::createUndoData;

%include "core/CRegisteredCommonName.h"
%include "core/CDataObject.h"

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

namespace std {

#if !defined(SWIGR) && !defined(SWIGPERL) && !defined(SWIGOCTAVE)
%template(DataObjectSet) set< const CDataObject * >;
%template(DataObjectMap) map< const CDataObject *, const CDataObject * >;
%template(DataObjectVector) vector< const CDataObject * >;
%template(VectorOfDataObjectVector) vector< vector< const CDataObject * > >;
#endif // !defined(SWIGR) && !defined(SWIGPERL) && !defined(SWIGOCTAVE)
}
