// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CVector.i,v $ 
//   $Revision: 1.7 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/09/01 13:52:22 $ 
// End CVS Header 

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

//%ignore operator<< <> (std::ostream& os,const CVector< CType >& A);
%ignore operator<< (std::ostream& os,const CVector< CType >& A);
%ignore operator[](const unsigned C_INT32 & row);
%ignore operator[](const unsigned C_INT32 & row) const;
%ignore operator()(const unsigned C_INT32 & row);
%ignore operator()(const unsigned C_INT32 & row) const;
%ignore operator = (const CType & value);
%ignore operator = (const CVector <CType> & rhs);
%ignore array() const;
%ignore CVector::resize;
%ignore CVector::applyPivot;


%warnfilter(362) operator=;
%warnfilter(389) operator[];


%include "utilities/CVector.h"

typedef CVectorCore<C_FLOAT64> FloatVectorCore;
typedef CVector<C_FLOAT64> FloatVector;

%template(FloatVectorCore) CVectorCore<C_FLOAT64>;
%template(FloatVector) CVector<C_FLOAT64>;

%extend CVectorCore<C_FLOAT64>
{
  virtual C_FLOAT64 get(unsigned C_INT32 index)
  {
      return (*self)[index];
  }
}

