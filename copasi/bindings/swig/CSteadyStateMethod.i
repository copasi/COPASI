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

#include "copasi/steadystate/CSteadyStateMethod.h"

%}

%newobject CSteadyStateMethod::createSteadyStateMethod(CTaskEnum::Method subType = CTaskEnum::Newton);

%ignore CSteadyStateMethod::process;

%include "copasi/steadystate/CSteadyStateMethod.h"

%extend CSteadyStateMethod
{
    CSteadyStateMethod::ReturnCode process(CState* pState, CMatrix<C_FLOAT64>& jacobianX)
    {
        return $self->process(pState,jacobianX,NULL);
    }
}
