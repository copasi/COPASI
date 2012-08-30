// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CAnnotatedMatrix.i,v $ 
//   $Revision: 1.4 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "utilities/CAnnotatedMatrix.h"

%}

%ignore operator<<;

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

