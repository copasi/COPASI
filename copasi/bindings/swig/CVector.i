// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CVectorCore::CVectorCore(const unsigned C_INT32&, CType*);

%warnfilter(362) operator=;
%warnfilter(389) operator[];
%warnfilter(302) operator<<;


%include "utilities/CVector.h"

%extend CVectorCore
{
  virtual CType get(unsigned C_INT32 index)
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

//%extend CVector
//{
//  virtual CType get(unsigned C_INT32 index)
//  {
//      return (*self)[index];
//  }
//
//  virtual unsigned C_INT32 size() const
//  {
//    return self->size();
//  }
//}

typedef CVectorCore<C_FLOAT64> FloatVectorCore;
typedef CVector<C_FLOAT64> FloatVector;
#if !SWIGPYTHON && !SWIGR
typedef CVectorCore<unsigned long> ULongVectorCore;
typedef CVector<unsigned long> ULongVector;
#endif
typedef CVectorCore<size_t> SizeTVectorCore;
typedef CVector<size_t> SizeTVector;
typedef CVectorCore<CCopasiObject*> ObjectVectorCore;
typedef CVector<CCopasiObject*> ObjectVector;

%template(FloatVectorCore) CVectorCore<C_FLOAT64>;
%template(FloatVector) CVector<C_FLOAT64>;
#if !SWIGPYTHON && !SWIGR
%template(ULongVectorCore) CVectorCore<unsigned long>;
%template(ULongVector) CVector<unsigned long>;
#endif
%template(SizeTVectorCore) CVectorCore<size_t>;
%template(SizeTVector) CVector<size_t>;
%template(ObjectVectorCore) CVectorCore<CCopasiObject*>;
%template(ObjectVector) CVector<CCopasiObject*>;


