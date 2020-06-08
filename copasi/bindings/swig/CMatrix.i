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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/core/CMatrix.h"
#include "copasi/utilities/CLinkMatrix.h"

%}

#if (defined SWIGJAVA || defined SWIGCSHARP)

// ignore some operators to get rid of the warnings
%ignore CMatrix::operator =;
%ignore CMatrix::operator [];
%ignore CMatrix::operator ();
%ignore CMatrix::array;

#endif // SWIGJAVA || CSHARP

%include "core/CMatrix.h"


%extend CMatrix
{
    virtual elementType get(const unsigned C_INT32& row,const unsigned C_INT32& col)
    {
        return (*self)(row,col);
    }
}

%template(FloatMatrix) CMatrix<C_FLOAT64>;
%template(IntMatrix) CMatrix<int>;

typedef CMatrix<C_FLOAT64> FloatMatrix;


%include "utilities/CLinkMatrix.h"
