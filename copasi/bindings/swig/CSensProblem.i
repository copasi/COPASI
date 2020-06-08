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


%{

#include "copasi/sensitivities/CSensProblem.h"

%}

%ignore CSensItem::operator==;
%ignore CSensItem::operator!=;

%ignore CSensProblem::SubTaskName;
%ignore CSensProblem::XMLSubTask;

%ignore CSensProblem::printResult;
%ignore CSensProblem::print;
%ignore CSensProblem::getResult() const;
%ignore CSensProblem::getResultAnnotated() const;
%ignore CSensProblem::getScaledResult() const;
%ignore CSensProblem::getScaledResultAnnotated() const;
%ignore CSensProblem::getCollapsedResult() const;
%ignore CSensProblem::getCollapsedResultAnnotated() const;

%ignore operator<<(std::ostream&,const CSensProblem&);

%include "sensitivities/CSensProblem.h"


