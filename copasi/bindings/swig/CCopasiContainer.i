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

#include "report/CCopasiContainer.h"

%}


%ignore operator++;
%ignore operator!=;
%ignore CCopasiContainer::CObjectMap::iterator;
%ignore CCopasiContainer::CObjectMap::iterator::operator++;
%ignore CCopasiContainer::CObjectMap::const_iterator::operator++;
%ignore CCopasiContainer::CCopasiContainer(const std::string& name,
                                           const CCopasiContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);

%ignore CCopasiContainer::add(CCopasiObject*,const bool&); // needs to be hidden since it conflicts with methods in derived classes 
%ignore CCopasiContainer::remove(CCopasiObject*); // needs to be hidden since it conflicts with methods in derived classes 
%ignore CCopasiContainer::getObjects;

%include "report/CCopasiContainer.h"

