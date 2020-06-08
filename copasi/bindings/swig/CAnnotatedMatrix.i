// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "copasi/core/CDataArray.h"

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

%include "copasi/core/CDataArray.h"
%include "copasi/core/CMatrix.h"

%extend CMatrixInterface {

  CCopasiAbstractArray::data_type get(int index1)
  {
    CCopasiAbstractArray::index_type index;
    index.push_back(index1);
    return (*($self->getArray()))[index];
  }
  
  CCopasiAbstractArray::data_type get(int index1, int index2)
  {
    CArrayAnnotation::index_type index;
    index.push_back(index1);
    index.push_back(index2);
    return (*($self->getArray()))[index];
  }
  
  CCopasiAbstractArray::data_type get(int index1, int index2, int index3)
  {
    CCopasiAbstractArray::index_type index;
    index.push_back(index1);
    index.push_back(index2);
    index.push_back(index3);
    return (*($self->getArray()))[index];
  }
}

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

