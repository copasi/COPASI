// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExperimentSet.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CExperimentSet.h"

%}

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CExperimentSet::getExperiment(const unsigned long&) const;
%ignore CExperimentSet::getExperiment(const std::string&) const;

#endif // SWIGJAVA


%include "parameterFitting/CExperimentSet.h"



