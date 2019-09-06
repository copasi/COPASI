// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "copasi/core/CDataContainer.h"

%}


%ignore operator++;
%ignore operator!=;
%ignore CDataContainer::CObjectMap::iterator;
%ignore CDataContainer::CObjectMap::iterator::operator++;
%ignore CDataContainer::CObjectMap::const_iterator::operator++;
%ignore CDataContainer::CDataContainer(const std::string& name,
                                           const CDataContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);

%ignore CDataContainer::add(CDataObject*,const bool&); // needs to be hidden since it conflicts with methods in derived classes 
%ignore CDataContainer::remove(CDataObject*); // needs to be hidden since it conflicts with methods in derived classes 
%ignore CDataContainer::getObjects;
%ignore CDataContainer::insert;
%ignore CDataContainer::updateIndex;


%include "copasi/core/CDataContainer.h"

#ifndef SWIGR
%template(ContainerList) std::vector<const CDataContainer*>;
#endif
