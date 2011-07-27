// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CVector.i,v $ 
//   $Revision: 1.8.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/07/27 12:58:49 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CVector.h"

%}

%ignore operator<<;
%ignore operator[](const size_t & );
%ignore operator[](const size_t & ) const;
%ignore operator()(const size_t & );
%ignore operator()(const size_t & ) const;
%ignore operator = (const CType &);
%ignore operator = (const CVector <CType> &);
%ignore CVectorCore::array() const;
%ignore CVectorCore::array();
%ignore CVector::resize;
%ignore CVector::applyPivot;
%ignore CVectorCore::CVectorCore(const size_t&, CType*);

%warnfilter(362) operator=;
%warnfilter(389) operator[];
%warnfilter(302) operator<<;


%include "utilities/CVector.h"

%extend CVectorCore
{
  virtual CType get(size_t index)
  {
      return (*self)[index];
  }

#ifdef SWIGPYTHON
  virtual size_t __len__() const
  {
    return self->size();
  }
#endif // SWIGPYTHON
}


typedef CVectorCore<C_FLOAT64> FloatVectorCore;
typedef CVector<C_FLOAT64> FloatVector;
typedef CVectorCore<unsigned long> ULongVectorCore;
typedef CVector<unsigned long> ULongVector;
typedef CVectorCore<size_t> SizeTVectorCore;
typedef CVector<size_t> SizeTVector;
typedef CVectorCore<CCopasiObject*> ObjectVectorCore;
typedef CVector<CCopasiObject*> ObjectVector;

%template(FloatVectorCore) CVectorCore<C_FLOAT64>;
%template(FloatVector) CVector<C_FLOAT64>;
%template(ULongVectorCore) CVectorCore<unsigned long>;
%template(ULongVector) CVector<unsigned long>;
%template(SizeTVectorCore) CVectorCore<size_t>;
%template(SizeTVector) CVector<size_t>;
%template(ObjectVectorCore) CVectorCore<CCopasiObject*>;
%template(ObjectVector) CVector<CCopasiObject*>;


