// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

#include "copasi/core/CVector.h"

%}

%ignore operator<<;
%ignore operator[](const size_t & );
%ignore operator[](const size_t & ) const;
%ignore operator()(const size_t & );
%ignore operator()(const size_t & ) const;
%ignore operator = (const CType &);
%ignore operator = (const CVector <CType> &);
%ignore operator = (const CVectorCore <CType> &);
%ignore CVector::operator=;
%ignore CVectorCore::array() const;
%ignore CVectorCore::array();
%ignore CVector::resize;
%ignore CVector::applyPivot;
%ignore CVectorCore::CVectorCore(const unsigned C_INT32&, CType*);

%warnfilter(362) operator=;
%warnfilter(389) operator[];
%warnfilter(302) operator<<;


%include "copasi/core/CVector.h"

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


%define ExtendCVectorPtr(name, T)
%extend name<T>
{
    T get(int i)
    {
      if (i >= self->size())
        return NULL;
      return (*self)[i];
    }

    size_t size() const
    {
      return self->size();
    }
}
%enddef

// %extend CVector
// {
//   virtual CType get(unsigned C_INT32 index) throw(std::out_of_range)
//   {
//       return (*self)[index];
//   }

//   virtual unsigned C_INT32 size() const
//   {
//     return self->size();
//   }
// }

typedef CVectorCore<C_FLOAT64> FloatVectorCore;
typedef CVector<C_FLOAT64> FloatVector;
#if !SWIGPYTHON && !SWIGR
typedef CVectorCore<unsigned long> ULongVectorCore;
typedef CVector<unsigned long> ULongVector;
#endif
typedef CVectorCore<size_t> SizeTVectorCore;
typedef CVector<size_t> SizeTVector;
typedef CVectorCore<CDataObject*> ObjectVectorCore;
typedef CVector<CDataObject*> ObjectVector;
typedef CVectorCore<const CDataObject*> ConstObjectVectorCore;
typedef CVector<const CDataObject*> ConstObjectVector;

%template(FloatVectorCore) CVectorCore<C_FLOAT64>;
%template(FloatVector) CVector<C_FLOAT64>;
#if !SWIGPYTHON && !SWIGR
%template(ULongVectorCore) CVectorCore<unsigned long>;
%template(ULongVector) CVector<unsigned long>;
#endif
%template(SizeTVectorCore) CVectorCore<size_t>;
%template(SizeTVector) CVector<size_t>;
%template(ObjectVectorCore) CVectorCore<CDataObject*>;
%template(ObjectVector) CVector<CDataObject*>;
ExtendCVectorPtr(CVector, CDataObject*);
%template(ConstObjectVectorCore) CVectorCore<const CDataObject*>;
%template(ConstObjectVector) CVector<const CDataObject*>;
ExtendCVectorPtr(CVector, const CDataObject*);
%template(ConstFunctionVector) CVector<const CFunction*>;
ExtendCVectorPtr(CVector, const CFunction*);
%template(ConstFunctionVectorCore) CVectorCore<const CFunction*>;
%template(ConstObjectInterfaceVector) CVector<const CObjectInterface*>;
%template(ConstObjectInterfaceVectorCore) CVectorCore<const CObjectInterface*>;
ExtendCVectorPtr(CVector, const CObjectInterface*);
