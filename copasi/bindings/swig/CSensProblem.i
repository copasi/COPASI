// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSensProblem.i,v $ 
//   $Revision: 1.1.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/07/27 19:39:52 $ 
// End CVS Header 

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
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

