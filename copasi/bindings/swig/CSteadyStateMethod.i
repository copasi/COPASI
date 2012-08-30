// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CSteadyStateMethod.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "steadystate/CSteadyStateMethod.h"

%}

%newobject CSteadyStateMethod::createSteadyStateMethod(CCopasiMethod::SubType subType = CCopasiMethod::Newton);

%ignore CSteadyStateMethod::process;

%include "steadystate/CSteadyStateMethod.h"

%extend CSteadyStateMethod
{
    CSteadyStateMethod::ReturnCode process(CState* pState, CMatrix<C_FLOAT64>& jacobianX)
    {
        return $self->process(pState,jacobianX,NULL);
    }
}
