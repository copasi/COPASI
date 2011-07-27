// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExperimentSet.i,v $ 
//   $Revision: 1.2.4.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/07/27 12:17:54 $ 
// End CVS Header 

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CExperimentSet.h"

%}

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CExperimentSet::getExperiment(const size_t&) const;
%ignore CExperimentSet::getExperiment(const std::string&) const;

#endif // SWIGJAVA


%include "parameterFitting/CExperimentSet.h"



