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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CAnnotatedMatrix.h"

%}

%ignore operator<<;

%ignore CArrayAnnotation::operator[]; 
%ignore CCopasiMatrixInterface::operator[] (const index_type & index); 
%ignore CCopasiMatrixInterface::operator[] (const index_type & index); 
%ignore CCopasiMatrixInterface::operator[] (const index_type & index) const;
%ignore CCopasiVectorInterface::operator[] (const index_type & index) ;
%ignore CCopasiVectorInterface::operator[] (const index_type & index) const;
%ignore CArrayAnnotation::operator=(const CArrayAnnotation&);
%ignore CArrayAnnotation::array() const;
%ignore CArrayAnnotation::printRecursively;
%ignore CArrayAnnotation::print;
%ignore CArrayAnnotation::appendElementReferences;
%ignore operator<<(std::ostream &os, const CArrayAnnotation & o);

%include "utilities/CAnnotatedMatrix.h"

%extend CCopasiMatrixInterface {
   /* convert the operator[] to get methods */
   virtual CCopasiAbstractArray::data_type& get(const CCopasiAbstractArray::index_type & index)
   {
      return (*($self))[index];
   }
};

%extend CCopasiVectorInterface {
   /* convert the operator[] to get methods */
   virtual CCopasiAbstractArray::data_type& get(const CCopasiAbstractArray::index_type & index)
   {
      return (*($self))[index];
   }
};

