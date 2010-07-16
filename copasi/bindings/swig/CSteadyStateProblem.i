// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSteadyStateProblem.i,v $ 
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

#include "steadystate/CSteadyStateProblem.h"

%}

%ignore CSteadyStateProblem::load;
%ignore CSteadyStateProblem::setJacobianRequested;
%ignore CSteadyStateProblem::setStabilityAnalysisRequested;

%include "steadystate/CSteadyStateProblem.h"

// unignore setJacobianRequested
%rename (setJacobianRequested) CSteadyStateProblem::setJacobianRequested;
// unignore setStabilityAnalysisRequested
%rename (setStabilityAnalysisRequested) CSteadyStateProblem::setStabilityAnalysisRequested;

%extend CSteadyStateProblem
{
    void setJacobianRequested(bool jacobianRequested)
    {
        $self->setJacobianRequested(jacobianRequested);
    }

    void setStabilityAnalysisRequested(bool stabilityAnalysisRequested)
    {
        $self->setStabilityAnalysisRequested(stabilityAnalysisRequested);
    }
}
