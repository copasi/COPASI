// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiProblem.i,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/06/23 12:45:47 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "utilities/CCopasiProblem.h"

%}

%ignore CCopasiProblem::CCopasiProblem(const CCopasiTask::Type& type, const CCopasiContainer* pParent);
%ignore CCopasiProblem::setModel(CModel* pModel);
%ignore CCopasiProblem::setCallback(CProcessReport* pCallBack);
%ignore CCopasiProblem::initialize();
%ignore CCopasiProblem::calculate();
%ignore CCopasiProblem::restore(const bool& updateModel);
%ignore CCopasiProblem::checkParametricConstraints();
%ignore CCopasiProblem::checkFunctionalConstraints();
%ignore CCopasiProblem::print(std::ostream* ostream) const;
%ignore CCopasiProblem::printResult(std::ostream* ostream) const;
%ignore operator<<(std::ostream& os,const CCopasiProblem& o);

%include "utilities/CCopasiProblem.h"

