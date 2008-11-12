// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMatrix.i,v $ 
//   $Revision: 1.6.24.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:18:48 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CMatrix.h"

%}

%include "utilities/CMatrix.h"


%extend CMatrix
{
    virtual elementType& get(const unsigned C_INT32& row,const unsigned C_INT32& col)
    {
        return (*self)(row,col);
    }
}

%template(FloatMatrix) CMatrix<C_FLOAT64>;

typedef CMatrix<C_FLOAT64> FloatMatrix;



