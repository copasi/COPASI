// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExperiment.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/15 20:47:01 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CExperiment.h"

%}

%ignore CExperiment::XMLType;
%ignore CExperiment::WeightMethodType;
%ignore CExperiment::operator=;

%include "parameterFitting/CExperiment.h"


