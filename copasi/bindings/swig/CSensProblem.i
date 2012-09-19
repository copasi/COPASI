// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CSensProblem.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/10/13 12:03:01 $ 
// End CVS Header 

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


