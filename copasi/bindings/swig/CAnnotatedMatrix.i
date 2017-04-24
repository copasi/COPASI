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

#include "core/CDataArray.h"

%}

%ignore operator<<;

%ignore CDataArray::operator[]; 
%ignore CMatrixInterface::operator[] (const index_type & index); 
%ignore CMatrixInterface::operator[] (const index_type & index); 
%ignore CMatrixInterface::operator[] (const index_type & index) const;
%ignore CVectorInterface::operator[] (const index_type & index) ;
%ignore CVectorInterface::operator[] (const index_type & index) const;
%ignore CDataArray::operator=(const CDataArray&);
%ignore CDataArray::array() const;
%ignore CDataArray::printRecursively;
%ignore CDataArray::print;
%ignore CDataArray::appendElementReferences;
%ignore operator<<(std::ostream &os, const CDataArray & o);

%include "core/CDataArray.h"
%include "core/CMatrix.h"

%extend CMatrixInterface {
   /* convert the operator[] to get methods */
   virtual CArrayInterface::data_type& get(const CArrayInterface::index_type & index)
   {
      return (*($self))[index];
   }
};

%extend CVectorInterface {
   /* convert the operator[] to get methods */
   virtual CArrayInterface::data_type& get(const CArrayInterface::index_type & index)
   {
      return (*($self))[index];
   }
};

