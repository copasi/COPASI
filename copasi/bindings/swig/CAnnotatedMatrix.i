// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CAnnotatedMatrix.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/23 12:45:47 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "utilities/CAnnotatedMatrix.h"

%}

%ignore CCopasiAbstractArray::operator[] (const index_type & index); 
%ignore CCopasiAbstractArray::operator[] (const index_type & index) const;
%ignore CCopasiArray::operator[] (const index_type & index); 
%ignore CCopasiArray::operator[] (const index_type & index) const;
%ignore CCopasiMatrixInterface::operator[] (const index_type & index); 
%ignore CCopasiMatrixInterface::operator[] (const index_type & index) const;
%ignore CCopasiVectorInterface::operator[] (const index_type & index) ;
%ignore CCopasiVectorInterface::operator[] (const index_type & index) const;
%ignore CArrayAnnotation::operator=(const CArrayAnnotation&);
%ignore CArrayAnnotation::array() const;
%ignore operator<<(std::ostream &os, const CArrayAnnotation & o);
%ignore CArrayAnnotation::print(std::ostream* ostream) const;

%include "utilities/CAnnotatedMatrix.h"

typedef std::vector<unsigned int> index_type;
typedef C_FLOAT64 data_type;


%extend CCopasiAbstractArray {
   /* convert the operator[] to get methods */
   virtual CCopasiAbstractArray::data_type& get(const CCopasiAbstractArray::index_type & index) = 0
   {
      return (*($self))[index];
   };
};

%extend CCopasiArray {
   /* convert the operator[] to get methods */
   virtual CCopasiAbstractArray::data_type& get(const CCopasiAbstractArray::index_type & index)
   {
      return (*($self))[index];
   }
};

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


%template(AnnotatedFloatMatrix) CCopasiMatrixInterface<CMatrix<C_FLOAT64> >;

typedef CCopasimatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;

