// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CVector.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/12/12 14:53:31 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CVector.h"

%}

%ignore operator<<(std::ostream& os,const CVector< CType >& A);
%ignore operator<< <>(std::ostream& os,const CVector< CType >& A);
%ignore operator[](const unsigned C_INT32 & row);
%ignore operator[](const unsigned C_INT32 & row) const;
%ignore operator()(const unsigned C_INT32 & row);
%ignore operator()(const unsigned C_INT32 & row) const;
%ignore operator = (const CType & value);
%ignore operator = (const CVector <CType> & rhs);
%ignore array() const;


%include "utilities/CVector.h"

%extend CVector<C_FLOAT64>
{
    C_FLOAT64 get(unsigned int index)
    {
        return (*self)[index];
    }
};


