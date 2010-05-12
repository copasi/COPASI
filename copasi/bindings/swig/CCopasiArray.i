// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiArray.i,v $ 
//   $Revision: 1.2.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/12 17:12:40 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "report/CCopasiArray.h"

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

%include "report/CCopasiArray.h"


%extend CCopasiAbstractArray {
   /* convert the operator[] to get methods */
   virtual CCopasiAbstractArray::data_type get(const CCopasiAbstractArray::index_type & index)
   {
      return (*($self))[index];
   }
};

%template(AnnotatedFloatMatrix) CCopasiMatrixInterface<CMatrix<C_FLOAT64> >;
typedef CCopasiMatrixInterface<CMatrix<C_FLOAT64> > AnnotatedFloatMatrix;

