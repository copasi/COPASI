// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "sensitivities/CSensProblem.h"

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


