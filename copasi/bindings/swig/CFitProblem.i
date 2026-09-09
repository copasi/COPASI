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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "copasi/parameterFitting/CFitProblem.h"

%}

%extend CFitProblem
{
  CFitItem & addFitItem(const CCommonName & objectCN)
  {
    return $self->addFitItem(CRegisteredCommonName(objectCN));
  }
  
  CFitItem & addFitItem(const std::string & objectCN)
  {
    return $self->addFitItem(CRegisteredCommonName(objectCN));
  }

  CFitConstraint& addFitConstraint(const CCommonName & objectCN)
  {
    return $self->addFitConstraint(CRegisteredCommonName(objectCN));
  }

  CFitConstraint& addFitConstraint(const std::string & objectCN)
  {
    return $self->addFitConstraint(CRegisteredCommonName(objectCN));
  }
}

%rename (output) CFitProblem::print;
//%ignore CFitProblem::setCallBack;
%ignore CFitProblem::getExperimentSet() const;
%ignore CFitProblem::getCrossValidationSet() const;

%include "copasi/parameterFitting/CFitProblem.h"



