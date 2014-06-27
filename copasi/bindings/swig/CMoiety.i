// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "model/CMoiety.h"  
  
%}

%nodefaultctor CMoiety;
%nodefaultdtor CMoiety;

%ignore CTotalNumberReference::CTotalNumberReference(const std::string & name,
                        const CCopasiContainer * pParent,
                        C_FLOAT64 & reference);
%ignore CDependentNumberReference::CDependentNumberReference(const std::string & name,
                            const CCopasiContainer * pParent,
                            C_FLOAT64 & reference);

%include "model/CMoiety.h"

/**
 * Actually CMoiety now has a method to refresh the dependent number and return
 * it, it is called dependentNumber().
 * getDependentNumber will only get the number without refresh.
%extend CMoiety
{
  
  C_FLOAT64 getDependentNumber() const
  {
    self->refreshDependentNumber();
    return self->getDependentNumber();
  }  

}
 */  




